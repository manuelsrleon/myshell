#include "memory.h"
#include <stdbool.h>
#include "../common/common.h"
#include <stddef.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <sys/shm.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


#define TAMANO 2048
void printList();

int p2_malloc(char* tokens[], int ntokens){
    bool _free = false; 
    _free = has_token(tokens,ntokens, "-free");

    //posibles casos
    //malloc | ntokens = 1
    //imprimir lista
    //malloc n | ntokens = 2 && !freeq
    if(ntokens == 2 && !_free){
        unsigned long tam = (size_t) strtoul(tokens[1],NULL,10);
        void * p; 
        //imprimir qué dirección ha salido de ahí
        p = malloc(tam); 
        printf("Asignados %lu bytes en %p\n",tam,p);
        //después meter en lista.
        return 0;
    }
    //malloc -free n |
    if(ntokens == 3 && _free){
        void *p = (void*) strtoul(tokens[2],NULL,16);
        free(p);
        //imprimir qué dirección se libera
        
        printf("%s %s\n","Se ha liberado la dirección ",tokens[ntokens-1]);
        return 0;
    }
    return 0;
};
void * ObtenerMemoriaShmget (key_t clave, size_t tam)
{
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;

    if (tam)     /*tam distito de 0 indica crear */
        flags=flags | IPC_CREAT | IPC_EXCL;
    if (clave==IPC_PRIVATE)  /*no nos vale*/
        {errno=EINVAL; return NULL;}
    if ((id=shmget(clave, tam, flags))==-1)
        return (NULL);
    if ((p=shmat(id,NULL,0))==(void*) -1){
        aux=errno;
        if (tam)
             shmctl(id,IPC_RMID,NULL);
        errno=aux;
        return (NULL);
    }
    shmctl (id,IPC_STAT,&s);
 /** Guardar en la lista, p.e.  InsertarNodoShared (&L, p, s.shm_segsz, clave); */
    return (p);
}

//comando leerfichero y escribo en x dirección
void SharedCreate (char *tr[])
{
   key_t cl;
   size_t tam;
   void *p;

   if (tr[0]==NULL || tr[1]==NULL) {
		/** ImprimirListaShared(&L); **/
		return;
   }
  
   cl=(key_t)  strtoul(tr[0],NULL,10);
   tam=(size_t) strtoul(tr[1],NULL,10);
   if (tam==0) {
	printf ("No se asignan bloques de 0 bytes\n");
	return;
   }
   if ((p=ObtenerMemoriaShmget(cl,tam))!=NULL)
		printf ("Asignados %lu bytes en %p\n",(unsigned long) tam, p);
   else
		printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}


void SharedDelkey (char *args[])
{
   key_t clave;
   int id;
   char *key=args[0];

   if (key==NULL || (clave=(key_t) strtoul(key,NULL,10))==IPC_PRIVATE){
        printf ("      delkey necesita clave_valida\n");
        return;
   }
   if ((id=shmget(clave,0,0666))==-1){
        perror ("shmget: imposible obtener memoria compartida");
        return;
   }
   if (shmctl(id,IPC_RMID,NULL)==-1)
        perror ("shmctl: imposible eliminar id de memoria compartida\n");
}

int p2_shared(char* tokens[], int ntokens){
    bool _free = false;
    bool _create = false;
    bool _delkey = false;
    
    _free = has_token(tokens,ntokens, "-free");
    _create = has_token(tokens,ntokens, "-create");
    _delkey = has_token(tokens,ntokens, "-delkey");

    int number_of_options = _free + _create + _delkey;

    char *cl = "";
    strcpy(cl,tokens[number_of_options+2]);
    //shared
    
    //imprimir lista SHARED
    //shared -create cl [tam] (ntokens = 4)
    if(ntokens == 4 && _create){
        //TODO test
        SharedCreate(&tokens[1]);
    }else
    //shared -free cl [tam]
    if(ntokens == 4 && _free){
        //TODO implement
        
    }else
    //shared -delkey cl
    if(ntokens == 4 && _delkey){
        //TODO implement
        SharedDelkey(&tokens[1]);
    }
    return 0;   
}

