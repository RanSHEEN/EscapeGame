CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -g -MMD
LDFLAGS = -L./lib -lmodel -lview -lSDL2 -lSDL2_image
DLIB = ../lib

all: libcontroller.a

libcontroller.a : main_controller.o  controller.o event.o
	ar -rv $(DLIB)/$@ $^

main_controller: main_controller.o controller.o event.o
	$(CC) $^  $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.d


libclean :
	rm ../lib/libcontroller.a


include $(wildcart .d)

