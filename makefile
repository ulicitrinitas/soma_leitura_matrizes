TARGET=os_proj
CC=gcc
PTHREAD=-pthread
CFLAGS=-Wall -g $(PTHREAD) -pipe
LD=gcc
LDFLAGS=$(PTHREAD) -static
OBJS=main.o
BUILD_DIR=build

all: $(OBJS)
	$(LD) -o $(BUILD_DIR)/$(TARGET) $(OBJS) $(LDFLAGS)

clean:
	rm -rf $(BUILD_DIR)
