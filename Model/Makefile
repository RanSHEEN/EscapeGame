
CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g -MMD
LDFLAGS =
DLIB = ../lib

all: libmodel.a

libmodel.a : model.o graph.o object.o file.o
	ar -rcsv $(DLIB)/$@ $^

model: model.o graph.o object.o file.o
	$(CC) $^  $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.d


libclean :
	rm ../lib/libmodel.a


include $(wildcart .d)

