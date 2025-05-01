# Makefile for sim.c
# This Makefile is designed to compile the sim.c program and manage its execution.


# compiler, flags
CC = gcc
CFLAGS = -Wall -O2

# source, target
SRC = sim.c
EXEC = sim

# default target: build executable
all: $(EXEC)

# compile sim.c into sim
$(EXEC): $(SRC)
	$(CC) $(CFLAGS) -o $(EXEC) $(SRC)

# run program
run: $(EXEC)
	./$(EXEC)

# test code
test: all
	bash test.sh

# clean up exec & output txt files
clean:
	rm -f $(EXEC)
	find . -maxdepth 1 -name "*.txt" ! -name "ReadMe.txt" -exec rm -f {} +

# clean & recompile
rebuild: clean all
