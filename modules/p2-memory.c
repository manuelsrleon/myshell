#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define TAMANO 512
#include "common/common.h"
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>



void do_DeallocateDelkey (char *args[])
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
        perror ("shmctl: imposible eliminar memoria compartida\n");
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
/* Gurdas en la lista de descriptores usados df, fichero*/
    return p;
}

void * ObtenerMemoriaShmget (key_t clave, size_t tam)
{
    void * p;
    int aux,id,flags=0777;
    struct shmid_ds s;

    if (tam)     /*tam distito de 0 indica crear */
        flags=flags | IPC_CREAT | IPC_EXCL; /*cuando no es crear pasamos de tamano 0*/
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
    shmctl (id,IPC_STAT,&s); /* si no es crear, necesitamos el tamano, que es s.shm_segsz*/
 /* Guardar en la lista   InsertarNodoShared (&L, p, s.shm_segsz, clave); */
    return (p);
}
void do_AllocateCreateshared (char *tr[])
{
   key_t cl;
   size_t tam;
   void *p;

   if (tr[0]==NULL || tr[1]==NULL) {
		//ImprimirListaShared(&L);
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

void do_AllocateShared (char *tr[])
{
   key_t cl;
   //size_t tam;
   void *p;

   if (tr[0]==NULL) {
		//ImprimirListaShared(&L);
		return;
   }
  
   cl=(key_t)  strtoul(tr[0],NULL,10);

   if ((p=ObtenerMemoriaShmget(cl,0))!=NULL)
		printf ("Asignada memoria compartida de clave %lu en %p\n",(unsigned long) cl, p);
   else
		printf ("Imposible asignar memoria compartida clave %lu:%s\n",(unsigned long) cl,strerror(errno));
}

void do_AllocateMmap(char *arg[])
{ 
     char *perm;
     void *p;
     int protection=0;
     
     if (arg[0]==NULL)
            {//ImprimirListaMmap(&L); return;
            }
     if ((perm=arg[1])!=NULL && strlen(perm)<4) {
            if (strchr(perm,'r')!=NULL) protection|=PROT_READ;
            if (strchr(perm,'w')!=NULL) protection|=PROT_WRITE;
            if (strchr(perm,'x')!=NULL) protection|=PROT_EXEC;
     }
     if ((p=MapearFichero(arg[0],protection))==NULL)
             perror ("Imposible mapear fichero");
     else
             printf ("fichero %s mapeado en %p\n", arg[0], p);
}


 int allocate(char* tokens[], int ntokens){
    
    bool opt_malloc = has_token(tokens,ntokens, "-malloc");
    bool opt_mmap = has_token(tokens,ntokens, "-mmap");
    bool opt_create = has_token(tokens,ntokens, "-create");
    bool opt_shared = has_token(tokens,ntokens, "-shared");

    if(ntokens==1){
        //print assigned blocks
    }
    //allocate -malloc n
    if(ntokens==3 && opt_malloc){
        unsigned long tam = (size_t) strtoul(tokens[2],NULL,10);
        void * p; 
        //TODO error handling
        p = malloc(tam); 
        printf("Asignados %lu bytes en %p\n",tam,p);
        //save in list
    }
    
    //allocate -shared cl
    if(ntokens==3 && opt_shared){
        do_AllocateShared(&tokens[1]);
    }
    
    //allocate -mmap file perm
    if(ntokens==4 && opt_mmap){
        do_AllocateMmap(&tokens[1]);
    }
    //allocate -create cl n
    if(ntokens==4 && opt_create){
        do_AllocateCreateshared(&tokens[1]);
    }
    return 0;
}
int deallocate(char* tokens[], int ntokens){
    
    bool opt_malloc = has_token(tokens,ntokens, "-malloc");
    bool opt_mmap = has_token(tokens,ntokens, "-mmap");
    bool opt_shared = has_token(tokens,ntokens, "-shared");
    bool opt_delkey = has_token(tokens,ntokens, "-delkey");

    if(ntokens==1){
        //print assigned blocks
    }
    //deallocate -malloc n
    if(ntokens==3 && opt_malloc){
        void *p = (void*) strtoul(tokens[2],NULL,16);
        free(p);
        //imprimir qué dirección se libera
        printf("%s %s\n","Se ha liberado la dirección ",tokens[ntokens-1]);
        //save in list
        return 0;
    }
    
    //deallocate -shared cl
    if(ntokens==3 && opt_shared){
        
    }
    
    //deallocate -mmap file perm
    if(ntokens==4 && opt_mmap){

    }
    //deallocate -delkey cl
    if(ntokens==3 && opt_delkey){
        do_DeallocateDelkey(&tokens[1]);
    }
    return 0;
}

void LlenarMemoria (void *p, size_t cont, unsigned char byte)
{
  unsigned char *arr=(unsigned char *) p;
  size_t i;

  for (i=0; i<cont;i++)
		arr[i]=byte;
}
int memfill(char* tokens[], int ntokens){
    //memfil addr cont ch
    if(ntokens == 4){
        void * _addr = (void*) strtoul(tokens[1], NULL, 16);
        size_t _cont = (size_t) strtoul(tokens[2],NULL,10);
        unsigned char _byte = strtoul(tokens[3], NULL, 16);
        printf("Filling %s bytes in memory with value %d at address %p\n",tokens[2], _byte, _addr);
        LlenarMemoria(_addr,_cont,_byte);
        return 0;
    }else{
    // throwWrongSyntaxError("memfill:");
        return 0;
    }
}
int memdump(char* tokens[], int ntokens){
    //memdump addr cont
    if(ntokens == 3 || ntokens == 2){

        void *_addr = (void*) strtoul(tokens[1],NULL,16);
        if(ntokens == 2){
            tokens[2] = "25";
        }
        size_t _cont = 25;
        if(ntokens == 3){
            _cont = (size_t) strtoul(tokens[2], NULL, 10);
        }

        unsigned char *arr = (unsigned char* ) _addr;

        printf("Dumping %s bytes of memory from address %p\n", tokens[2], _addr);
        for(int i = 0; i < _cont; i++){
            if( i% 10 == 0 && i != 0){
                printf("\n");
            }
            printf("%02x ", arr[i]);//0-9 10
        }
        printf("\n");
        return 0;
    }else{
        //throwWrongSyntaxError("memdump");
        return 0;
    }

}

int printMemoryList(){
    //list print stub
    return 0;
}

int gVar1 = 42;
int gVar2 = 1337;
int gVar3 = 1312;

int ugVar1 = 42;
int ugVar2 = 1337;
int ugVar3 = 1312;
void Do_pmap (void) /*sin argumentos*/
 { pid_t pid;       /*hace el pmap (o equivalente) del proceso actual*/
   char elpid[32];
   char *argv[4]={"pmap",elpid,NULL};
   
   sprintf (elpid,"%d", (int) getpid());
   if ((pid=fork())==-1){
      perror ("Imposible crear proceso");
      return;
      }
   if (pid==0){
      if (execvp(argv[0],argv)==-1)
         perror("cannot execute pmap (linux, solaris)");
         
      argv[0]="procstat"; argv[1]="vm"; argv[2]=elpid; argv[3]=NULL;   
      if (execvp(argv[0],argv)==-1)/*No hay pmap, probamos procstat FreeBSD */
         perror("cannot execute procstat (FreeBSD)");
         
      argv[0]="procmap",argv[1]=elpid;argv[2]=NULL;    
            if (execvp(argv[0],argv)==-1)  /*probamos procmap OpenBSD*/
         perror("cannot execute procmap (OpenBSD)");
         
      argv[0]="vmmap"; argv[1]="-interleave"; argv[2]=elpid;argv[3]=NULL;
      if (execvp(argv[0],argv)==-1) /*probamos vmmap Mac-OS*/
         perror("cannot execute vmmap (Mac-OS)");      
      exit(1);
  }
  waitpid (pid,NULL,0);
}

int memory(char* tokens[], int ntokens){
    
    bool opt_funcs = has_token(tokens,ntokens, "-funcs");
    bool opt_blocks = has_token(tokens,ntokens, "-blocks");
    bool opt_vars = has_token(tokens,ntokens, "-vars");
    bool opt_all = has_token(tokens,ntokens, "-all");
    bool opt_pmap = has_token(tokens,ntokens, "-pmap");
    //optional
    bool opt_varsizes = has_token(tokens,ntokens, "-varsizes");

    //local variables
    int lVar1 = 42;
    int lVar2 = 1337;
    int lVar3 = 1312;

    //global variables

    //static variables
    static int sVar1 = 42;
    static int sVar2 = 1337;
    static int sVar3 = 1312;

    static int uStaticVar1;
    static int uStaticVar2;
    static int uStaticVar3;
    //write all
    if(opt_vars || opt_all || ntokens == 1){
        printf("local variables: %p, %p, %p\n", &lVar1, &lVar2, &lVar3);
        printf("global variables: %p %p %p\n", &gVar1, &gVar2, &gVar3);
        printf("(U.I.) global variables: %p %p %p\n", &ugVar1, &ugVar2, &ugVar3);
        printf("static variables:  %p, %p, %p\n", &sVar1, &sVar2, &sVar3);
        printf("(U.I.) static Variables: %p %p %p\n", &uStaticVar1, &uStaticVar2, &uStaticVar3);
    }
    if(opt_funcs || opt_all || ntokens == 1){
        printf("Program functions %p %p %p\n", &allocate, &deallocate, &printMemoryList);
        printf("Library functions %p %p %p\n", &printf, &strtoul, &scanf);
    }
    if(opt_blocks || opt_all || ntokens == 1){
        printMemoryList();
    }
    if(opt_pmap){
        Do_pmap();
    }
    if(opt_varsizes){
        printf("sizeof(int): %lu\n",sizeof(int));
    }
    return 0; 
}


void Recursiva (int n)
{
  char automatico[TAMANO];
  static char estatico[TAMANO];

  printf ("parametro:%3d(%p) array %p, arr estatico %p\n",n,&n,automatico, estatico);
 if (n>0)
    Recursiva(n-1);
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
int readfile(char* tokens[], int ntokens){
    if(ntokens == 4){ //readfile file addr cont
        char* f = tokens[1]; //missing conversion functions
        void *p = (void*)strtoull(tokens[2], NULL, 16);
        size_t cont = strtoul(tokens[3],NULL,10);
        LeerFichero(f,p,cont);
    }else{
        perror("wrong syntax");
    }
    return 0;
}
int writefile(char* tokens[], int ntokens){
    if(ntokens == 4){ //writefile file addr cont
        //write();
    }
    return 0;
}
int _read(char* tokens[], int ntokens){
    //read df addr cont
    if(ntokens == 4){    
        unsigned long df = strtoul(tokens[1],NULL, 10);
        void * p = tokens[2];
        int cont = strtoul(tokens[3],NULL,10);
        int n = 0;
        int aux;
        if ((n=read(df,p,cont))==-1){
            aux=errno;
            close(df);
            errno=aux;
        return -1;
    }
   }
   return 0;
}
int _write(char* tokens[], int ntokens){
    return 0;
}
int recurse(char* tokens[], int ntokens){
    if(ntokens== 1){
        //printUsage
        return 0;
    }
    if(ntokens == 2 ){
        Recursiva(strtoul(tokens[1],NULL,10));
        return 0;
    }
    return 0;
}