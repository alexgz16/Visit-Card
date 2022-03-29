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
  char buf[256];
  char buf1[256];
  char mesal[256];
  
  if (argc != 3)
    {
      printf ("Sintaxa: %s <adresa_server> <port>\n", argv[0]);
      return -1;
    }

  port = atoi (argv[2]);

  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("Eroare la socket().\n");
      return errno;
    }

  server.sin_family = AF_INET;
  server.sin_addr.s_addr = inet_addr(argv[1]);
  server.sin_port = htons (port);
  
  
  if (connect (sd, (struct sockaddr *) &server,sizeof (struct sockaddr)) == -1)
    {
      perror ("[client]Eroare la connect().\n");
      return errno;
    }
  memset(buf,'\0',sizeof(buf));
  
  while (1)
  {
     memset(buf,'\0',sizeof(buf));
  printf ("Alegeti o comanda: Cauta/Actualizeaza/Adauga/Sterge/Exit +  parametrii: ");
  fflush (stdout);
  read (0, buf, 256);
  if(strncmp(buf,"Exit",4)==0)
      {
        close(sd);
        break;
      }
  printf("[client] Am citit %s\n",buf);
  fflush(stdout);
  if (write (sd,&buf,256) <= 0)
    {
      perror ("[client]Eroare la write() spre server.\n");
      return errno;
    }
     memset(buf,'\0',sizeof(buf));
  if (read (sd, &buf,256) < 0)
    {
      perror ("[client]Eroare la read() de la server.\n");
      return errno;
    }
  printf ("[client]Mesajul primit este: %s\n", buf);
  fflush(stdout);
  }
  return 0;
}
