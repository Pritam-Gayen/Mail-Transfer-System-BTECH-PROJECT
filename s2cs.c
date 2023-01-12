/*ESTABLISHMENT OF CONNECTION AND TRANSFER OF CONTENT OF THE FILE FROM SERVER TO CLIENT(INTERNET DOMAIN)*/

/*A filename is taken by the client program in the command line argument.client process sends this filename to the server
 process through the socket.server process reads the filename from the socket and opens that file,and sends the content
 of the file to the client process through socket.client reads it from the socket and prints it to the output.*/

/*server code*/

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>
#include "unix.h"    

#define NAME "SOCKET"
main()
{
  	int sock,msgsock,rval,fd,n;
  	struct sockaddr_in serv_addr;
  	char buff[1024];

/*open a internet domain stream socket*/
	if((sock=socket(AF_INET,SOCK_STREAM,0))<0)
 		err_dump("server:cant open stream socket");

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);  /*32 bit netid/hosted*/
	serv_addr.sin_port=htons(SERV_TCP_PORT); /* 16 bit port id*/

	if(bind(sockfd,(struct sockaddr*)&serv_addr,sizeof(struct sockaddr_in))<0)
    		err_dump("server:cant bind local address");
	listen(sockfd,5);

	for(;;)
  	{
  		msgsock=accept(sock,0,0);

  		if(msgsock==-1)
   			err_dump("accept error");
  		else 
			do
			{
           			bzero(buf,sizeof(buf));
           			if((rval=read(msgsock,buf,1024))<0)
              				err_dump("error in reading message");
           			else if(rval==0)
              				print("ending connection");
           			     else
          			     { 
						print("-->%s\n".buf);
             					fd=open(buf,0);
            					bzero(buf,sizeof(buf));
            					while((n=read(fd,buf,1024))>0)
               					{
                 					write(msgsock,buf,n);
               					}  
               
                				print("ending connection\n");
                 				if(n<0)
                   					err_dump("error");
          			     }
        		}while(rval>0);
      		close(msgsock);
     }
     close(sock);
     unlink(NAME);
}

