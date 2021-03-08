#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <pthread.h>

#define PORT 2021

extern int errno;

typedef struct thData{
	int idThread;
	int cl;
}thData;

static void *treat(void *);
void raspunde(void *);

int main ()
{
  struct sockaddr_in server;
  struct sockaddr_in from;	
  
  int sd;		
  int pid;
  pthread_t th[100];
	int i=0;
  

  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server]Socket error().\n");
      return errno;
    }
  int on=1;
  setsockopt(sd,SOL_SOCKET,SO_REUSEADDR,&on,sizeof(on));
  
  bzero (&server, sizeof (server));
  bzero (&from, sizeof (from));
  
 
    server.sin_family = AF_INET;	
    server.sin_addr.s_addr = htonl (INADDR_ANY);
    server.sin_port = htons (PORT);
  

  if (bind (sd, (struct sockaddr *) &server, sizeof (struct sockaddr)) == -1)
    {
      perror ("[server]Bind error().\n");
      return errno;
    }


  if (listen (sd, 2) == -1)
    {
      perror ("[server]Listen error().\n");
      return errno;
    }
 
  while (1)
    {
      int client;
      thData * td;  
      int length = sizeof (from);

      printf ("[server]Waiting %d...\n",PORT);
      fflush (stdout);

     
      if ( (client = accept (sd, (struct sockaddr *) &from, &length)) < 0)
	{
	  perror ("[server]Accept error().\n");
	  continue;
	}
	

	td=(struct thData*)malloc(sizeof(struct thData));	
	td->idThread=i++;
	td->cl=client;

	pthread_create(&th[i], NULL, &treat, td);	      
				
	}   
};				
static void *treat(void * arg)
{		
		struct thData tdL; 
		tdL= *((struct thData*)arg);	
		printf ("[thread]- %d - Waiting for message...\n", tdL.idThread);
		fflush (stdout);		 
		pthread_detach(pthread_self());		
		raspunde((struct thData*)arg);
		close ((intptr_t)arg);
		return(NULL);	
  		
};


void raspunde(void *arg)
{
        int i=0;
        char buf[200];
	struct thData tdL; 
	tdL= *((struct thData*)arg);
	if (read (tdL.cl, buf,200 )<= 0)
			{
			  printf("[Thread %d]\n",tdL.idThread);
			  perror ("Read error!\n");
			
			}
	
	printf ("[Thread %d]Message received %s\n",tdL.idThread,buf);
		      
		    
		      char resp[200] = "Hello, "; 
          strcat(resp, buf);
          strcpy(buf, resp);


	printf("[Thread %d]Message is sending back to client...%s\n",tdL.idThread, resp);
		      
		      
		    
	 if (write (tdL.cl, buf, 200) <= 0)
		{
		 printf("[Thread %d] ",tdL.idThread);
		 perror ("[Thread]Write error!\n");
		}
	else
		printf ("[Thread %d]Message was sent successfully!\n",tdL.idThread);	

}