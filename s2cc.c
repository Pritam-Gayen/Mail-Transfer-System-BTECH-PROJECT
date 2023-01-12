/*ESTABLISHMENT OF CONNECTION AND TRANSFER OF CONTENT OF THE FILE FROM SERVER TO CLIENT(INTERNET DOMAIN)*/

/*A filename is taken by the client program in the command line argument.client process sends this filename to the server
 process through the socket.server process reads the filename from the socket and opens that file,and sends the content
 of the file to the client process through socket.client reads it from the socket and prints it to the output.*/


/* client code */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "unix.h" 

main(argv)
char *argv[];
{
  	int sock,c;
  	struct sockaddr_in serv_addr;
  	char buff[1024];

 	if((sock=socket(AF_INET,SOCK_STREAM,0))<0)   /*open internet domain stream socket*/
   		err_dump("server:cant open stream socket");
  	serv_addr.sun_family=AF_INET;
  	serv_addr.sin_addr.s_addr=inet_addr(SERV_HOST_ADDR);
  	serv_addr.sin_port=htons(SERV_TCP_PORT);
     
  	if(connect(sock,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in)),0)
   	{
     		close(sock);
     		err_dump("error in connecting");
   	}
  	while((c=read(sock,buff,sizeof(buff)))>0)
    		write(1,buff,c);
    	close(sock);
}
