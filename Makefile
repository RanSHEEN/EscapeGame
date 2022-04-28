CC = gcc
CFLAGS =-Wall -Wextra -pedantic-errors -g -MMD -I./View -I./Model
LDFLAGS= -L./lib -lmodel -lview -lSDL2 -lSDL2_image

all: make_model make_view main


make_model:
	make -C  ./Model
	make -C  ./Model clean

make_view:
	make -C ./View
	make -C ./View clean

main: main.o
	$(CC) $^  $(LDFLAGS) -o $@


%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@
	
clean:
	rm -f *.o *.d
	rm main

distclean :
	rm -f ./lib/*.a

include $(wildcart .d)
