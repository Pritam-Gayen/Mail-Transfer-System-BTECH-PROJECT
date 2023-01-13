
# MAIL TRANSFER SYSTEM

A mail transfer system in LAN using Linux CLI.
## INTRODUCTION
Using UNIX socket programming in connection-oriented protocol (TCP) built a mail transfer system. We connect two or more computers. We assume one of them is as a server. Server holds the database about the all accounts and also usernames and passwords.
We divide the whole task in some phases, they are-

	1.	Login
	2.	Compose mail
	3.	Send mail
	4.	Forward mail
	5.	Display the mail
	6.	Delete mail
	7.	Create mail account
	8.	Log out

Used Data Structure:	String (character type array) this data structure is built in Unix. 

Data types are used: 	integer(int), character(char), constant character (const char).

Now we shall discuss about the phases - 

##### 1. Login: 
First, we ask username & password from user. We, then check validity of given username-password combination. If they are valid, we give access to that account to the user.
##### 2. Compose mail:
If user choose the option to compose mail, then we invoke a text-editor. User can write his/her mail there and send it to the desired destination (any person’s or organization’s e-mail address), and then we save that mail file to ‘sent-mail’ folder.
##### 3. Send mail:
If user chooses the option for sending mail, we ask for the user account if given the mail is sent to the corresponding account located in server machine.
##### 4. Forward mail:
If there is a mail on user’s account and if he/she choose the option ‘forward mail’ then we ask for the mail number of the mail to be forwarded and receiver’s user account, if given then the mail is sent to the corresponding account located in the server computer.
##### 5. Display the mail:
To display mails users have to choose the option ‘inbox’ after logged in. Here we ask for the corresponding mail number to display a particular mail, if given, we print it on screen.
##### 6. Delete mail:
If user chooses the option for deleting mail, then we ask for the mail number, if given, the corresponding mail file is deleted (removed) from the folder inbox.
##### 7. Create mail account:
If user choose ‘create mail’ option, then we ask for username. If given username is valid then we ask for a password and given username-password combination is stored in log file and corresponding user account is created in server computer.
##### 8. Log out:
If a logged in user choose to ‘log out’ option then we save the corresponding transaction to server machine and we send the user to the home or first screen.
## Description of the software of Mail transfer protocol
| Procedure     | Function           | Used system calls  |
| :-------------: |:-------------:| :-----:|
| Login             | login(), fopen(), fprintf(), fclose(), system()| socket(),bind(),listen(),accept()
|Compose & send     | login(),fprintf(),fopen(),fclose()             |Socket(),bind(),listen(),accept()
| Display mail      | login(),fopen(),fprintf(),fclose(),system()    | Socket(),bind(),listen(),accept()
|Delete mail        | login(),fopen(),fprintf(),fclose(),system()    | Socket(),bind(),listen(),accept()
|Create mail account| login(),fopen(),fprintf(),fclose(),system()    | Socket(),bind(),listen(),accept()
|Forward mail       | login(),fopen(),fprintf(),fclose(),system()    | Socket(),bind(),listen(),accept()
|Log out            | system() | |

## LOG IN
This phase has been implemented in following steps(page no.- 11)-

(a) A server program is running, the function name is ‘runningserver ()’. That connects the client machine by system calls socket, bind, listen and accept.

(b) We get a file from client computer where username & password is given and on the top of the file a ‘1’ tag (which indicates that user wants to login on that particular account) is also given. Using ‘write2file()’ function(page no.- 8) that file is written from the socket and is kept to new file ‘tempfile.txt’ by using ‘fputs()’ function.

(c)	Now we call ‘processfile()’ to calculate  what to do next.

(d) In ‘processfile()’ function we put  the tag value in ‘code’ variable. we put the ‘username ’ in ‘usrid’ string and password in ‘pwd’ variable.

(e)	Now if ‘code=0’ then do procedure for creating a mail account.

(f)	We check ‘usrid’ whether it is already in ‘logfile.txt’ or not. If not then we create a folder according to that ‘usrid’ and append ‘logfile.txt’ with new ‘usrid’ and ‘pwd’ .We also create inbox and sent mail folder inside that account and ‘count.txt’,’inbox.txt’,’sentmail.txt’ file is created inside the folder corresponding to that account.

(g)	After log in this we create a feedback file name ‘feedback.txt’ and that file is printed on client desktop monitor, whether the account is created or not.

## COMPOSE MAIL
This phase has been implemented in the following steps -
On processfile() function if we get ‘code=4’,then if ‘feedback=0’

(a) Open a temporary file ‘temp.c’ .This file is created dynamically (on runtime).

(b) The written mail created by user, collected from socket stream and written on a file ‘ftemp.txt’.

(c) We create a text file on the corresponding user folder in server machine.

(d) We take the value from ‘count.txt’ that is a integer number. Then we create a text file with the integer value inside the sent mail folder.

(e) Create another text file name with that integer value inside the account (to whom the user want to send that file) and inside the inbox folder.

