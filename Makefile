.DEFAULT_GOAL := all
all: input_exists
	g++ -lncurses main.cpp -o curse-of-curses
input_exists:
	touch main.cpp
curses: all
	chmod 777 ./curse-of-curses
	./curse-of-curses
debug: input_exists
	g++ -g -lncurses main.cpp -o curse-of-curses
	chmod 777 ./curse-of-curses
	sudo gdb -tui ./curse-of-curses
