# Echo - A Simple Echo Server
This is an implementation of an echo client and server.

To run an echo server:
- cd to this directory
- run echod on one machine (or in one terminal)
- run ./echo [IP address] 23457 on another machine (or in another terminal)
	where [IP address] is the IP address of the machine running the server
	and 23457 is the port number (server uses 23457)
- type text in the client
- the server will display the text and send it back to the client
- to exit, kill the client with ctrl-c
- kill the server with ctrl-c
