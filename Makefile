CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g -MMD -I./View -I./Model -I./Controller
LDFLAGS= -L./lib -lAll -lSDL2 -lSDL2_image
LDFLAGS_UT= -L./lib -lmodel -lview -lcontroller -lSDL2 -lSDL2_image

all: make_model make_view make_controller main

make_model:
	make -C ./Model
	make -C ./Model clean

make_view:
	make -C ./View
	make -C ./View clean

make_controller:
	make -C ./Controller
	make -C ./Controller clean

main: main.o
	ar -rcT ./lib/libAll.a ./lib/libmodel.a ./lib/libview.a ./lib/libcontroller.a
	$(CC) $^  $(LDFLAGS) -o $@

Test: UTest.o
	$(CC) $^  $(LDFLAGS_UT) -lcmocka -o $@

Test_Edge: UTest_Edge.o
	$(CC) $^  $(LDFLAGS_UT) -lcmocka -o $@

Test_graph: UTest_graph.o
	$(CC) $^  $(LDFLAGS_UT) -lcmocka -o $@

Test_State: UTest_State.o
	$(CC) $^  $(LDFLAGS_UT) -lcmocka -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean: distclean clean_exc
	rm -f *.o *.d
	rm -f main

clean_exc:
	rm -f main
	rm -f Test*

distclean :
	rm -f ./lib/*.a

include $(wildcart .d)