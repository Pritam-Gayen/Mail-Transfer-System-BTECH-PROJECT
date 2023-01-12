#include<stdio.h>
#include<string.h>

void writemail()
{
	FILE *f;
	char mail[3];
	f=fopen("temp.txt","a");
	printf("Enter ur mail here: \n");
	while(1)
	{
		gets(mail);
		if(mail[0]=='.' && mail[1]=='\n')
			break;
		fprintf(f,"%s\n",mail);
	}
	fclose(f);
}

void create()
{
	FILE *f;
	int ;
	char usrid[30],pwd[30];
	printf("\nChoosse user id: ");
	scanf("%s",&usrid);
	printf("\nChoosse password: ");
	scanf("%s",&pwd);
	f=fopen("temp.txt","w");
	fprintf(f,"0\n%s\n%s\n",usrid,pwd);
	fclose(f);
	system("gcc c2sc.c");
	system("./a.out temp.txt");
	system("gcc s2cc.c");
	system("./a.out feedback.txt");
}

void login()
{
	FILE *f;
	int choice,flag=0,msgnum;
	char usrid[30],pwd[30],sendusr[30];
	printf("\nChoosse user id: ");
	scanf("%s",&usrid);
	printf("\nChoosse password: ");
	scanf("%s",&pwd);
	f=fopen("temp.txt","w");
	fprintf(f,"1\n%s\n%s\n",usrid,pwd);
	fclose(f);
	system("gcc c2sc.c");
	system("./a.out temp.txt");
	system("gcc s2cc.c");
	system("./a.out feedback.txt");

	printf("If login success press 1, else 0: ");
	scanf("%d",&choice);
	if(choice==1)
	{
		while(1)
		{
			printf("1 : see inbox\n2 : see sent mail\n3 : compose mail\n4 : forword mail\n5 : display mail\n6 : delete  mail\n7 : logout.\n  You choose: ");
			scanf("%d",&choice);
			switch(choice)
			{
				case 1: printf("\n   INBOX   \n");f=fopen("temp.txt","w");fprintf(f,"2\n%s\n%s\n",usrid,pwd);fclose(f);system("gcc c2sc.c"); system("./a.out temp.txt");system("gcc s2cc.c");system("./a.out feedback.txt");break;
				case 2: printf("\n   SENT MAIL   \n");f=fopen("temp.txt","w");fprintf(f,"3\n%s\n%s\n",usrid,pwd);fclose(f);system("gcc c2sc.c"); system("./a.out temp.txt");system("gcc s2cc.c");system("./a.out feedback.txt");break;
				case 3: f=fopen("temp.txt","w");printf("Enter reciever id: ");scanf("%s",&sendusr);fprintf(f,"4\n%s\n%s\n%s\n",usrid,pwd,sendusr);fclose(f);writemail();printf("\nmail sent\n");break;
				case 4: f=fopen("temp.txt","w");printf("Enter reciever id: ");scanf("%s",&sendusr);printf("enter the no. of msg you want to forword: ");scanf("%d",&msgnum);fprintf(f,"5\n%s\n%s\n%s\n%d\n",usrid,pwd,sendusr,msgnum);printf("\nmail forworded.\n");break;
				case 5: printf("enter the no. of mail you want to see from inbox: ");scanf("%d",&msgnum);f=fopen("temp.txt","w");fprintf(f,"6\n%s\n%s\n",usrid,pwd);fclose(f);system("gcc c2sc.c"); system("./a.out temp.txt");system("gcc s2cc.c");system("./a.out feedback.txt");break;
				case 6: printf("enter the no. of mail you want to delete from inbox: ");scanf("%d",&msgnum);f=fopen("temp.txt","w");fprintf(f,"7\n%s\n%s\n",usrid,pwd);fclose(f);system("gcc c2sc.c"); system("./a.out temp.txt");system("gcc s2cc.c");system("./a.out feedback.txt");break;
				case 7: system("rm temp.txt");flag=1;break;
			}
			if(flag==1)
				break;
		}
	}
}


void main()
{
	int choice;
	while(1)
	{
		printf("\n\nTo create an account: 1\nTo login an account: 2\nTo exit: 0\nEnter your choice: ");
		scanf("%d",&choice);
		switch(choice)
		{
			case 0: exit(0);break;
			case 1: create();break;
			case 2: login();break;
		}
	}
}
