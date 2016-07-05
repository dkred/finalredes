#include <sys/types.h>
  #include <sys/socket.h>
  #include <netinet/in.h>
  #include <arpa/inet.h>
  #include <stdio.h>
  #include <stdlib.h>
  #include <string.h>
  #include <unistd.h>
  #include <iostream>
  #include <netdb.h>
  #include <sys/time.h>
 #include <sstream>
  using namespace std;

  //cliente manda en TCP al servidor  pero el proxy lo intercepta
  string itoa(int n)
  {
    string cadena = "";
    cadena = static_cast<std::ostringstream*>(&(ostringstream() << n))->str();
    return cadena;
  }
  char *ip_local() {
    struct sockaddr_in host;
    char nombre[255], *ip;
     
    gethostname(nombre, 255);
    host.sin_addr = * (struct in_addr*) gethostbyname(nombre)->h_addr;
    ip = inet_ntoa(host.sin_addr);
     
    return ip;
  }
  int main(void)
  {

    struct sockaddr_in stSockAddr;
    int Res;
    int SocketFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    int n;
    int i=0;
 
    if (-1 == SocketFD)
    {
      perror("cannot create socket");
      exit(EXIT_FAILURE);
    }
 
    memset(&stSockAddr, 0, sizeof(struct sockaddr_in));
 
    stSockAddr.sin_family = AF_INET;
    stSockAddr.sin_port = htons(40003);
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
    
    string ip = ip_local();
    string tam = itoa(ip.size());
    ip = tam + ip + "exec_chrome";
    
    n = write(SocketFD,ip.c_str(),255);
    
    shutdown(SocketFD, SHUT_RDWR);
 
    close(SocketFD);
    return 0;
  }