
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
  string itoa(int n)
  {
    string cadena = "";
    cadena = static_cast<std::ostringstream*>(&(std::ostringstream() << n))->str();
    return cadena;
  }
  void  funcion_client()
  {
     int sockfd; /* descriptor a usar con el socket */
     struct sockaddr_in their_addr; /* almacenara la direccion IP y numero de puerto del servidor */
     struct hostent *he; /* para obtener nombre del host */
     int numbytes; /* conteo de bytes a escribir */
     /* Creamos el socket */
     if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
     perror("socket");
     exit(1);
     }

     /* a donde mandar */
     their_addr.sin_family = AF_INET; /* usa host byte order */
     their_addr.sin_port = htons(40006); /* usa network byte order */
     //their_addr.sin_addr = 127.0.0.1;//*((struct in_addr *)he->h_addr);
     inet_pton(AF_INET, "127.0.0.1", &their_addr.sin_addr);
     bzero(&(their_addr.sin_zero), 8); /* pone en cero el resto */
     
     /* enviamos el mensaje */
     struct timeval comienzo;

       gettimeofday(&comienzo, NULL);
       int time_ = comienzo.tv_usec;
     if ((numbytes=sendto(sockfd,buffer,BUFFER_LEN,0,(struct sockaddr *)&their_addr, sizeof(struct sockaddr))) == -1) {
     perror("sendto");
     exit(1);
     }

     printf("enviados %d bytes hacia %s\n",numbytes,inet_ntoa(their_addr.sin_addr));
     /* cierro socket */
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
 
     struct timeval comienzo;
     bzero(buffer,256);
     n = read(ConnectFD,buffer,255);
     
     gettimeofday(&comienzo, NULL);
     int time_difference  = comienzo.tv_usec - atoi(buffer);
     //cout <<"fin:  "<< comienzo.tv_sec <<"    "<<(float)comienzo.tv_usec/1000000<<endl;
     cout << time_difference << endl;
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
