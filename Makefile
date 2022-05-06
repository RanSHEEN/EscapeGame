CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g -MMD -I./View -I./Model -I./Controller
LDFLAGS= -L./lib -lmodel -lview -lcontroller -lSDL2 -lSDL2_image -lSDL2_mixer

all: make_model make_view make_controller main

make_model:
	make -C ./Model
	make -C ./Model clean

make_view:
	make -C ./View
	make -C ./View clean

make_controller:
	make -C ./Controller
	make -C  ./Controller clean

main: main.o
	$(CC) $^  $(LDFLAGS) -o $@

Test: UTest.o
	$(CC) $^  $(LDFLAGS) -o $@

Test_graph: UTest_graph.o
	$(CC) $^  $(LDFLAGS) -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean: distclean
	rm -f *.o *.d
	rm -f main

clean_exc:
	rm -f main
	rm -f Test
	rm -f Test_graph

distclean :
	rm -f ./lib/*.a

include $(wildcart .d)