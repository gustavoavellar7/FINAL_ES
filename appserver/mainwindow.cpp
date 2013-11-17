#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "qpainter.h"
#include "QtGui"
#include "stdio.h"
#include <QFileDialog>
#include <QString>
#include <iostream>
#include <fstream>
#include "unistd.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/Xutil.h>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    qApp->installEventFilter(this);
    ui->setupUi(this);
    //READ: Instanciar el Server de Char
    this->ChatServer = new Server();
    //READ: Definir al server de Chat, el LOG (textEdit)
    this->ChatServer->log = this->ui->textEdit;


}

MainWindow::~MainWindow()
{
    delete ui;
    //READ: Liberar el ChatServer
    delete this->ChatServer;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
  if (event->type() == QEvent::MouseMove)
  {
    //QMouseEvent *mouseEvent = static_cast<QMouseEvent*>(event);
    //statusBar()->showMessage(QString("hola Mouse move (%1,%2)").arg(mouseEvent->pos().x()).arg(mouseEvent->pos().y()));
    //qDebug() <<mouseEvent->pos();
    int x,y;
    x=QCursor::pos().rx();
    y=QCursor::pos().ry();
    qDebug() << QCursor::pos();
   // this->update();
   // QPixmap mypix (":/imagenes/camisa1.jpg");
   // ui->lproducto->setPixmap(mypix);
   // ui->lproducto->update();
    if(y > 530){
        if(x>0 && x<330){
            qDebug() << "vans";
            QPixmap mypix (":/imagenes/vans2.jpg");
            ui->lproducto->setPixmap(mypix);
            ui->lproducto->setFixedSize(270,270);
            QPixmap qrpix (":/imagenes/vansqr.png");
            ui->lqr->setPixmap(qrpix);
            ui->textdesc->clear();
            ui->textdesc->append(QString("Marca: Vans \nmodelo: hevc\ncolores: gris, negro , azul \ntallas disponibles: 8-11"));
        }else{
            if(x>330 && x<730){
                qDebug() << "adidas";
                QPixmap mypix (":/imagenes/adidas1.jpg");
                ui->lproducto->setPixmap(mypix);
                ui->lproducto->setFixedSize(450,270);
                QPixmap qrpix (":/imagenes/adidasqr.png");
                ui->lqr->setPixmap(qrpix);
                ui->textdesc->clear();
                ui->textdesc->append(QString("Marca: adidas \nmodelo: sdk \ncolores: blanco, negro , rojo \ntallas disponibles: 8-11"));

            }else{
                if(x>730 && x<1080){
                    qDebug() << "camisa1";
                    QPixmap mypix (":/imagenes/camisa1.jpg");
                    ui->lproducto->setPixmap(mypix);
                    ui->lproducto->setFixedSize(200,270);
                    QPixmap qrpix (":/imagenes/camisaqr.png");
                    ui->lqr->setPixmap(qrpix);
                    ui->textdesc->clear();
                    ui->textdesc->append(QString("Marca: Emerica \ncolores: rojo, azul , verde \ntallas disponibles: M,L,XL"));

                }else{
                    if(x>180 && x<1320){
                        qDebug() << "camisa2";
                        QPixmap mypix (":/imagenes/camisa21.jpg");
                        ui->lproducto->setPixmap(mypix);
                        ui->lproducto->setFixedSize(200,270);
                        QPixmap qrpix (":/imagenes/camisa2qr.png");
                        ui->lqr->setPixmap(qrpix);
                        ui->textdesc->clear();
                        ui->textdesc->append(QString("Marca: Element \ncolores: negro, azul , blanco \ntallas disponibles: M,L,XL"));

                    }else{

                    }
                }
            }
        }
    }else{
        if(x>1170){
            if(y<145){
                qDebug() << "tiposcamisas";
                QPixmap mypix (":/imagenes/tiposcamisas.jpg");
                ui->lproducto->setPixmap(mypix);
                ui->lproducto->setFixedSize(400,400);

                ui->lqr->clear();
                ui->textdesc->clear();
            }else{
                if(y>195 && y<250){
                    qDebug() << "tipostennis";
                    QPixmap mypix (":/imagenes/tiposadidas.jpg");
                    ui->lproducto->setPixmap(mypix);
                    ui->lproducto->setFixedSize(600,400);

                    ui->lqr->clear();
                    ui->textdesc->clear();
                }else{
                    if(y>300 && y<355){
                        qDebug() << "tiposjeans";
                        QPixmap mypix (":/imagenes/tiposjeans.jpg");
                        ui->lproducto->setPixmap(mypix);
                        ui->lproducto->setFixedSize(500,400);

                        ui->lqr->clear();
                        ui->textdesc->clear();
                    }
                }
            }
        }
    }
  }
  return false;
}




