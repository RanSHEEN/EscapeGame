.PHONY = all clean

CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g
LINKERFLAG = -lm -no-pie -fno-stack-protector
LDFLAGS= -lSDL2

all: main 

main: main.o 
	$(CC) $^ -o $@ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f *.o

