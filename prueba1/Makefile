CC = g++
TEST= test1.cpp

CFLAGS= -g -Wall `pkg-config --cflags libfreenect` #-lopengl32 -lglut32
LIBS = `pkg-config --libs libfreenect` -lGL -lGLU -lglut -pthread

#CFLAGS=-fPIC -g -Wall `pkg-config --cflags opencv`
#LIBS = `pkg-config --libs opencv`
INCLUDE = -I/usr/local/include/libfreenect
FREE_LIBS = -L/usr/local/lib -lfreenect


OUTPUT = test1

all: $(OUTPUT)

test1: $(TEST)
	$(CC) $(INCLUDE) -o test1 $(TEST) $(CFLAGS)  $(LIBS) $(FREE_LIBS)
	 
	
clean:
	rm -f $(OUTPUT)