void moverMouse()
{
   /* qDebug() << "Hello from thread " << QThread::currentThread();

    qDebug()<<"estoy moviendo " << x<<" "<<y;

    qDebug()<<"estoy ya no";*/
    qDebug()<<"estoy adentro ";
   int sockfd,n;
   struct sockaddr_in servaddr,cliaddr;
   socklen_t len;
   char mesg[100];

   sockfd=socket(AF_INET,SOCK_DGRAM,0);

   bzero(&servaddr,sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
   servaddr.sin_port=htons(6000);
   bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
   for (;;)
   {
       len = sizeof(cliaddr);
       n = recvfrom(sockfd,mesg,100,0,(struct sockaddr *)&cliaddr,&len);
       //sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
       //qDebug()<<"-------------------------------------------------------\n";
       mesg[n] = 0;
       //qDebug()<<"Received the following:\n";
       //qDebug()<<mesg;
       //qDebug()<<"-------------------------------------------------------\n";
       QString temp;
       //printf("Name: %s\n", name.at(7));
       //QString::SectionFlag flag = QString::SectionSkipEmpty;
       temp = QString(mesg);
       int x,y;
       x=temp.split(" ")[2].toInt();
       y=temp.split(" ")[3].toInt();
       //qDebug() <<x<<" "<<y;
       Display *dpy;
       Window root_window;

       dpy = XOpenDisplay(0);
       root_window = XRootWindow(dpy, 0);
       XSelectInput(dpy, root_window, KeyReleaseMask);

       XWarpPointer(dpy, None, root_window, 0, 0, 1366, 768, x, y);

       XFlush(dpy);
       XCloseDisplay(dpy);
   }
}
bool serverOn;
void MainWindow::on_btnStart_clicked()
{

    //READ: Iniciar el server en el puerto 7777 o cualquiera que deseen
    // El metodo start recibe de parametro el puerto donde escuchar
    //this->ChatServer->start(5000);
    //int x =this->ChatServer->x;
    //int y=this->ChatServer->y;
    serverOn=true;
    QFuture<void> future = QtConcurrent::run(moverMouse);

   // qDebug() << "hello from GUI thread " << QThread::currentThread();
   // future.waitForFinished();
    //qDebug() << "hello from GUI thread " << QThread::currentThread();
    //while(serverOn){


      //  }
         //usleep(100000);

    /*this->setFocus();

    while(this->hasFocus()){
        this->ChatServer->busy=true;
        qDebug()<<"estoy moviendo " << this->ChatServer->x<<" "<<this->ChatServer->y;
        QCursor::setPos(this->ChatServer->x,this->ChatServer->y);
        this->ChatServer->busy=false;
        usleep(100000 );
    }*/
     /*   qDebug()<<"estoy adentro ";
       int sockfd,n;
       struct sockaddr_in servaddr,cliaddr;
       socklen_t len;
       char mesg[1000];

       sockfd=socket(AF_INET,SOCK_DGRAM,0);

       bzero(&servaddr,sizeof(servaddr));
       servaddr.sin_family = AF_INET;
       servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
       servaddr.sin_port=htons(6000);
       bind(sockfd,(struct sockaddr *)&servaddr,sizeof(servaddr));
       for (;;)
       {
          len = sizeof(cliaddr);
          n = recvfrom(sockfd,mesg,1000,0,(struct sockaddr *)&cliaddr,&len);
          //sendto(sockfd,mesg,n,0,(struct sockaddr *)&cliaddr,sizeof(cliaddr));
          qDebug()<<"-------------------------------------------------------\n";
          mesg[n] = 0;
          qDebug()<<"Received the following:\n";
          qDebug()<<mesg;
          qDebug()<<"-------------------------------------------------------\n";

       }*/
}

void MainWindow::on_btnStop_clicked()
{

    //READ:Detener el server
    serverOn=false;
    this->ChatServer->stop();
}

void MainWindow::on_btnQuit_clicked()
{
    //READ: Cerrar la ventana pero antes de eso, primero hacer un STOP
    //del server y luego cerrarse
    this->ChatServer->stop();
    this->close();




}

void MainWindow::modificarVentana(QString archivo){

    std::string s = archivo.toStdString();
    char *name=new char[s.size()+1];
    name[s.size()]=0;
    memcpy(name,s.c_str(),s.size());
    ifstream fe(name);
    char cadena[128];

    while(!fe.eof()) {
        //fe >> cadena;
        fe.getline(cadena, 128);
        QString string(cadena);

        cout << cadena << endl;
    }
}
