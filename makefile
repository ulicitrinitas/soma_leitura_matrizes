TARGET=os_proj
CC=gcc
PTHREAD=-pthread
CFLAGS=-Wall -g $(PTHREAD) -pipe
LD=gcc
LDFLAGS=$(PTHREAD) -static
OBJS=main.o
BUILD_DIR=build


