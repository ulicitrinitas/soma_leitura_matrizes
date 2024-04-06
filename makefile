TARGET=os_proj
CC=gcc
PTHREAD=-pthread
CFLAGS=-Wall -g $(PTHREAD) -pipe
LD=gcc
LDFLAGS=$(PTHREAD) -static
OBJS=main.o
BUILD_DIR=build
T=4
n=3

all: build $(OBJS)
	$(LD) -o $(BUILD_DIR)/$(TARGET) $(BUILD_DIR)/$(OBJS) $(LDFLAGS)

main.o: src/main.c
	$(CC) $(CFLAGS) -c src/main.c -o $(BUILD_DIR)/main.o

clean:
	rm -rf $(BUILD_DIR)

run:
	$(BUILD_DIR)/$(TARGET) $(T) $(n) arqA.dat arqB.dat arqC.dat arqD.dat arqE.dat

build:
	mkdir -p $(BUILD_DIR)