void * MapearFichero (char * fichero, int protection)
{
    int df, map=MAP_PRIVATE,modo=O_RDONLY;
    struct stat s;
    void *p;

    if (protection&PROT_WRITE)
          modo=O_RDWR;
    if (stat(fichero,&s)==-1 || (df=open(fichero, modo))==-1)
          return NULL;
    if ((p=mmap (NULL,s.st_size, protection,map,df,0))==MAP_FAILED)
           return NULL;
/* Guardar en la lista    InsertarNodoMmap (&L,p, s.st_size,df,fichero); */
    return p;
}
int p2_mmap(char* tokens[], int ntokens){
    bool _free = has_token(tokens, ntokens, "-free");
    //mmap [-free] fich prm 
    if(ntokens == 3 && !_free){
        //mmap fich prm
        MapearFichero(tokens[1], PROT_WRITE);
    }else if(ntokens == 4 && _free){
        //mmap -free fich prm
        //TODO duda ¿Cómo libero el mapeado de un fichero?
    }else{
        printf("Número de argumentos inválido.");
    }
    return 0;
}

ssize_t LeerFichero (char *f, void *p, size_t cont)
{
   struct stat s;
   ssize_t  n;  
   int df,aux;

   if (stat (f,&s)==-1 || (df=open(f,O_RDONLY))==-1)
	return -1;     
   if (cont==-1)   /* si pasamos -1 como bytes a leer lo leemos entero*/
	cont=s.st_size;
   if ((n=read(df,p,cont))==-1){
	aux=errno;
	close(df);
	errno=aux;
	return -1;
   }
   close (df);
   return n;
}

int p2_read(char* tokens[], int ntokens){
    /* read fiche addr cont
    Lee cont bytes desde fich a la dirección addr
    */
    char* _fich = tokens[1];
    void* _addr = (void*) strtoul(tokens[2], NULL, 16);
    size_t _cont = (size_t) strtoul(tokens[3],NULL,10);
    if(ntokens == 4){
        LeerFichero(_fich, _addr, _cont);
    }else{
        printf("Número de argumentos inválido");
    }
    return 0;
}

int p2_write(char* tokens[], int ntokens);

int p2_memdump(char* tokens[], int ntokens){
    //memdump addr cont
    void * _addr = (void*) strtoul(tokens[1], NULL, 16);
    size_t _cont = (size_t) strtoul(tokens[2],NULL,10);
    
    unsigned char *arr =(unsigned char*) _addr;
    

    if(ntokens == 3){
        printf("Volcando %s bytes desde la dirección %p",tokens[1],_addr);
        for(int i = 0; i <= _cont; i++){
            printf("%02x ",arr[i]);
            if(i % 10 == 0){
                printf("\n");
            }
        }
        printf("\n");
        return 0;
    }else{
        perror("memdump");
        return 1;
    }
}

void LlenarMemoria (void *p, size_t cont, unsigned char byte)
{
  unsigned char *arr=(unsigned char *) p;
  size_t i;

  for (i=0; i<cont;i++)
		arr[i]=byte;
}


int p2_memfill(char* tokens[], int ntokens){
    //llenar memoria con un caracter
    //malloc -> reservo memoria -> cojo la referencia desde la lista -> escribo fichero en dirección 0xXXX
    //sin lista simplemente lo implemento como tal
    //memfill addr cont byte | ntokens == 4
    void * _addr = (void*) strtoul(tokens[1], NULL, 16);
    size_t _cont = (size_t) strtoul(tokens[2],NULL,10);
    unsigned char _byte = strtoul(tokens[3], NULL, 16);
    
    if(ntokens == 4) {
        printf("Llenando %lu bytes de memoria con el byte (%x) a partir de la dirección %p\n",_cont,_byte,_addr);
        LlenarMemoria(_addr,_cont,_byte);
        return 0;
    }else{
        printf("Número de parámetros inválido.");
        return 1;
    }
}
int p2_mem(char* tokens[], int ntokens);

void Recursiva (int n)
{
  char automatico[TAMANO];
  static char estatico[TAMANO];

    printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico);

  if (n>0)
    Recursiva(n-1);
}
int p2_recurse(char* tokens[], int ntokens){
    //Está ahí para imprimir direcciones de memoria. ¿Por qué salen esas direcciones y por qué no otras? 
    //recurse n
    if(ntokens == 2){
        Recursiva(atoi(tokens[1]));
    }else{
        printf("Numero de argumentos inválido");
    }
    return 0;
}