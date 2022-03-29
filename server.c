#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <signal.h>
#include <json-c/json.h>
#include <pthread.h>


#define PORT 2916
extern int errno;

typedef struct thData{
	int idThread; 
	int cl; 
}thData;

static void *treat(void *); 
void raspunde(void *);
char * Cauta(char *buf1)
{
   
   char *lname, *email1, *age1, *fname;
   char *prefix=malloc(256);
   char *verif=malloc(256);
   int i=0;
   strcat(verif,buf1);
   verif[strlen(verif)-1]='\0';
   strcat(verif,".json");
   printf("verif=%s\n",verif);
   if(access(verif, F_OK))
        {
          char *prm=malloc(256);
         strcat(prm,"Nu exista fisierul");
         prm[strlen(prm)]='\0';
         return prm;
        }
   json_object *root = json_object_from_file(verif);

   json_object *name = json_object_object_get(root,  "name");
   json_object *first_name = json_object_object_get(root, "first_name");
   json_object *email = json_object_object_get(root,  "email");
   json_object *age = json_object_object_get(root,  "age");
   
 
   lname = strdup(json_object_get_string(name));
   fname = strdup(json_object_get_string(first_name));
   email1 = strdup(json_object_get_string(email));
   age1=strdup(json_object_get_string(age));
   snprintf(prefix,256,"Nume: %s\n Prenume:%s\n Varsta: %s\n Email:%s\n",lname,fname,age1,email1);
     return prefix;
   
   json_object_put(root);

   printf("%s, %s\n", fname, email1);
   printf("%s",age1);

   free(&verif);
   free(lname);
   free(fname);
   free(age);
   free(email1);
}

