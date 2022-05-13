
CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g -MMD
LDFLAGS =
DLIB = ../lib

all: libmodel.a

libmodel.a : model.o graph.o object.o file.o
	ar -rcsv $(DLIB)/$@ $^

model: model.o graph.o object.o file.o
	$(CC) $^  $(LDFLAGS) -o $@

get_coverage_infos:
	lcov --capture --directory . --output-file ../Tests/Coverage_Info/coverage.info
	genhtml ../Tests/Coverage_Info/coverage.info --output-directory ../Tests/Coverage_Info


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.d


libclean :
	rm ../lib/libmodel.a


include $(wildcart .d)

