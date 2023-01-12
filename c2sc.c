/*TRANSFER A FILE FROM CLIENT TO SERVER IN INTERNET DOMAIN*/


/*client using tcp protocol*/


#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include  "inet.h"
#define SERV_TCP_PORT 6000
#define SERV_HOST_ADDR "192.43.235.6"

main(argv)

char *argv[];
{

	int sockfd;

  	struct sockaddr_in serv_addr;
  
   	char *pname=argv[0];

/*fill in the structure "serv_addr" with the address of the server*/

	bzero((char *)&serv_addr,sizeof(serv_addr));

	serv_addr.sin_family=AF_INET;

	serv_addr.sin_addr.s_addr=inet_addr(SERV_HOST_ADDR);

	serv_addr.sin_port=htons(SERV_TCP_PORT);


	if((sockfd=socket(AF_INET,SOCK_STREAM,0))<0)   /*OPEN A TCP SOCKET*/

  	err_sys("CLIENT:CAN'T OPEN STREAM SOCKET");

/*connection to the server*/

	if(connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
  	err_sys("client:cant connect to the server");

	str_cli(stdin,sockfd);   /*do it all*/
 	close(sockfd);
	exit(0);

}

/*Read the contents of the FILE *fp,write each line to the stream socket(to the server process)*/

#include <stdio.h>
#define MAXLINE 512

str_cli(fp,sockfd)
register FILE *fp;
register int sockfd;
{
  	int n;
   	char sendline[MAXLINE],recvline[MAXLINE+1];
 	while(fgets(sendline,MAXLINE,fp)!= NULL)
	{
 		n=strlen(sendline);
 		if(written(sockfd,sendline,n)!= n)
 		err_sys("str_cli:written error on socket");
    	}
 	if(ferror(fp))
 	   err_sys("str_cli:error reading file"); 
}


/*Write "n" bytes to a descriptor*/

int
written(fd,ptr,nbytes)
register int fd;
register char *ptr;
register int nbytes;
{
	int nleft,nwritten;

	nleft=nbytes;
	while(nleft>0)
	{    
		nwritten=write(fd,ptr,nleft);
   		if(nwritten<=0)
   		return(nwritten);   /*error*/
   		nleft-=nwritten;
   		ptr+=nwritten;
	}
	return(nbytes-nleft);

}  
