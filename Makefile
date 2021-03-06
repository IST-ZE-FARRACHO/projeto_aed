#
# Makefile for Park program
#

CC=gcc
TARGET=autopark
CFLAGS= -Wall -ansi -O3
LIBS= -lm

SRCFILES= main.c cars.c graph.c heap.c liberation.c LinkedList.c park_config.c restrictions.c spots.c time.c tools.c
INCFILES= defs.h cars.h graph.h heap.h liberation.h LinkedList.h park_config.h restrictions.h spots.h time.h tools.h
OBJFILES= main.o cars.o graph.o heap.o liberation.o LinkedList.o park_config.o restrictions.o spots.o time.o tools.o

default: $(TARGET)

$(TARGET): $(OBJFILES)
	$(CC) $(CFLAGS) $(SRCFILES) -o $(TARGET) $(LIBS)

clean:
	rm -f $(TARGET) $(OBJFILES) core.* #*

main.o: main.c time.h defs.h tools.h cars.h restrictions.h LinkedList.h park_config.h heap.h liberation.h spots.h

cars.o: client.c cars.h

graph.o: graph.c graph.h

heap.o: heap.c heap.h

liberation.o: liberation.c liberation.h

LinkedList.o: LinkedList.c LinkedList.h

park_config.o: park_config.c park_config.h

restrictions.o: restrictions.c restrictions.h

spots.o: spots.c spots.h

time.o: time.c time.h

tools.o: tools.c tools.h