(f) Then open sentmail file of user accout and append the new entry.

(g) Then open inbox.txt file of the receiver account and append the new entry.

## SEND MAIL
Implementation mechanism of send mail phase is same as compose mail.

## FORWORD MAIL
This phase has been implemented in the following steps(page no.-12)-

(a)	User have to choose the mail from inbox (which file he/she want to send to the receiver). Client side program store the corresponding file name and send it to the server.

(b)	Server reads the file name from socket and store it in a string.

(c)	Now from receiver account folder we open count.txt, take the value for inbox and increment it.

(d)	Create a text file by that integer value inside the inbox and copy the copy the content of the corresponding file here.

(e)	Now from user account folder we open count.txt and take the value according to sent mail and increment it.

(f)	Create a text file by that integer value inside the sent mail folder and copy the content of the corresponding file here.

## DISPLAY MAIL
This phase has been implemented as follows-

(a)	First, client choose the option inbox or sent mail. According to that option server sends the corresponding file to client socket.

(b)	Client machine writes that file in tempfile.txt.

(c)	Now we display the tempfile.txt on screen.

(d)	User choose the sequence number of a file in inbox or sentmail.

(e)	Client send the value to server machine.

(f)	According to that value server sends the corresponding text file from the corresponding folder.

(g)	Client machine reads the file from socket and write it on the terminal.

## DELETE MAIL
This phase has been implemented as follows –

(a)	First, client choose the option inbox.

(b)	Then inbox.txt file is sent to the client socket by server.

(c)	The inbox.txt file is displayed at the terminal.

(d)	User select serial number of the file he wants to delete.

(e)	Selected serial number is sent to the server.

(f)	According to the serial number the corresponding text file is removed from the inbox folder.

(g)	According to the serial number the corresponding line is removed from ‘inbox.txt’.

## CREATE MAIL ACCOUNT
This phase has been implemented as the following steps -

(a)	First, ‘create mail’ option is chosen. According to that option ‘0’ is saved on a temporary file.

(b)	Then user is asked for username and password. Given username and password is saved in the temporary file, where two separate variables hold username and password. This file is sent to the server machine.

(c)	Server reads that file and save them in a temporary file.

(d)	Then server checks whether the given username is in log file or not.

d.1. If no match is found then create the account (create a folder         according to that username and enter the details of that account in the logfile.txt).

d.2. Else write on feedback.txt file that, this username already exists and send it to the client trying to create an account.

## LOG OUT
This phase has been implemented as the following steps -

(a)	If client choose the option ‘log out’ then put ‘username’ in the variable which holds username and put ‘password’ in the variable that holds password.

(b)	Remove the temporary file from client.

## CONCLUSION
##### Some notes on SMTP (The Simple Mail Transfer Protocol):
To transmit mail through internet this protocol is widely used.It has many drawbacks and as remedy to these drawbacks modified versions are replacing previous versions day-to-day.

##### SMTP works as follows:
Within the internet , e-mail is delivered by having the source machine established a TCP connection to port 25 of the destination machine.Listening to this port is an e-mail daemon that speaks SMTP.This daemon accepts incoming connections and copies messages from them into the appropriate mailboxes.If a message cannot be delivered , an error containing the first part of the undelivered message is returned to the sender.AS SMTP use TCP connection, so it performs reliable mail transfer. 
SMTP is a simple ASCII protocol.

##### Comparison of our implementation to SMTP:
If on a UNIX system, in a shell, we type-
telnet mail.isp.com 25 (here, mail.isp.com is DNS name of the user’s ISP’s mail server)
This command will establish a telnet (i.e. TCP) connection to port 25 on that machine. We probably get following response-
	
	Trying 192.30.200.66….
	Connected to mail.isp.com
	escape character is  ‘^]’
	220 mail.isp.com Smail #74 ready at Thu, 20 June 2013 20:26 +0200 

The first three lines are from telnet telling user what it is doing. The last line is from the server on the remote machine announcing its willingness to talk to user and accept e-mail.
Thus SMTP and most internet protocol use ASCII text for commands.
Using ASCII text makes the protocol easy to test and debug.
They can be tested by sending commands manually, and dumps of the messages are easy to read.

But mail transfer system implemented by us has limitation on that aspect. In our system ASCII text for commands cannot be used.


As we saw, e-mail is delivered by having the sender establish a TCP connection to the receiver and then ship the e-mail over it. This model worked fine for decades when all ARPANET (and later internet) hosts were, in fact, on-line all the time to accept TCP connections.
However, with the advent of people who access the internet by calling their ISP over a modem, it breaks down. The problem is that, when both sender and receiver are not on-line, a TCP connection cannot be established and thus cannot run SMTP protocol. This is a limitation of SMTP protocol.

while we send mail to receiver mail account, not necessary that the corresponding client machine is online. The mail is stored in a folder named ‘inbox’ corresponding to that mail account in server machine.

##### Limitations of our implementation:
In addition to the above limitation, our implementation has no interface to user, so it is usable only by us (designer) in terminal.
