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

ifeq ($(detected_OS),Windows)
	CONFIG=Makefile_win
else
	CONFIG=Makefile
endif

.PHONY: all dynamic memo test compile_debug trim clean

all: dynamic

dynamic:
	$(MAKE) -C $(SOURCE_DIR) -f $(CONFIG) dynamic

static:
	$(MAKE) -C $(SOURCE_DIR) -f $(CONFIG) static

memo: trim
	$(MAKE) -C $(SOURCE_DIR) -f $(CONFIG) compile_debug
	$(MAKE) -C $(TEST_DIR) -f $(CONFIG) memo

test: trim
	$(MAKE) -C $(SOURCE_DIR) -f $(CONFIG) compile_debug
	$(MAKE) -C $(TEST_DIR) -f $(CONFIG) test

compile:
	$(MAKE) -C $(SOURCE_DIR) -f $(CONFIG) compile

trim:
	$(MAKE) -C $(SOURCE_DIR) -f $(CONFIG) trim
	$(MAKE) -C $(TEST_DIR) -f $(CONFIG) trim

clean:
	$(MAKE) -C $(SOURCE_DIR) -f $(CONFIG) clean
	$(MAKE) -C $(TEST_DIR) -f $(CONFIG) clean
