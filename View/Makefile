
CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g -MMD
LDFLAGS = -lSDL2 -lSDL2_image
DLIB = ../lib

all: libview.a

libview.a : main_view.o
	ar -rcsv $(DLIB)/$@ $^

view: main_view.o
	$(CC) $^  $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.d


libclean :
	rm ../lib/libview.a

include $(wildcart .d)
