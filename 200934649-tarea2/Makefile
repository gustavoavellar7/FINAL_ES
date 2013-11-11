CC = gcc
FORK-WEBSERVER = fork-webserver.c

FLAGS = pthread

OUTPUT = stress-client fork-webserver

all: $(OUTPUT)

fork-webserver: $(FORK-WEBSERVER)	
	$(CC) -$(FLAGS) $(FORK-WEBSERVER) -o fork-webserver

	
stress-client: stress-client.c
	$(CC) -$(FLAGS) stress-client.c -o stress-client
	
clean:
	rm -f $(OUTPUT)
