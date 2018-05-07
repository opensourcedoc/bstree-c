ifndef CFLAGS
	ifeq ($(TARGET),Debug)
		CFLAGS=-Wall -Wextra -g -std=c99
	else
		CFLAGS=-Wall -Wextra -O2 -std=c99
	endif
endif

MEM_CHECK=valgrind --quiet
SOURCE_DIR=../src
OBJS=test_bstree.o test_manipulation.o test_traversal.o
TEST_PROG=test_bstree.out

.PHONY: memo test compile trim clean

memo:
	$(MEM_CHECK) ./$(TEST_PROG)
	echo $$?

test:
	./$(TEST_PROG)
	echo $$?

compile: $(TEST_PROG)

$(TEST_PROG): $(OBJS)
	$(CC) $(CFLAGS) -o $(TEST_PROG) *.o $(SOURCE_DIR)/*.o -I../include

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I../include

trim:
	perl -lpi -e "s{\s+$$}{}g;" *

clean:
	$(RM) $(TEST_PROG) *.obj *.o
