#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <string.h>

extern int errno;

int port;

int main (int argc, char *argv[])
{
  int sd;			
  struct sockaddr_in server;
  	
  int nr=0;
  char buf[200];

  if (argc != 3)
    {
      printf ("Sintax: %s <server_address> <port>\n", argv[0]);
      return -1;
    }

  port = atoi (argv[2]);

  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Socket error().\n");
      return errno;
    }

 
  server.sin_family = AF_INET;

  server.sin_addr.s_addr = inet_addr(argv[1]);
 
  server.sin_port = htons (port);
  
 
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Connect error().\n");
      return errno;
    }


  printf ("[client]What is your name? ");
  fflush (stdout);
  read (0, buf, 200);
 
  
   
  printf("[client] Read %s\n",buf);

 
  if (write (sd,buf,200) <= 0)
    {
      perror ("[client]Write error!\n");
      return errno;
    }


  if (read (sd, buf,200) < 0)
    {
      perror ("[client]Read error!\n");
      return errno;
    }
 
  printf ("[client]The message is: %s\n", buf);

  
  close (sd);
}