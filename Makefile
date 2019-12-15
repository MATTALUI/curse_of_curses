.DEFAULT_GOAL := all
all: input_exists
	@g++ -lncurses main.cpp -o curse-of-curses
input_exists:
	@touch main.cpp
curses: all
	@chmod 777 ./curse-of-curses
	@./curse-of-curses
