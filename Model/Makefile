CC = gcc
CFLAGS = -Wall -Wextra -pedantic-errors -g -MMD
LDFLAGS =
DLIB = ../lib

all: libmodel.a

libmodel.a : main_model.o object.o personnage.o graph.o
	ar -rv $(DLIB)/$@ $^

main_model: main_model.o object.o personnage.o graph.o
	$(CC) $^  $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.d


libclean :
	rm ../lib/libmodel.a


include $(wildcart .d)

