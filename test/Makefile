CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g -MMD
LDFLAGS =-lSDL2 -lSDL2_image


main: main.o
	$(CC) $^  $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.d
include $(wildcart .d)
