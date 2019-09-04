# RepeatClientServer

Simple client/server program written in C to practice using sockets. The server here just echos what the client
sends back to the client.

## TCPclient/TCPserver

Built using the "old" way to manually set the values for the `sockaddr_in` struct from 
(Socket Programming Tutorial in C for Beginners)(https://www.youtube.com/watch?v=LtXEMwSG5-8&t=3s)

## new_server/new_client

Built on the more modern way of building the `sockaddr_in` struct, following
[Beej's Guide to Network Programming](https://beej.us/guide/bgnet/html/multi/syscalls.html#getaddrinfo)
