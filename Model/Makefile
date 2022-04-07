CC = gcc
<<<<<<< HEAD
CFLAGS = -g -Wall -Wextra
LDFLAGS = 
LIB = 


all: personnage

personnage: main.o personnage.o
	$(CC) $(LDFLAGS) $^ $(LIB) -o $@ -g
=======
CFLAGS = -Wall -Wextra -pedantic-errors -g -MMD
LDFLAGS =
DLIB = ../lib

all: libmodel.a

libmodel.a : main_model.o object.o personnage.o
	ar -rv $(DLIB)/$@ $^

main_model: main_model.o object.o personnage.o
	$(CC) $^  $(LDFLAGS) -o $@
>>>>>>> be348f2db29d26e4d6189f5ad4b0ae1d216506a8

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
<<<<<<< HEAD
	rm -f *.o personnage *~


=======
	rm -f *.o *.d


libclean :
	rm ../lib/libmodel.a


include $(wildcart .d)

>>>>>>> be348f2db29d26e4d6189f5ad4b0ae1d216506a8
