CFLAGS=-Wall -Wextra -g -std=c99
MEM_CHECK=valgrind
SOURCE_DIR=../src
OBJS=test_bstree.o test_manipulation.o test_traversal.o
TEST_PROG=test_bstree.out

memo: compile
	$(MEM_CHECK) ./$(TEST_PROG)
	echo $$?

test: compile
	./$(TEST_PROG)
	echo $$?

compile: $(OBJS)
	$(CC) $(CFLAGS) -o $(TEST_PROG) *.o $(SOURCE_DIR)/*.o \
		-I../include/algo
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -I../include/algo