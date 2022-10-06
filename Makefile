CC=g++
NAME=cvrptw
CC_FLAGS=-o $(NAME)

.PHONY: test clean

cvrptw: main.cpp
	$(CC) $(CC_FLAGS) main.cpp
clean:
	rm -f main.o $(NAME)
