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

compile: crline
	$(CC) -Wall -g -o $(TARGET) test_bstree.c \
		test_manipulation.c test_traversal.c \
		bstree.c bstiter.c bstnode.c \
		-std=c99

crline:
	perl -pi -e "s{^[ \t]+$$}{}g;" *

clean:
	$(RM) $(RMFLAG) $(TARGET)
