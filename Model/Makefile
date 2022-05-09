CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -g -MMD
LDFLAGS =
DLIB = ../lib

all: libmodel.a

libmodel.a : object.o personnage.o graph.o
	ar -rv $(DLIB)/$@ $^

model: object.o personnage.o graph.o
	$(CC) $^  $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.d


libclean :
	rm ../lib/libmodel.a


include $(wildcart .d)

