CC=g++
NAME=cvrptw
CC_FLAGS=-o $(NAME) -Wall -Wextra -Wpedantic
DEPS=src/Problem.cpp src/Depot.cpp

.PHONY: test clean

cvrptw: src/main.cpp
	$(CC) $(CC_FLAGS) src/main.cpp $(DEPS)
clean:
	rm -f main.o $(NAME)
