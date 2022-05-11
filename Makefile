CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g -MMD -I./View -I./Model -I./Controller
LDFLAGS= -L./lib -lAll -lSDL2 -lSDL2_image
LDFLAGS_UT= -lcmocka

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

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean: distclean
	rm -f *.o *.d
	rm -f main

distclean :
	rm -f ./lib/*.a

include $(wildcart .d)