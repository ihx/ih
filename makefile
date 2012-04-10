CFLAGS = -ansi -pedantic -Wall -Werror -o3

SOURCES = $(shell ls *.c)
OBJECTS = $(SOURCES:.c=.o)
LIBRARY = libih.a

$(LIBRARY): $(OBJECTS)
	ar rcs $(LIBRARY) *.o

clean:
	rm -f *~ .*~ *.o $(LIBRARY)
