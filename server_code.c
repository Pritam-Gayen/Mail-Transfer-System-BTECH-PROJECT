//server code//
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include "inet.h"
#define MAXLINE 512
#define SERV_TCP_PORT 6000
#define SERV_HOST_ADDR "192.43.235.6"
char *pname;

void main()
{
	const char *command1="mkdir pmail";
	const char *command2="mkdir pmail/log";
	const char *logfile="touch pmail/log/logfile.txt";
	
	system(command1);
	system(command2);
	system(logfile);
	runingserver();
	
}


runingserver()
{
	int sockfd,newsockfd,clilen,childpid;
	struct sockaddr_in cli_addr,serv_addr;
	

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

      			write2file();                /*process the request*/
 			processfile();    
     			

		}
       		close(newsockfd);
  	}

}

write2file()
{
	FILE	*fp,*fw;
	int	sockfd;
	struct sockaddr *pserv_addr;    /* ptr to appropriate sockaddr_XX structure */
	int	servlen;        /* actual sizeof{*pserv_addr) */
	int     n;
	char    sendline[MAXLINE], recvline[MAXLINE + 1];
	while (fgets(sendline, MAXLINE, fp) !=NULL) 
	{ 
		n = strlen(sendline);
		if (sendto(sockfd, sendline, n, 0, pserv_addr, servlen) != n) 
			err_dump("dg_cli: sendto error on socket");
/*
*Now read a message from the socket and write it to
*our standard output.
*/
		n = recvfrom(sockfd, recvline, MAXLINE, 0,(struct sockaddr *) 0, (int *) 0);
		if (n < 0)
			err_dump("dg_cli: recvfrom error"); recvline[n] = 0;        /* null terminate */ 
	fw=fopen("pmail/log/tempfile.txt","w");	
	fputs(recvline, fw);
	fclose(fw);
	}
	if(ferror(fp))
		err_dump("dg_cli: error reading file");
}

