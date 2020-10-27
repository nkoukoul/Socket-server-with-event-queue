#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include "project.h"
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/signal.h>
#include <netinet/tcp.h>



#define check(expr) if (!(expr)) { perror(#expr); kill(0, SIGTERM); }

namespace tcp_server{
  // function prototypes
  int HandleInput(int fd);
  int HandleOutput(int fd);

  int socket_timeout = 3000;

  int target[FD_SETSIZE];

  void enable_keepalive(int sock) {
    int yes = 1;
    check(setsockopt(sock, SOL_SOCKET, SO_KEEPALIVE, &yes, sizeof(int)) != -1);

    int idle = 1;
    check(setsockopt(sock, IPPROTO_TCP, TCP_KEEPIDLE, &idle, sizeof(int)) != -1);

    int interval = 1;
    check(setsockopt(sock, IPPROTO_TCP, TCP_KEEPINTVL, &interval, sizeof(int)) != -1);

    int maxpkt = 10;
    check(setsockopt(sock, IPPROTO_TCP, TCP_KEEPCNT, &maxpkt, sizeof(int)) != -1);
  }

  void * SocketServerServe(void * args){
    int sock,fd;
    socklen_t client_len;
    struct sockaddr_in server,client; 
    fd_set active_set, read_set, write_set;
    std::cout << "FD_SETSIZE = " << FD_SETSIZE << "\n";
    for (fd = 0; fd < FD_SETSIZE; fd++) {
      target[fd] = 0;
    }
    
    sock = socket(AF_INET, SOCK_STREAM, PF_UNSPEC);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(8955);

    int my_error = 0;
    if (my_error = bind(sock, (struct sockaddr *) &server, sizeof(server))<0){
      std::cout << "bind failed with error "<< my_error <<"\n";
      exit(1);
    }
    
    listen(sock, 5);
    
    FD_ZERO(&active_set);
    FD_SET(sock, &active_set);
    std::cout << "server ready\n";
    struct timeval timeout;
    timeout.tv_sec  = socket_timeout / 1000;
    timeout.tv_usec = socket_timeout % 1000;
    while (true){
      memcpy(&read_set, &active_set, sizeof active_set);
      memcpy(&write_set, &active_set, sizeof active_set);
      //select(FD_SETSIZE, &read_set, NULL, NULL, &timeout);
      select(FD_SETSIZE, &read_set, &write_set, NULL, NULL);
      /* Did we get a connection request? If so, we accept it,
	 add the new descriptor into the read set, choose a random
	 number for this client
      */
      if (FD_ISSET(sock, &read_set)){
	client_len = sizeof client;
	fd = accept(sock, (struct sockaddr *)&client, &client_len);
	//enable_keepalive(fd);
	FD_SET(fd, &active_set);
	std::cout << "new connection on fd " << fd << "\n";
	target[fd] = 1 + rand()%1000;
      }
	

      /* Now we must check eac descriptor in the read set in turn.
	 For each one which is ready we process the client request
      */
      for (fd = 0; fd < FD_SETSIZE; fd++){
	if (fd == sock) continue; // Omit the rendezvous descriptor
	if (target[fd] == 0) continue; // Empty table entry
	if (FD_ISSET(fd, &read_set)){
	  if (HandleInput(fd)<0){
	    /* If the client has closed its end of the conection,
	       or if the dialogue with the client is complete, we
	       close our end, and remove the descriptor from the
	       read set
	    */
	    close(fd);
	    FD_CLR(fd, &active_set);
	    target[fd] = 0;
	    std::cout << "on read closing fd= "<< fd << "\n";
	  }
	}
	if (FD_ISSET(fd, &write_set)){
	  if (HandleOutput(fd)<0){
	    /* If the client has closed its end of the conection,
	       or if the dialogue with the client is complete, we
	       close our end, and remove the descriptor from the
	       read set
	    */
	    close(fd);
	    FD_CLR(fd, &active_set);
	    target[fd] = 0;
	    std::cout << "on write closing fd= "<< fd << "\n";
	  }
	}	
      }
    }    
  }

  int HandleInput(int fd){
    char inbuffer[MAXBUF], *p = inbuffer;
    // Read data from client
    int bytes_read = read(fd, inbuffer, MAXBUF);
    if ( bytes_read <= 0 )
      return -1; //client closed connection
    std::string input_data, request_type, uri;
    for (int i = 0; i < bytes_read; i++) input_data += inbuffer[i];
    std::cout << "received data: " << input_data << "\n" << "on fd= "
	      << fd << "\n";
    //std::stringstream ss(input_data);
    //ss >> request_type >> uri;
    //std::cout << "request: " << request_type << " for uri "<< uri << "\n";
    //std::string response = "hello there";
    //if (write(fd,response.c_str(),response.size()) < 0 )
    //return -1;
    return 1;
  }

  int HandleOutput(int fd){
    char outbuffer[MAXBUF], *p = outbuffer;
    std::string response = "hello there";
    if (write(fd,response.c_str(), response.size()) < 0 )
      return -1;
    return 1;
  }

}
#endif // TCP_SERVER
