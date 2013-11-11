/*
 * This file is part of the OpenKinect Project. http://www.openkinect.org
 *
 * Copyright (c) 2010 individual OpenKinect contributors. See the CONTRIB file
 * for details.
 *
 * This code is licensed to you under the terms of the Apache License, version
 * 2.0, or, at your option, the terms of the GNU General Public License,
 * version 2.0. See the APACHE20 and GPL2 files for the text of the licenses,
 * or the following URLs:
 * http://www.apache.org/licenses/LICENSE-2.0
 * http://www.gnu.org/licenses/gpl-2.0.txt
 *
 * If you redistribute this file in source form, modified or unmodified, you
 * may:
 *   1) Leave this header intact and distribute it under the same terms,
 *      accompanying it with the APACHE20 and GPL20 files, or
 *   2) Delete the Apache 2.0 clause and accompany it with the GPL2 file, or
 *   3) Delete the GPL v2 clause and accompany it with the APACHE20 file
 * In all cases you must keep the copyright notice intact and include a copy
 * of the CONTRIB file.
 *
 * Binary distributions must follow the binary distribution requirements of
 * either License.
 */


#include "libfreenect.hpp"
#include <pthread.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <cmath>
#include <vector>

#if defined(__APPLE__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <stdlib.h>
#include <ncurses.h>

#include <assert.h>
#include <X11/Xlib.h>
#include <X11/Xatom.h>
#include <X11/extensions/XTest.h>
#include <math.h>

#define SCREEN (DefaultScreen(display)

#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <time.h>
#include  <sys/time.h> 

int snstvty;
float pointerx = 0, pointery = 0;
float mousex = 0, mousey = 0;
float tmousex = 0, tmousey = 0;
int pause1 = 0;
int screenw = 0, screenh = 0;
int pusx = 0, pusy = 0; 
Display *display;
Window root_window;

freenect_context *f_ctx;
freenect_device *f_dev;

char *archivo;
char *ip;
int num_threads;
int num_ciclos;
char *port;
int contador = 0;

void *llamada(void * param){

	int ciclos;

	for (ciclos = 0; num_ciclos > ciclos; ciclos++) {
		int sockfd, bindfd; // socket and bind file descriptors
		char getrequest[1024];
		struct addrinfo hints, *res;

		memset(&hints, 0, sizeof hints);
		hints.ai_family = AF_UNSPEC;
		hints.ai_socktype = SOCK_STREAM;

		sprintf(getrequest, "GET %s HTTP/1.1\nHOST: %s\nConnection:close\n\n", archivo, ip);

		// gets linked list of results of a specified hostname
		if ( getaddrinfo(ip, port, &hints, &res) != 0 ) {
		    fprintf(stderr, "Host or IP not valid\n"); //quits program if the hostname was not found
		    exit(0);
		}

		// creates a socket from hostname results and passes everything to a file descriptor
		sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);

		// bind the socket to the port passed to getaddrinfo()
		bindfd = bind(sockfd, res->ai_addr, res->ai_addrlen);

		// establish a connection and quits if there is a connection error
		if ( connect(sockfd, res->ai_addr, res->ai_addrlen) != 0 ) {
		    fprintf(stderr, "Connection error\n");
		    exit(0);
		}

		int optval = 1;
		setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval);

		// writes the HTTP request to the socked file descriptor
		write(sockfd, getrequest, strlen(getrequest));

		close(sockfd);
	}

	printf("Termino un cliente\n");
	return NULL;
}

void *client(char *host1, char *dato, char *port1){

	char *ptr, *host, path[100], *dns;
	archivo = dato; //                     /ser
	ip = host1;
	port = port1;
	num_threads = 1;
	num_ciclos = 1;

	printf(" ser ...\n");
	int creardor, cerrar;
	pthread_t thread_id[num_threads];

	//creando hilos
	printf(" Accediendo ...\n");
	for(creardor = 0; creardor < num_threads; creardor++){
		printf("Conexión: %d\n",creardor);
		pthread_create( &thread_id[creardor], NULL, llamada, NULL );
	}
	
	//waits all threads to finish
	contador = 0;
	for(cerrar = 0; cerrar < num_threads; cerrar++) {
		pthread_join( thread_id[cerrar], NULL);
	}
}

class Mutex {
public:
    Mutex() {
        pthread_mutex_init( &m_mutex, NULL );
    }
    void lock() {
        pthread_mutex_lock( &m_mutex );
    }
    void unlock() {
        pthread_mutex_unlock( &m_mutex );
    }

    class ScopedLock
    {
        Mutex & _mutex;
    public:
        ScopedLock(Mutex & mutex)
            : _mutex(mutex)
        {
            _mutex.lock();
        }
        ~ScopedLock()
        {
            _mutex.unlock();
        }
    };
private:
    pthread_mutex_t m_mutex;
};


