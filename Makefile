CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g -MMD -I./View -I./Model -I./Controller
LDFLAGS= -L./lib -lmodel -lview -lcontroller -lSDL2 -lSDL2_image -lcmocka

all: make_model make_view make_controller main

make_model:
	make -C ./Model
	make -C  ./Model clean

make_view:
	make -C ./View
	make -C  ./View clean

make_controller:
	make -C ./Controller
	make -C  ./Controller clean

main: main.o UTest.o UTest_graph.o
	$(CC) $^  $(LDFLAGS) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f *.o *.d
	rm main

distclean :
	rm -f ./lib/*.a



include $(wildcart .d)