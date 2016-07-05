#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <iostream>
#include <sys/time.h>
#include <sstream>
#define SERVER_PORT 40000
#define BUFFER_LEN 1024
using namespace std; 
//servidor recibe en UDP la peticion y este lo convierte en TCP 
char buf[BUFFER_LEN]; 
void  funcion_client()
  {
    struct sockaddr_in stSockAddr;
    int Res;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_UDP);
    //int SocketFD = socket(AF_INET, SOCK_DGRAM, 0);
    int n;
 
    if (-1 == SocketFD)
    {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
 
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
 
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(40000);
    Res = inet_pton(AF_INET, "127.0.0.1", &stSockAddr.sin_addr);
 
    if (0 > Res)
    {
      perror("error: first parameter is not a valid address family");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
    else if (0 == Res)
    {
      perror("char string (second parameter does not contain valid ipaddress");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
 
    if (-1 == connect(SocketFD, (const struct sockaddr *)&stSockAddr, sizeof(struct sockaddr_in)))
    {
      perror("connect failed");
      close(SocketFD);
      exit(EXIT_FAILURE);
    }
   
    n = write(SocketFD,buf,18);
    /* perform read write operations ... */
 
    shutdown(SocketFD, SHUT_RDWR);
 
    close(SocketFD);
  }
 
  void funcion_server()
  {
     int sockfd; /* descriptor para el socket */
     struct sockaddr_in my_addr; /* direccion IP y numero de puerto local */
     struct sockaddr_in their_addr; /* direccion IP y numero de puerto del cliente */
     /* addr_len contendra el tamanio de la estructura sockadd_in y numbytes el
     * numero de bytes recibidos
     */
     int addr_len, numbytes;
     /* Buffer de recepción */
     
     /* se crea el socket */
     if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
     perror("socket");
     exit(1);
     }
     
     /* Se establece la estructura my_addr para luego llamar a bind() */
     my_addr.sin_family = AF_INET; /* usa host byte order */
     my_addr.sin_port = htons(SERVER_PORT); /* usa network byte order */
     my_addr.sin_addr.s_addr = INADDR_ANY; /* escuchamos en todas las IPs */
     bzero(&(my_addr.sin_zero), 8); /* rellena con ceros el resto de la estructura */
     
     /* Se le da un nombre al socket (se lo asocia al puerto e IPs) */
     
     if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
     perror("bind");
     exit(1);
     }
     
     /* Se reciben los datos (directamente, UDP no necesita conexión) */
     addr_len = sizeof(struct sockaddr);
    
     
     if ((numbytes=recvfrom(sockfd, buf, BUFFER_LEN, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
     perror("recvfrom");
     exit(1);
     }
     cout << buf<<endl;
     /* cerramos descriptor del socket */
     close(sockfd);
   
   }

   int main(void)
  {
    
      funcion_server();
      //funcion_client();
   
    return 0;
  }