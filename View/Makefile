<<<<<<< HEAD
.PHONY = all clean

CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g
LINKERFLAG = -lm -no-pie -fno-stack-protector
LDFLAGS= -lSDL2

all: main 

main: main.o window.o renderer.o
	$(CC) $^ -o $@ $(LDFLAGS)
	g++ render.c -lSDL2 -lGL
=======
CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g -MMD
LDFLAGS= -lSDL2 -lSDL2_image
DLIB = ../lib

all: libview.a

libview.a : main_view.o
	ar -rv $(DLIB)/$@ $^

main_view: main_view.o
	$(CC) $^  $(LDFLAGS) -o $@
>>>>>>> be348f2db29d26e4d6189f5ad4b0ae1d216506a8

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
<<<<<<< HEAD
	rm -f *.o

=======
	rm -f *.o *.d


libclean :
	rm ../lib/libview.a

include $(wildcart .d)
>>>>>>> be348f2db29d26e4d6189f5ad4b0ae1d216506a8