/* thanks to Yoda---- from IRC */
class MyFreenectDevice : public Freenect::FreenectDevice {

public:
    MyFreenectDevice(freenect_context *_ctx, int _index)
        : Freenect::FreenectDevice(_ctx, _index), m_buffer_depth(freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB).bytes),m_buffer_video(freenect_find_video_mode(FREENECT_RESOLUTION_MEDIUM, FREENECT_VIDEO_RGB).bytes), m_gamma(2048), m_new_rgb_frame(false), m_new_depth_frame(false)
    {
        for( unsigned int i = 0 ; i < 2048 ; i++) {
            float v = i/2048.0;
            v = std::pow(v, 3)* 6;
            m_gamma[i] = v*6*256;
        }
    }

    //~MyFreenectDevice(){}
    // Do not call directly even in child
    void VideoCallback(void* _rgb, uint32_t timestamp) {
        Mutex::ScopedLock lock(m_rgb_mutex);
        uint8_t* rgb = static_cast<uint8_t*>(_rgb);
        std::copy(rgb, rgb+getVideoBufferSize(), m_buffer_video.begin());
        m_new_rgb_frame = true;
    };

    // Do not call directly even in child
    void DepthCallback(void* _depth, uint32_t timestamp) {
        Mutex::ScopedLock lock(m_depth_mutex);
        uint16_t* depth = static_cast<uint16_t*>(_depth);
        
	int first = 0;
	int px = 0 , py = 0;
	int tx = 0 , ty = 0;
	int alert = 0;

        for( unsigned int i = 0 ; i < 640*480 ; i++) {
            int pval = m_gamma[depth[i]];
	    
            tx++;
	    if(tx >= 640) {
		tx = 0;		
		ty++;
	    }

            switch (pval >> 8) {

            case 0:
                m_buffer_depth[3*i+0] = 255;
                m_buffer_depth[3*i+1] = 0;
                m_buffer_depth[3*i+2] = 0;
		alert ++;
		if (!first) { 
			first = i;
			px = tx;
			py = ty;				
		}
                break;
            case 1:
                m_buffer_depth[3*i+0] = 255;
                m_buffer_depth[3*i+1] = 255;
                m_buffer_depth[3*i+2] = 255;
                break;
            default:
                m_buffer_depth[3*i+0] = 0;
                m_buffer_depth[3*i+1] = 0;
                m_buffer_depth[3*i+2] = 0;
                break;
            }
	
        }
	
	

	if(alert > snstvty) {	
		printf("\n!!!TOO CLOSE!!!\n");

	} else {
		if(first) {
			pointerx = ((px-640.0f) / -1);
			pointery = (py);
			mousex = ((pointerx / 630.0f) * screenw);
			mousey = ((pointery / 470.0f) * screenh);
			int mx , my;
			mx = mousex;
			my = mousey;

			if(mx > tmousex) tmousex += (mx - tmousex) / 7;
			if(mx < tmousex) tmousex -= (tmousex - mx) / 7;
			if(my > tmousey) tmousey += (my - tmousey) / 7;
			if(my < tmousey) tmousey -= (tmousey - my) / 7;			
			
			if((pusx <= (mx + 15))  && (pusx >= (mx - 15)) && (pusy <= (my + 15))  && (pusy >= (my - 15))) {
				pause1 ++;
			} else {
				pusx = mx;
				pusy = my;
				pause1 = 0;
			}		
			
			if(pause1 > 15) {
				pause1 = -30;
			//	XTestFakeButtonEvent(display, 1, TRUE, CurrentTime);
			//	XTestFakeButtonEvent(display, 1, FALSE, CurrentTime);
			}

			printf("x => %d y => %d \n", mx, my);
			
			char *host1 = "172.18.107.208";
			char *dato1 = "/1";
			char *port1 = "5000"; 
			printf(" ser1234 ...\n");
			client(host1, dato1, port1);
			printf(" ser4321 ...\n");
		//	sleep(1);
		//	XTestFakeMotionEvent(display, -1, tmousex-200, tmousey-200, CurrentTime);
		//	XSync(display, 0);
		}
	}
        m_new_depth_frame = true;
    }

    bool getRGB(std::vector<uint8_t> &buffer) {
        Mutex::ScopedLock lock(m_rgb_mutex);
        if (!m_new_rgb_frame)
            return false;
        buffer.swap(m_buffer_video);
        m_new_rgb_frame = false;
        return true;
    }

    bool getDepth(std::vector<uint8_t> &buffer) {
        Mutex::ScopedLock lock(m_depth_mutex);
        if (!m_new_depth_frame)
            return false;
        buffer.swap(m_buffer_depth);
        m_new_depth_frame = false;
        return true;
    }

private:
    std::vector<uint8_t> m_buffer_depth;
    std::vector<uint8_t> m_buffer_video;
    std::vector<uint16_t> m_gamma;
    Mutex m_rgb_mutex;
    Mutex m_depth_mutex;
    bool m_new_rgb_frame;
    bool m_new_depth_frame;
};

Freenect::Freenect freenect;
MyFreenectDevice* device;

void *gl_threadfunc(void *arg){

    printf("GL thread 1 \n");

    while (1){}

    printf("GL thread 2\n");
    return NULL;
}

int main(int argc, char **argv) {
	printf("\n=== Kinect Mouse ===\n");

	if (argc == 2) {
		snstvty = atoi(argv[1]);
	} else {
		snstvty = 20000;
	}

//	mousemask(ALL_MOUSE_EVENTS, NULL);

//	display = XOpenDisplay(0);

	//root_window = DefaultRootWindow(display);

	//screenw = XDisplayWidth(display, SCREEN);
	//screenh = XDisplayHeight(display, SCREEN);
	screenw = 1920;
	screenh = 1280;

	screenw += 200;
	screenh += 200;

	device = &freenect.createDevice<MyFreenectDevice>(0);

	//freenect_set_log_level(f_ctx, FREENECT_LOG_DEBUG);
	
	device->startVideo();
	device->startDepth();
	gl_threadfunc(NULL);
	device->stopVideo();
	device->stopDepth();
	return 0;
}
