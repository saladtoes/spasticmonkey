CC = gcc
CFLAGS = -Wall
LDFLAGS = -lX11

TARGET = spasticmonkey
SRC = spasticmonkey.c 

all:
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f spasticmonkey

install: all 
	cp $(TARGET) /usr/local/bin/$(TARGET)
	chmod 755 /usr/local/bin/$(TARGET) 

uninstall:
	rm -f /usr/local/bin/$(TARGET)