void  Adauga(char *buf1)
{
   printf("%s\n",buf1);
   char verif[256];
   char nume[256],age[256],email[256],prenume[256];
   int i=0;
   int j1=0,j2=0,j3=0,j4=0;;
   int nr=0;
   memset(verif, 0, sizeof(verif));
   memset(nume, 0, sizeof(nume));
   memset(prenume, 0, sizeof(prenume));
   memset(age, 0, sizeof(age));
   memset(email, 0, sizeof(email));
   strcat(verif,buf1);
   verif[strlen(verif)-1]='\0';
   bzero(&buf1, sizeof(buf1));
   printf("%s\n",verif);
   while(verif[i]!='\0')
   {
     if(verif[i]==',' || verif[i]=='\0')
         {
           nr++;
         }
     else{
        if(nr==0)
            {nume[j1]=verif[i];
            j1++;}
        if(nr==2)
        {
          age[j2]=verif[i];
          j2++;
        }
        if(nr==1)
        {
          prenume[j3]=verif[i];
          j3++;
        }
        if(nr==3)
        {
          email[j4]=verif[i];
          j4++;
        }
     }
     i++;
   }
   nume[strlen(nume)]='\0';
   prenume[strlen(prenume)]='\0';
   age[strlen(age)]='\0';
   email[strlen(email)]='\0';
   printf("%s\n",nume);
   printf("%s\n",age);
   printf("%s\n",email);
   char filename[256];
   memset(filename, 0, sizeof(filename));
   strcat(filename,nume);
   strcat(filename,".json");
   filename[strlen(filename)]='\0';
   FILE *fp = NULL;

        fp = fopen( filename,"a");
   
   json_object *root = json_object_new_object();
     
   json_object_object_add(root, "name", json_object_new_string(nume));
   json_object_object_add(root, "first_name", json_object_new_string(prenume));
   json_object_object_add(root, "age", json_object_new_string(age));
   json_object_object_add(root, "email", json_object_new_string(email));
   json_object_to_file(filename, root);
   json_object_put(root);
    bzero(&verif,sizeof(verif));
   
}
char *Actualizeaza(char *buf1)
{
  printf("%s\n",buf1);
   char verif[256];
   char nume[256],age[256],email[256],prenume[256];
   int i=0;
   int j1=0,j2=0,j3=0,j4=0;;
   int nr=0;
   memset(verif, 0, sizeof(verif));
   memset(nume, 0, sizeof(nume));
   memset(prenume, 0, sizeof(prenume));
   memset(age, 0, sizeof(age));
   memset(email, 0, sizeof(email));
   strcat(verif,buf1);
   verif[strlen(verif)-1]='\0';
   bzero(&buf1, sizeof(buf1));
   printf("%s\n",verif);

   while(verif[i]!='\0')
   {
     if(verif[i]==',' || verif[i]=='\0')
         {
           nr++;
         }
     else{
        if(nr==0)
            {nume[j1]=verif[i];
            j1++;}
        if(nr==2)
        {
          age[j2]=verif[i];
          j2++;
        }
        if(nr==1)
        {
          prenume[j3]=verif[i];
          j3++;
        }
        if(nr==3)
        {
          email[j4]=verif[i];
          j4++;
        }
     }
     i++;
   }
   nume[strlen(nume)]='\0';
   prenume[strlen(prenume)]='\0';
   age[strlen(age)]='\0';
   email[strlen(email)]='\0';
   char filename[256];
   memset(filename, 0, sizeof(filename));
   strcat(filename,nume);
   strcat(filename,".json");
   filename[strlen(filename)]='\0';
   if( access( filename, F_OK ) == 0 )
       {
         remove(filename);
         FILE *fp = NULL;

         fp = fopen( filename,"a");
   
          json_object *root = json_object_new_object();
     
          json_object_object_add(root, "name", json_object_new_string(nume));
          json_object_object_add(root, "first_name", json_object_new_string(prenume));
          json_object_object_add(root, "age", json_object_new_string(age));
          json_object_object_add(root, "email", json_object_new_string(email));
          json_object_to_file(filename, root);
          json_object_put(root);
          char *prm=malloc(256);
         strcat(prm,"Am facut update fisierul");
         prm[strlen(prm)]='\0';
         return prm;
       }
  else {
         char *prm=malloc(256);
         strcat(prm,"Nu exista fisierul");
         prm[strlen(prm)]='\0';
         return prm;
       }  
       bzero(&verif,sizeof(verif));
       bzero(&nume,sizeof(nume));
}
void Sterge(char *buf1)
{
   char verif[256];
   strcat(verif,buf1);
   verif[strlen(verif)-1]='\0';
   strcat(verif,".json");
   printf("verif=%s\n",verif);
   if (remove(verif) == 0)
      printf("Deleted successfully");
   else
      printf("Unable to delete the file");
}
int main ()
{
  struct sockaddr_in server;	
  struct sockaddr_in from;	
  int nr;		
  int sd;		
  int pid;
  pthread_t th[100];   
	int i=0;
  

  
  if ((sd = socket (AF_INET, SOCK_STREAM, 0)) == -1)
    {
      perror ("[server]Eroare la socket().\n");
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
      perror ("[server]Eroare la bind().\n");
      return errno;
    }

  if (listen (sd, 2) == -1)
    {
      perror ("[server]Eroare la listen().\n");
      return errno;
    }
  
  while (1)
    {
      int client;
      thData *td;     
      int length = sizeof (from);

      printf ("[server]Asteptam la portul %d...\n",PORT);
      fflush (stdout);

      if ( (client = accept (sd, (struct sockaddr *) &from, &length)) < 0)
	{
	  perror ("[server]Eroare la accept().\n");
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
		printf ("[thread]- %d - Asteptam mesajul...\n", tdL.idThread);
		fflush (stdout);
    pthread_detach(pthread_self());		
		raspunde((struct thData*)arg);
    close ((intptr_t)arg);
		return(NULL);	
  		
};


void raspunde(void *arg)
{
        int i=0;
        char buf[256];
        char ok[2]="ok";
	struct thData tdL; 
	tdL= *((struct thData*)arg);
  
  while(1)
  {
	 if (read (tdL.cl, &buf,sizeof(buf)) <= 0)
			{
			  printf("[Thread %d]\n",tdL.idThread);
			  perror ("Eroare la read() de la client.\n");
			}	
	printf ("[Thread %d]Mesajul a fost receptionat...%s\n",tdL.idThread, buf);
		      
		if(strncmp(buf, "Adauga",6)==0)
        {
          char buf1[256]; 
           memset(buf1, 0, sizeof(buf1));
          strcpy(buf1,buf+8);
          printf("%s\n",buf1);
          Adauga(buf1);
          if (write (tdL.cl, &ok, sizeof(ok)) <= 0)
		     {
		       printf("[Thread %d] ",tdL.idThread);
		       perror ("[Thread]Eroare la write() catre client.\n");
		     }
	        else
		       printf ("[Thread %d]Mesajul a fost trasmis cu succes.\n",tdL.idThread);
           bzero(&buf,strlen(buf));
           bzero(buf1,strlen(buf1));
        }
    else if(strncmp(buf,"Cauta",5)==0)
            {
              char buf1[256]; 
              memset(buf1, 0, sizeof(buf1));
              strcpy(buf1,buf+7);
              printf("%s\n",buf1);
               char *raspuns=Cauta(buf1);
               printf("raspuns:%s\n",raspuns);
               if (write (tdL.cl, raspuns, strlen(raspuns)) <= 0)
		          {
		           printf("[Thread %d] ",tdL.idThread);
		           perror ("[Thread]Eroare la write() catre client.\n");
		          }
	             else
		            printf ("[Thread %d]Mesajul a fost trasmis cu succes.\n",tdL.idThread); 
                bzero(&buf,strlen(buf));
                bzero(buf1,strlen(buf1));
            }
         else if(strncmp(buf, "Sterge",6)==0)
               {
                 char buf1[256]; 
                 memset(buf1, 0, sizeof(buf1));
                 strcpy(buf1,buf+8);
                 printf("%s\n",buf1);
                 Sterge(buf1);
                 char sters[]="A fost sters";
                 if (write (tdL.cl, &sters, sizeof(sters)) <= 0)
		            {
		             printf("[Thread %d] ",tdL.idThread);
		             perror ("[Thread]Eroare la write() catre client.\n");
		            }
	               else
		             printf ("[Thread %d]Mesajul a fost trasmis cu succes.\n",tdL.idThread);
                 bzero(&buf,strlen(buf));
                bzero(buf1,strlen(buf1));
               }
              else if(strncmp(buf,"Actualizeaza",12)==0)
                     { 
                      char buf1[256]; 
                      memset(buf1, 0, sizeof(buf1));
                      strcpy(buf1,buf+14);
                      printf("%s\n",buf1);
                      char *raspuns=Actualizeaza(buf1);
                      if (write (tdL.cl, raspuns, 256) <= 0)
		                 {
		                    printf("[Thread %d] ",tdL.idThread);
		                    perror ("[Thread]Eroare la write() catre client.\n");
		                 }
	                    else
		                     printf ("[Thread %d]Mesajul a fost trasmis cu succes.\n",tdL.idThread);
                     }
                    else
                       {
                              if (write (tdL.cl, "Comanda gresita", sizeof("Comanda gresita")) <= 0)
		                         {
		                          printf("[Thread %d] ",tdL.idThread);
		                          perror ("[Thread]Eroare la write() catre client.\n");
		                         }
                             else
		                       printf ("[Thread %d]Mesajul a fost trasmis cu succes.\n",tdL.idThread);  
                       }	
    bzero(&ok,2);
    bzero(&buf,256);
  }
}
