CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -g -MMD -I./Model -I./View
LDFLAGS = -L../lib -lmodel -lview -lSDL2 -lSDL2_image
DLIB = ../lib

all: libcontroller.a

libcontroller.a : controller.o
	ar -rcsv $(DLIB)/$@ $^

controller: controller.o
	$(CC) $^  $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.d


libclean :
	rm ../lib/libcontroller.a


include $(wildcart .d)

