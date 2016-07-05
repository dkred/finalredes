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
#define SERVER_PORT 40007
#define BUFFER_LEN 1024
using namespace std; 
//servidor recibe en UDP la peticion y este lo convierte en TCP 
int main(void)
{
     char buffer[256];
     int sockfd; /* descriptor para el socket */
     struct sockaddr_in my_addr; /* direccion IP y numero de puerto local */
     struct sockaddr_in their_addr; /* direccion IP y numero de puerto del cliente */
     /* addr_len contendra el tamanio de la estructura sockadd_in y numbytes el
     * numero de bytes recibidos
     */
     int addr_len, numbytes;
     char buf[BUFFER_LEN]; /* Buffer de recepción */
     
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
    
     struct timeval comienzo;
     bzero(buffer,256);

     if ((numbytes=recvfrom(sockfd, buf, BUFFER_LEN, 0, (struct sockaddr *)&their_addr, (socklen_t *)&addr_len)) == -1) {
     perror("recvfrom");
     exit(1);
     }
     gettimeofday(&comienzo, NULL);
     int time_difference  = comienzo.tv_usec - atoi(buf);
     //cout <<"fin:  "<< comienzo.tv_sec <<"    "<<(float)comienzo.tv_usec/1000000<<endl;
     cout << time_difference << endl;
     
     /* cerramos descriptor del socket */
     close(sockfd);

     return 0;
}