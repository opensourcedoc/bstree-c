CFLAGS=-Wall -Wextra -g -std=c99
OBJS=bstree.o bstnode.o bstiter.o

all: $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -I../include/algo