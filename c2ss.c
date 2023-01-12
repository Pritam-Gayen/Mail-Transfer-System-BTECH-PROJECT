/*TRANSFER A FILE FROM CLIENT TO SERVER IN INTERNET DOMAIN*/

/*server using tcp protocol*/


#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include "inet.h"

#define SERV_TCP_PORT 6000
#define SERV_HOST_ADDR "192.43.235.6"
char *pname;

main(argc,argv)
int argc;
char *argv[];
{
	int sockfd,newsockfd,clilen,childpid;
	struct sockaddr_in cli_addr,serv_addr;
	char *pname=argv[0];


/* open a tcp socket(an internet stream socket)*/

	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)   /*SOCKFD IS SOCKET DESCRIPTOR*/
           err_dump("server:can't open stream socket");

/* bind our local addresses so that client can send to us */

	bzero((char *)&serv_addr,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(SERV_TCP_PORT);

	if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
	   err_dump("server:can't bind local addressing");
	listen(sockfd,5);   /* 5 is the max value of backlog*/
	for(;;)
	{
                       /*wait for a connection from a client process*/
		clilen=sizeof(cli_addr);
		newsockfd=accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
		if(newsockfd<0)

		err_dump("server:accept error");

		if((childpid=fork())<0)

   		err_dump("server:fork error");

		else if(childpid==0)
		{                      /*child process*/

     			close(sockfd);                        /*close original socket*/

      			str_req(newsockfd);                  /*process the request*/
     
     			exit(0);

		}
       		close(newsockfd);
  	}

}

/*Read a stream socket one line at a time,return when the connection is terminated*/

#define MAXLINE 512
str_req (sockfd)
int sockfd;

{

    	int n;
    	char line[MAXLINE];
 	for(;;)
	{
             n=readline(sockfd,line,MAXLINE);
             if(n==0)
                 return;
	     else if(n<0)
                err_dump("str_echo:readline error");
  	}
}

/*Read a line from a descriptor.read the line one byte at a time,
looking for the new line.We store the newline in the buffer,
then follow it with a null.
We return the number of characters up to,but not including,the null.*/

int
readline(fd,ptr,maxlen)
register int fd;
register char *ptr;
register int maxlen;

{

   	int n,rc;
	char c;
	for(n=1;n<maxlen;n++)
	{
   		if((rc=read(fd,&c,1))==1)
		{
           
           		*ptr++=c;
            		if(c=='\n')
               		break;
  		}
		else if(rc==0)
		     {
          		if(n==1)
             		 return(0);  /*EOF,no data read*/
          		else
              		 break;
  		     }
		     else
       			return(-1);
	}
	*ptr=0;
	return(n);
}

