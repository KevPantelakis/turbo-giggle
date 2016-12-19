# Auteur :	Philippe Proulx
# Date :	19 février 2013
CC=gcc
CFLAGS=-m32 -gdwarf-2 -Wall
RM=rm -f
TARGET=tp3
OBJECTS=tp3.o filter.o

.PHONY : clean

$(TARGET) : $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

tp3.o : tp3.c $(HEADERS)
	$(CC) $(CFLAGS) -c -o $@ $<
	
filter.o : filter.s $(HEADERS)
	$(CC) $(CFLAGS) -xassembler-with-cpp -c -o $@ $<

clean :
	$(RM) *.o $(TARGET)
