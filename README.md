# RepeatClientServer

Simple client/server program written in C to practice using sockets. The server here just echos what the client
sends back to the client.

## Local setup

We'll be running our servers in a docker container running Ubuntu 18.04 based on the OMSCS 6200 container
[found here](https://hub.docker.com/r/fsgeek/omscs6200). To get started:

#### 1) Pull the image
In the current directory run `make docker_pull` (make sure you have docker installed and running)

#### 2) Start the container
From here we'll want start the docker container, do this by running `make docker_run` in a terminal window.
Now since we'll be running both the client and server we'll want to open another terminal window and
run `make docker_connet`. What this does is first initializes and starts the docker container with the `docker_run`
command and then we connect to that already running container in our other terminal window with the `docker_connect`
command.

#### 3) Compile the client and server
There are a few different options here. We can either compile both sets of client/servers, only the new, or only the
old. No matter what you choose, you'll want to run these compile commands from within the docker container.

1) To compile all you will run `make` which will give you the executables in the table below.
2) To compile only the new version run `make new` which will give you only the executables for the new files
3) To compile only the old version run `make old` which will give you only the executables for the old filesa

| File Name    | Executable Generated |
|--------------|----------------------|
| TCPclient.c  | client               |
| TCPserver.c  | server               |
| new_client.c | new_client           |
| new_server.c | new_server           |

#### 4) Run your client and server!
Start the server first, for the new server `./new_server`, for the old server `./server` in one of the terminal windows.
Then start the client, for the new client `./new_client`, for the old client `./client`
(Note: make sure you run the new pair or the old pair, as of now new/old can't talk to each other)

## TCPclient/TCPserver

Built using the "old" way to manually set the values for the `sockaddr_in` struct from 
(Socket Programming Tutorial in C for Beginners)(https://www.youtube.com/watch?v=LtXEMwSG5-8&t=3s)

## new_server/new_client

Built on the more modern way of building the `sockaddr_in` struct, following
[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/multi/syscalls.html#getaddrinfo)
