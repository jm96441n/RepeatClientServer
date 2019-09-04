CC = gcc
ASAN_FLAGS = -fsanitize=address -fno-omit-frame-pointer -Wno-format-security
ASAN_LIBS = -static-libasan
CFLAGS := -Wall -Werror --std=gnu99 -g3
CONTAINER_NAME = 'repeat'

ARCH := $(shell uname)
ifneq ($(ARCH),Darwin)
  LDFLAGS +=  -lpthread
endif

# default is to build with address sanitizer enabled
all: client server new_client new_server

old: client server

new: new_client new_server

client: TCPclient.c
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $^ $(LDFLAGS)

server: TCPserver.c
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $^ $(LDFLAGS)

new_client: new_client.c
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $^ $(LDFLAGS)

new_server: new_server.c
	$(CC) -o $@ $(CFLAGS) $(ASAN_FLAGS) $^ $(LDFLAGS)


%.o : %.c
	$(CC) -c -o $@ $(CFLAGS) $(ASAN_FLAGS) $<

clean:
	rm -fr *.o client server

docker_pull:
	docker pull fsgeek/omscs6200

docker_run:
	docker run --name=$(CONTAINER_NAME) --rm -it -w /RepeatClientServer -v/$(PWD):/RepeatClientServer fsgeek/omscs6200 /bin/bash

docker_connect:
	docker exec -it $(CONTAINER_NAME) /bin/bash
