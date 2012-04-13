CFLAGS = -ansi -pedantic -Wall -Werror -o3 -D_BSD_SOURCE -g

SOURCES = $(shell ls *.c)
OBJECTS = $(SOURCES:.c=.o)
LIBRARY = libih.a

$(LIBRARY): $(OBJECTS)
	ar rcs $(LIBRARY) *.o

clean:
	rm -f *~ .*~ *.o .etags $(LIBRARY)

stats:
	wc -l *.[h,c]
