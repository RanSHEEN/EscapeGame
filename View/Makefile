CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g -MMD
LDFLAGS= -lSDL2 -lSDL2_image
DLIB = ../lib

all: libview.a

libview.a : main_view.o
	ar -rv $(DLIB)/$@ $^

main_view: main_view.o Launch_Game.o Launch_menu.o
	$(CC) $^  $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f *.o *.d


libclean :
	rm ../lib/libview.a

include $(wildcart .d)