
  #include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include <iostream>
  #include <sys/time.h>
  #include <sstream>
  using namespace std;
  char buffer[256];
  void fun()
  {
    int socketfdTCP;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    struct sockaddr_in their_addr; 
    struct hostent *he; 
    //struct sockaddr_inn stSockAddr;

  }
  void  funcion_client()
  {
     int sockfd; 
     struct sockaddr_in their_addr; 
     struct hostent *he; 
     int numbytes; 
     
     if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
     perror("socket");
     exit(1);
     }
     their_addr.sin_family = AF_INET; 
     their_addr.sin_port = htons(40000);
     
     inet_pton(AF_INET, "127.0.0.1", &their_addr.sin_addr);
     bzero(&(their_addr.sin_zero), 8); 
     
     if ((numbytes=sendto(sockfd,buffer,256,0,(struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) {
     perror("sendto");
     exit(1);
     }
     //printf("enviados %d bytes hacia %s\n",numbytes,inet_ntoa(their_addr.sin_addr));
     
     close(sockfd);
  }
  
  void funcion_server()
  {
    struct sockaddr_in stSockAddr;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    //int SocketFD = socket(AF_INET, SOCK_DGRAM, 0);
    int n;
 
    if(-1 == SocketFD)
    {
      perror("can not create socket");
      exit(EXIT_FAILURE);
    }
 
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
 
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(40003);
    stSockAddr.sin_addr.s_addr = INADDR_ANY;
 
    if(-1 == bind(SocketFD,(const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
      perror("error bind failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
 
    if(-1 == listen(SocketFD, 10))
    {
      perror("error listen failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
 
      int ConnectFD = accept(SocketFD, NULL, NULL);
 
      if(0 > ConnectFD)
      {
        perror("error accept failed");
        close(SocketFD);
        exit(EXIT_FAILURE);
      }
 
     bzero(buffer,256);
     n = read(ConnectFD,buffer,255);
     
     cout << buffer << SocketFD<<endl;
     if (n < 0) perror("ERROR reading from socket");
     /* perform read write operations ... */
      shutdown(ConnectFD, SHUT_RDWR); 
      close(ConnectFD);
      close(SocketFD);
  }
  int main(void)
  {

      funcion_server();
      funcion_client(); 
    
    return 0;
  }
