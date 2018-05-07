ifeq ($(OS),Windows_NT)
    detected_OS := Windows
else
    detected_OS := $(shell sh -c 'uname -s 2>/dev/null || echo not')
endif

export detected_OS

CC=

ifndef CC
	ifeq ($(detected_OS),Windows)
		CC=cl
	else ifeq ($(detected_OS),Darwin)
		CC=clang
	else
		CC=gcc
	endif
endif

export CC

ifeq ($(detected_OS),Windows)
	RM=del
endif

export RM

ifndef TARGET
	TARGET=Release
endif

export TARGET

SOURCE_DIR=src
TEST_DIR=test

ifeq ($(CC),cl)
	OBJS := $(echo $(SOURCE_DIR)/*.obj $(TEST_DIR)/*.obj)
else
	OBJS := $(echo $(SOURCE_DIR)/*.o $(TEST_DIR)/*.o)
endif

.PHONY: all memo test compile trim clean

all: test

memo: compile
	$(MAKE) -C $(TEST_DIR) memo

test: compile
	$(MAKE) -C $(TEST_DIR) test

compile: trim $(OBJS)
	$(MAKE) -C $(SOURCE_DIR) compile
	$(MAKE) -C $(TEST_DIR) compile

trim:
	$(MAKE) -C $(SOURCE_DIR) trim
	$(MAKE) -C $(TEST_DIR) trim

clean:
	$(MAKE) -C $(SOURCE_DIR) clean
	$(MAKE) -C $(TEST_DIR) clean
