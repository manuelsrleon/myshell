//Autores
/*  Manuel Santamariña Ruiz de León (manuel.santamarina)
 (some remnants are from Mateo Rivela Santos, who was my partner year/s before*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include "src/common/common.h"


#define AUTOR_1_N "Manuel Santamariña Ruiz de León"
#define AUTOR_1_L "manuel.santamarina"
#define AUTOR_2_N "Mateo Rivela Santos"
#define AUTOR_2_L "mateo.rivela"

//P0
#include "src/p0/clangintro.h"
#include "src/list/dynamic_list.h"
tList List;
//P1
#include "src/p1/filesystems.h"
//P2
#include "src/p2/memory.h"

#define MAX_LINE 1024
#define MAX_TOKENS 100

void imprimirPrompt(){
    char name[32];
    char cwd[100] = "current working directory";
    getcwd(cwd, 100);

    gethostname(name,32);
    printf("%s@%s:%s$ ",getlogin(),name,cwd);
}
int parseString(char * cadena, char * trozos[]) {
    int i=1;
    if ((trozos[0]=strtok(cadena," \n\t"))==NULL)
        return 0;
    while ((trozos[i]=strtok(NULL," \n\t"))!=NULL)
        i++;

    return i;
}
//Métodos
//autores
int authors(char *tokens[], int ntokens) {
    //TODO
    Author manuel = {"Manuel Santamariña Ruiz de León", "manuel.santamarina",false};
    Author mateo =  {"Mateo Rivela Santos", "mateo.rivela",true};

    struct Author* authorArray[] = {&manuel, &mateo};
    int nauthors = sizeof (authorArray) / sizeof(authorArray[0]);

    
    autores(tokens,ntokens,authorArray,nauthors);
    return 0;    
}
int infosys(char *tokens[], int ntokens){
    struct utsname sysinfo;

    if( uname( &sysinfo ) == -1 ) {
        perror( "uname" );
        return EXIT_FAILURE;
    }
    printf( "Nombre de sistema  : %s\n", sysinfo.sysname );
    printf( "Nombre de equipo: %s\n", sysinfo.nodename );
    printf( "Versión de kernel: %s\n", sysinfo.release );
    printf( "version name : %s\n", sysinfo.version );
    return EXIT_SUCCESS;
}

int __exit(char *tokens[], int ntokens) {
    exit(1);
    return 1;
}
int instruction_not_found(char* tokens[], int ntokens){
    
    printf("ERROR: Command %s not found",tokens[0]);
    return 1;
}

struct cmd cmds[] = {
        //help format: "Usage: <command usage>\n<cmd-description>\n\nOptions:\n<option>\t<noption-text>"
        //P0
        {"authors", authors, "Usage: authors [-l|-n]\nPrints the names and logins of the program authors.\n\nOptions:\n-l\tPrint only the logins\n-n\tPrint only the names"},
        {"pid", pid,"Usage: pid [-p]\nPrints the pid of the process executing the shell.\n\n"},
        // {"chdir", chdir,"Usage: carpeta [direct]\nChanges the current working directory of the shell to \"direct\" (using the \"chdir\" system call). When invoked without arguments it prints the current working directory (using the \"getcwd\" system call)."},
        // {"date", date,"Usage: fecha [-d|-h]\nWithout arguments it prints both the current date and the current time.\n\nOptions:\n-d\tPrint the current date in the format DD/MM/YYYY.\n-h\tPrint the current time in the format hh:mm:ss"},
        // {"time", __time,"Usage: time\nPrints information on the machine running the shell (as obtained via the \"uname\" system call/library function)."},
        {"hist", hist, "Usage: hist [-c | N]\nShows/clears the \"historic\" of commands executed by this shell. In order to do this, a list to store all the commands input to the shell must be implemented.\n\nOptions:\n-c\t Clear the historic\n-N\tPrints the first N commands"},
        // {"comand", command, "Usage: command [N]\nRepeats command number N (from historic list)"},
        // {"open", open, ""},
        // {"close",close, ""},
        // {"dup",dup, ""},
        // {"listopen",listopen, ""},
        // {"infosys",infosys, ""},
        // hacer hist
        // {"help", ayuda,"Usage: help [cmd]\n\"help\" displays a list of available commands. \"help cmd\" gives a brief help on the usage of command \"cmd\""},
        {"quit", __exit,"Usage: fin\nEnds the shell"},
        {"exit",__exit,"Usage: salir\nEnds the shell"},
        {"bye",__exit,"Usage: bye\nEnds the shell"},
        //P1        
        {"create", create, "Usage: create [-f] [name]\nCreates files or directories.\n\n"},
        {"stat", _stat, "Usage: create [name]\nCreates files or directories.\n\n"},
        {"list", list, "Usage: list [name]\nGives information on files or directories\n\n"},
        {"delete", _delete, "Usage: delete [name]\ndeletes files and/or empty directories\n\n"},
        // {"deltree", deltree, "Usage: deltree [name]\ndeletes files and/or non empty directories recursively\n\n"},
        //P2
        {"malloc",p2_malloc,""},
        {"memfill",p2_memfill,""},
        {"memdump",p2_memdump,""},
        //P3
        {NULL, NULL,"you shouldn't be able to read this."}
};

int ayuda(char *tokens[], int ntokens,char *arg[],char *env[]) {
    int i = 0;
    while(cmds[i].cmd_name != NULL){
        if(!strcmp(tokens[1],cmds[i].cmd_name)){
            printf("%s", cmds[i].cmd_help);
            return 0;
        }
    i++;
    }
    perror("Command not found");
    return 1;
    
}
int __ayuda(char *tokens[], int ntokens){
    int i = 0;
    while(cmds[i].cmd_name != NULL){
        if(tokens[1] != NULL){
            if(strcmp(tokens[1],cmds[i].cmd_name) == 0){

                if(cmds[i].cmd_help != NULL){
                    printf("%s\n\n",cmds[i].cmd_help);
                }else{
                    perror("No help found for that command");
                }
                return 0;

            }
        }
        i++;
    }
    if(tokens[1] != NULL){
        perror("No help found for that command");
    }else if(ntokens == 1){
        printf("Usage: ayuda [cmd]\n\"ayuda\" displays a list of available commands. \"ayuda cmd\" gives a brief help on the usage of command \"cmd\"\n\n");
    }
    return 0;
}

//si quiero insertar al final inserto en 0
int processCmd(char *tokens[], int ntokens,char *arg[],char *env[]) {
    bool commandFound = false;
    tItemL item;
    strcpy(item.command, *tokens );

     for(int i=0; cmds[i].cmd_name != NULL; i++) {
         if(strcmp(tokens[0],cmds[i].cmd_name) == 0){
            commandFound = true;
            return cmds[i].cmd_fun(tokens, ntokens);
         }
     }
    if(!commandFound){
        printf("Command %s not found.\n",tokens[0]);
        return 0;
    }
    insertItem(item, NULL, &List);
    return 0;
}

int hist(char *tokens[],int ntokens){
    int i = 0;
    if(ntokens==1){
        if(!isEmptyList(List)){
            tPosL current = first(List);

            while (current!=last(List)){
                printf("%i > %s %s\n",i,getItem(current,List).command,getItem(current,List).parameters);
                current=next(current,List);
                i++;
            }
            printf("%i > %s %s\n",i,getItem(current,List).command,getItem(current,List).parameters);

        }else{
            printf("void2\n");
        }
    }else if(strcmp(tokens[1],"-c")==0){
        if(!isEmptyList(List)){
            tPosL current = first(List);
            tPosL current2;
            while (current!=last(List)){
                current2 = next(current,List);
                deleteAtPosition(current,&List);
                current = current2;
            }
        }else if(strcmp(tokens[1],"-N")==0){
            if(!isEmptyList(List)){
                printf("check");
                tPosL current = first(List);
                printf("%s %s\n",getItem(current,List).command,getItem(current,List).parameters);
            }else{
                printf("List is currently empty.\n");
            }
        }
    }
    return i;
}

int main(int argc, char *argv[], char * envp[]){
    char line[MAX_LINE];
    char *tokens[MAX_TOKENS];
    int ntokens;
    int end = 0;
    createEmptyList(&List);
    // mList LM;
    // createEmptyListM(&LM);
    // pList LP;
    // createEmptyListP(&LP);

    while(!end) {
        imprimirPrompt();
        fgets(line,MAX_LINE,stdin);
        ntokens = parseString(line, tokens);
        end = processCmd(tokens, ntokens, argv,envp);
    }

    return 0;
}