processfile()
{
	FILE *f,*tf,*fr=fopen("pmail/log/tempfile.txt","r");
	char ch,code,usrid[50],pwd[50],check,checkusrid[50],sendusr[50],coma='"',persent='%';
	int i,j,idcheck,encript,feedback,count,imc,smc;
	//copy usr details from incoming file to variables start
	code=fgetc(fr);
	ch=fgetc(fr);
	i=0;
	while((ch=fgetc(fr))!='\n')
	{
		usrid[i]=ch;
		i++;
	}
	usrid[i]='\0';
	ch=fgetc(fr);
	i=0;
	while((ch=fgetc(fr))!='\n')
	{
		pwd[i]=ch;
		i++;
	}
	pwd[i]='\0';
	//copy usr details from incoming file to variables end

	if(code=='0')// 0 for creat mail account
	{
		check=usrid[i];
		while(check!='\0')//check validity of userid
		{
			if(check==' ' || check=='@' || check=='!' || check=='#' || check=='$' || check=='%' || check=='^' || check=='&')
			{	break;	}
			check=usrid[i++];
		
		}
		if(check=='\0')
		{	
		
			f=fopen("pmail/log/logfile.txt","r");		
			ch=fgetc(f);
			while(ch!=EOF)
			{
				i=0;
				while(ch!=' ')
				{
					checkusrid[i]=ch;
					ch=fgetc(f);
					i++;
				}
				checkusrid[i]='\0';
				idcheck=strcmp(checkusrid,usrid);
				if(idcheck==0)
				{
					feedback=1;
					break;
				}
				while(ch!='\n')
					ch=fgetc(f);
				ch=fgetc(f);
			}
			if(ch==EOF)
			{
				fclose(f);
				i=0;
				while(pwd[i]!='\0')//encripting the password
				{
					encript=pwd[i];
					encript+=100;
					pwd[i]=encript;
					i++;
				}
				f=fopen("pmail/log/logfile.txt","a");//saving usrid & encripted password to log file
				fprintf(f,"%s %s\n",usrid,pwd);			
				fclose(f);
		
				f=fopen("tempo.c","w");//a temporary file for creating account
				fprintf(f,"#include<stdio.h>\n#include<stdio.h>\n#include<stdlib.h>\n#include<sys/types.h>\n#include<sys/stat.h>\n#include<fcntl.h>\nvoid main()\n{\nFILE *fp;");
				fprintf(f,"\nconst char *foldername=%cmkdir pmail/%s%c;",coma,usrid,coma);
				fprintf(f,"\nconst char *folderinbox=%cmkdir pmail/%s/inbox%c;",coma,usrid,coma);
				fprintf(f,"\nconst char *fileinbox=%ctouch pmail/%s/inbox.txt%c;",coma,usrid,coma);
				fprintf(f,"\nconst char *foldersentmail=%cmkdir pmail/%s/sentmail%c;",coma,usrid,coma);
				fprintf(f,"\nconst char *filesentmail=%ctouch pmail/%s/sentmail.txt%c;",coma,usrid,coma);
				fprintf(f,"\nconst char *filecount=%ctouch pmail/%s/count.txt%c;",coma,usrid,coma);
				fprintf(f,"\nsystem(foldername);\nsystem(fileinbox);\nsystem(filesentmail);\nsystem(filecount);\nsystem(folderinbox);\nsystem(foldersentmail);");
				fprintf(f,"\nfp=fopen(%cpmail/%s/count.txt%c,%ca%c);",coma,usrid,coma,coma,coma);
				fprintf(f,"\nfprintf(fp,%c0 0%c);",coma,coma);
				fprintf(f,"\nfclose(fp);\n}");
				fclose(f);
				system("gcc tempo.c");
				system("./a.out");
			
				system("rm tempo.c");//remove the temporary file
			}
		}
		else
		{
			feedback=1;
		}
		f=fopen("feedback.txt","w");
		if(feedback==0)//feedback chooses what will be the message for the client machine
			fprintf(f,"Your account created successfully.");
		if(feedback==1)
			fprintf(f,"This name allready exists, try another one...");
		fclose(f);
	}
	if(code=='1')// 1 for login in mail account
	{
		feedback=login(usrid,pwd);
		f=fopen("feedback.txt","w");
		if(feedback==1)
			fprintf(f,"bad username or password");	
		if(feedbach==0)
			fprintf(f,"loggedin successfully.");
		fclose(f);
	}
	if(code=='2')//2 for display inbox
	{
		feedback=login(usrid,pwd);
		if(feedback==0)
		{
			tf=fopen("tempo.c","w");
			fprintf(f,"#include<stdio.h>\n#include<stdio.h>\n#include<stdlib.h>\n#include<sys/types.h>\n#include<sys/stat.h>\n#include<fcntl.h>\nvoid main()\n{\nFILE *fp,*fb;");
			fprintf(f,"fp=fopen(%cpmail/%s/inbox.txt%c,%cr%c);\n",coma,usrid,coma,coma,coma);
			fprintf(f,"fb=fopen(%cfeedback.txt%c,%cw%c);",coma,coma,coma);
			fprintf(f,"while((ch=fgetc(fp))!=EOF){fprintf(fb,%c%c%c,coma,ch,coma);}\nch=EOF;\nfprintf(fb,%c%c%c,coma,ch,coma);\nfclose(fp);\nfclose(fb);\n}");
			fclose(tf);
			system("gcc tempo.c");
			system("./a.out");
		}
	}

	if(code=='3')//3 for display sentmail
	{
		feedback=login(usrid,pwd);
		if(feedback==0)
		{
			tf=fopen("tempo.c","w");
			fprintf(f,"#include<stdio.h>\n#include<stdio.h>\n#include<stdlib.h>\n#include<sys/types.h>\n#include<sys/stat.h>\n#include<fcntl.h>\nvoid main()\n{\nFILE *fp,*fb;");
			fprintf(f,"fp=fopen(%cpmail/%s/sentmail.txt%c,%cr%c);\n",coma,usrid,coma,coma,coma);
			fprintf(f,"fb=fopen(%cfeedback.txt%c,%cw%c);",coma,coma,coma);
			fprintf(f,"while((ch=fgetc(fp))!=EOF){fprintf(fb,%c%c%c,coma,ch,coma);}\nch=EOF;\nfprintf(fb,%c%c%c,coma,ch,coma);\nfclose(fp);\nfclose(fb);\n}");
			fclose(tf);
			system("gcc tempo.c");
			system("./a.out");
			system("rm tempo.c");
		}
	}
	if(code=='4')// 4 for compose mail
	{
		feedback=login(usrid,pwd);
		count=0;
		if(feedback==0)
		{
			i=0;
			while((ch=fgetc(fr))!='\n')
			{
				sendusr[i]=ch;
				i++;
			}
			fclose(fr);				
			tf=fopen("tempo.c","w");
			fprintf(tf,"#include<stdio.h>\n#include<stdio.h>\n#include<stdlib.h>\n#include<sys/types.h>\n#include<sys/stat.h>\n#include<fcntl.h>\nvoid main()\n{\nFILE *fi,*fs,*ftemp;");
			fprintf(tf,"ftemp=fopen(%cpmail/log/tempfile.txt%c,%cr%c);\n",coma,coma,coma,coma);
			fprintf(tf,"for(count=0;count<=4; )\n{if((ch=fgetc(ftemp))=='\n')\ncount++;}\n");
			fprintf(tf,"fi=fopen(%cpmail/%s/inbox/%d.txt%c,%cw%c);",coma,sendusr,imc,coma,coma,coma);
			fprintf(tf,"fs=fopen(%cpmail/%s/sentmail/%d.txt%c,%cw%c);",coma,usrid,smc,coma,coma,coma);
			fprintf(tf,"while((ch=fgetc(ftemp))!=EOF){\nfprintf(fi,%c%c%c,coma,ch,coma);\nfprintf(fs,%c%c%c,coma,ch,coma);\n}");
			fprintf("fclose(fi);\nfclose(fs);");
			fclose(tf);
			
		}
	}
	if(code=='5')// 5 for forword mail
	{
		feedback=login(usrid,pwd);
		if(feedback==0)
		{
			i=0;
			while((ch=fgetc(fr))!='\n')
			{
				sendusr[i]=ch;
				i++;
			}
			i=0;
			while((ch=fgetc(fr))!=EOF)
			{
				sendfile[i]=ch;
				i++;
			}
			fclose(fr);
			tf=fopen("tempo.c","w");
			fprintf(tf,"#include<stdio.h>\n#include<stdio.h>\n#include<stdlib.h>\n#include<sys/types.h>\n#include<sys/stat.h>\n#include<fcntl.h>\nvoid main()\n{\nFILE *old,*new1,*new2,fr;");
			fprintf(tf,"int i,j,mult,smc,imc;\n");
			fprintf(tf,"char inboxc[6],sentmailc[6],ch;\n");
			fprintf(tf,"old=fopen(%cpmail/%s/inbox/%s.txt%c,%cr%c);\n",coma,usrid,sendfile,coma,coma,coma);
			fprintf(tf,"fr=fopen(%cpmail/%s/count.txt%c,%cr%c);\n",coma,usrid,coma,coma,coma);
			fprintf(tf,"i=0;\nwhile((ch=fgetc(fr))!=' '){ inboxc[i]=ch; i++; }\n inboxc[i]='\0';");
			fprintf(tf,"i=0;\nwhile((ch=fgetc(fr))!='\n'){ sentmailc[i]=ch; i++; }\n sentmailc[i]='\0';");
			fprintf(tf,"i=strlen(sentmailc);\nfor(mult=1,smc=0;i>0;i--){ j=sentmailc[i]; j=j-48; smc=smc+(j*mult); mult=mult*10; }");
			fprintf(tf,"smc++;");
			fprintf(tf,"i=strlen(inboxc);\nfor(mult=1,imc=0;i>0;i--){ j=inboxc[i]; j=j-48; imc=imc+(j*mult); mult=mult*10; }");
			fprintf(tf,"fclose(fr);fr=fopen(%cpmail/%s/count.txt%c,%cw%c);\n",coma,usrid,coma,coma,coma);
			fprintf(tf,"fprintf(fr,%d %d,imc,smc);fclose(fr);");
			fprintf(tf,"new1=fopen(%cpmail/%s/sentmail/%d.txt%c,%cw%c);\n",coma,usrid,imc,coma,coma,coma);
			fprintf(tf,"new2=fopen(%cpmail/%s/inbox/%d.txt%c,%cw%c);\n",coma,sendusr,smc,coma,coma,coma);
			fprintf(tf,"while((ch=fgetc(old))!=EOF){fprintf(new1,%c%cc%c,ch);}\n}",coma,persent,coma);
			fclose(tf);
			system("gcc tempo.c");
			system("./a.out");
			system("rm tempo.c");
			
		}
	}
	if(code=='6')//6 for display a mail
	{
		feedback=login(usrid,pwd);
		if(feedback==0)
		{
			i=0;
			while((ch=fgetc(fr))!=EOF)
			{inboxc[i]=ch; i++;}
			inboxc[i]='\0'	
			tf=fopen("tempo.c","w");
			fprintf(f,"#include<stdio.h>\n#include<stdio.h>\n#include<stdlib.h>\n#include<sys/types.h>\n#include<sys/stat.h>\n#include<fcntl.h>\nvoid main()\n{\nFILE *fp,*fb;");
			fprintf(f,"fp=fopen(%cpmail/%s/inbox/%s.txt%c,%cr%c);\n",coma,usrid,inboxc,coma,coma,coma);
			fprintf(f,"fb=fopen(%cfeedback.txt%c,%cw%c);",coma,coma,coma);
			fprintf(f,"while((ch=fgetc(fp))!=EOF){fprintf(fb,%c%c%c,coma,ch,coma);}\nch=EOF;\nfprintf(fb,%c%c%c,coma,ch,coma);\nfclose(fp);\nfclose(fb);\n}");
			fclose(tf);
			system("gcc tempo.c");
			system("./a.out");
			system("rm tempo.c");
		}
	}	
	if(code=='7')// 7 for delete a mail
	{
		feedback=login(usrid,pwd);
		if(feedback==0)
		{
			while((ch=fgetc(fr))!=EOF)
			{inboxc[i]=ch; i++;}
			inboxc[i]='\0'	
			tf=fopen("tempo.c","w");
			fprintf(tf,"#include<stdio.h>\n#include<stdio.h>\n#include<stdlib.h>\n#include<sys/types.h>\n#include<sys/stat.h>\n#include<fcntl.h>\nvoid main()\n{\nFILE *fp,*fb;\nchar ch;");
			fprintf(tf,"fp=fopen(%cpmail/%s/inbox.txt%c,%cr%c);\n",coma,usrid,coma,coma,coma);
			fprintf(tf,"fb=fopen(%ctempinbox.txt%c,%cw%c);",coma,coma,coma);
			fprintf(tf,"while((ch=fgetc(fp))!=EOF){fprintf(fb,%c%cc%c,ch)} fclose(fp);fclose(fb);\n",coma,persent,coma);
			fprintf(tf,"system(rm pmail/%s/inbox.txt);",usrid);
			fprintf(tf,"fp=fopen(%cpmail/%s/inbox.txt%c,%cw%c);\n",coma,usrid,coma,coma,coma);
			fprintf(tf,"while((ch=fgetc(fb))!=EOF){");
			fprintf(tf,"i=0;while((ch=fgetc(fb))!=' '){temps[i]=ch;i++} temps[i]='\0';");
			fprintf(tf,"i=strcmp(temps,%s)",inboxc);
			fprintf(tf,"if(i==0){while((ch=fgetc(fb))!='\n')}else{fprintf(fp,%c%cs%c,temps); }",coma,persent,coma);
			fclose(tf);
			system("gcc tempo.c");
			system("./a.out");
			system("rm tempo.c");
		}
	}
}

void login(char *usrid, char *pwd)
{
	FILE *f;
	int encript,idcheck,i,check,flag=0;
	char checkusrid[50],checkpwd[50],ch;
	f=fopen("pmail/log/logfile.txt","r");		
	ch=fgetc(f);
	while(ch!=EOF)
	{
		
		i=0;
		while(ch!=' ' && ch!=EOF)
		{
			checkusrid[i]=ch;
			ch=fgetc(f);
			i++;
		}
		checkusrid[i]='\0';
		if(ch==' ')
			ch=fgetc(f);
		idcheck=strcmp(checkusrid,usrid);
		if(idcheck==0)
		{
			i=0;
			while(ch!='\n' && ch!=EOF)
			{
				encript=ch;
				encript-=100;
				checkpwd[i]=encript;	
				ch=fgetc(f);
				i++;
			}
			checkpwd[i]='\0';
			idcheck=strcmp(checkpwd,pwd);
			if(idcheck==0)
				flag=1;
		}
		else
		{
			while(ch!='\n' && ch!=EOF)
				ch=fgetc(f);
		}
		if(ch!=EOF)
			ch=fgetc(f);
	}
	fclose(f);
	if(flag==1)
	{
		return(0);
	}
	else
		return(1);
}
