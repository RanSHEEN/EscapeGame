CC = gcc
CFLAGS = -g -Wall -Wextra
LDFLAGS = 
LIB = 


all: personnage

personnage: main.o personnage.o
	$(CC) $(LDFLAGS) $^ $(LIB) -o $@ -g

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o personnage *~


