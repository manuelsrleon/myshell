#include "clangintro.h"
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>

int autores(char *tokens[], int ntokens, struct Author* authors[], int nauthors) {
    //TODO fix :success on "unrecognized command"
    bool opt_login = false;
    bool opt_names = false;
    if(ntokens <= 3){
        //check for only_logins
        for(int i = 1; i < ntokens; i++){  
            opt_login = !strcmp(tokens[i],"-l");
        }
        //check for only_names
        for(int i = 1; i < ntokens; i++){
            opt_names = !strcmp(tokens[i],"-n");
        }
        printf("Autores:\n");
        //print author names given conditions
        for(int i = 0; i < nauthors; i++){
            if(authors[i]->honourable)
                printf("\nHonourable mention:\n");
            
            if(opt_names && !opt_login){
                printf("%s\n",authors[i]->name);
            }else if(opt_login){
                printf("%s",authors[i]->login);
            }else{
                printf("%s",authors[i]->name);
                printf(" (%s)\n",authors[i]->login);
            }
        }//endAuthors    
    }else{
        perror("Comando no reconocido\n");
        return 1;
    }
    printf("\n");
    return 0;
}
int pid(char *tokens[], int ntokens){
    if(ntokens == 1){
        printf("%d\n",getpid());
    }else if(ntokens == 2 && !strcmp(tokens[1], "-p")){
        printf("%d\n",getppid());
    }
    return 0;
}


int date(char *tokens[], int ntokens);
int __time(char *tokens[], int ntokens);
int _chdir(char *tokens[], int ntokens);
int command(char *tokens[], int ntokens);
int open(char *tokens[], int ntokens);
int _close(char *tokens[], int ntokens);
int dupefd(char *tokens[], int ntokens);
int listopen(char *tokens[], int ntokens);
int infosys(char *tokens[], int ntokens);
int help(char *tokens[], int ntokens);
int quit(char *tokens[], int ntokens);

