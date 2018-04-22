CC=gcc
MEM_CHECK=valgrind
RM=rm
RMFLAG=-rf
TARGET=test_bstree.out

all: run

check: compile
	$(MEM_CHECK) ./$(TARGET)
	echo $$?

run: compile
	./$(TARGET)
	echo $$?

compile:
	$(CC) -Wall -g -o $(TARGET) test_bstree.c bstree.c bstiter.c bstnode.c -std=c99

clean:
	$(RM) $(RMFLAG) $(TARGET)