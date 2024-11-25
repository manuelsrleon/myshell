#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#define TAMANO 512
#include "common/common.h"

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
        p = malloc(tam); 
        printf("Asignados %lu bytes en %p\n",tam,p);
        //save in list
    }
    
    //allocate -shared cl
    if(ntokens==3 && opt_shared){
        
    }
    
    //allocate -mmap file perm
    if(ntokens==4 && opt_mmap){

    }
    //allocate -create cl n
    if(ntokens==4 && opt_create){

    }
    return 0;
}
int deallocate(char* tokens[], int ntokens){
    
    bool opt_malloc = has_token(tokens,ntokens, "-malloc");
    bool opt_mmap = has_token(tokens,ntokens, "-mmap");
    bool opt_create = has_token(tokens,ntokens, "-create");
    bool opt_shared = has_token(tokens,ntokens, "-shared");

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
    //deallocate -create cl n
    if(ntokens==4 && opt_create){

    }
    return 0;
}
// int memfill(char* tokens[], int ntokens);
// int memdump(char* tokens[], int ntokens);

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

// int readfile(char* tokens[], int ntokens);
// int writefile(char* tokens[], int ntokens);
// int read(char* tokens[], int ntokens);
// int write(char* tokens[], int ntokens);
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