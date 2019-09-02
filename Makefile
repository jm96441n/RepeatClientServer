CC = gcc
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
ASAN_LIBS = -static-libasan
CFLAGS := -Wall -Werror --std=gnu99 -g3

ARCH := $(shell uname)
ifneq ($(ARCH),Darwin)
  LDFLAGS +=  -lpthread
endif

# default is to build with address sanitizer enabled
all: client server

client: TCPclient.c
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $^ $(LDFLAGS)

server: TCPserver.c
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $^ $(LDFLAGS)

%.o : %.c
	$(CC) -c -o $@ $(CFLAGS) $(ASAN_FLAGS) $<

clean:
	rm -fr *.o client server
