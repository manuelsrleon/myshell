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
#include <ctype.h>

//p0
#include "modules/p0-clangintro.h"
//p1
#include "modules/p1-filesystems.h"

#include "modules/cmdlist/cmdlist.h"
//p2
#include "modules/p2-memory.h"
#include "modules/memorylist/memorylist.h"

#include "modules/common/common.h"

// #include "modules/common/common.c"

#define MAX_LINE 1024
#define MAX_TOKENS 100

CmdList commandList;

int __exit(char *tokens[], int ntokens) {
    exit(1);
    return 1;
}
void debug(char* message){
    printf("%s", message);
    fflush(stdout);
}
int hist(char *tokens[], int ntokens, char *arg[], char *env[]);
int ayuda(char *tokens[], int ntokens);
struct cmd cmds[] = {
        //help format: "Usage: <command usage>\n<cmd-description>\n\nOptions:\n<option>\t<noption-text>"
        //P0
        {"authors", authors, "Usage: authors [-l|-n]\nPrints the names and logins of the program authors.\n\nOptions:\n-l\tPrint only the logins\n-n\tPrint only the names"},
        {"pid", pid,"Usage: pid [-p]\nPrints the pid of the process executing the shell.\n"},
        {"ppid", ppid,"Prints the pid of the shell's parent process"},
        {"cd", cd, "Usage: cd [dir]\nChanges the current working directory of the shell to \"direct\" (using the \"chdir\" system call). When invoked without arguments it prints the current working directory (using the \"getcwd\" system call)."},
        {"date", date,"Usage: fecha [-d|-h]\nWithout arguments it prints both the current date and the current time.\n\nOptions:\n-d\tPrint the current date in the format DD/MM/YYYY.\n-h\tPrint the current time in the format hh:mm:ss"},
        // {"time", __time,"Usage: time\nPrints information on the machine running the shell (as obtained via the \"uname\" system call/library function)."},
        {"historic", hist, "Shows the historic of commands executed by this shell. In order to do this, a list to store all the commands input to the shell must be implemented. – historic Prints all the comands that have been input with their order number – historic N Repeats command number N (from historic list)  – historic -N Prints only the last N comands Students are free to decide whether historic stars numbering commands at 0 or at 1. Hypothetically, there’s a scenario where trying to repeat a historic command could yield an infinite loop or a stack overflow  (depending on how it is coded), so students may choose to not storecalls to historic N itself in the historic list if they want so (See the NOTES ON LIST IMPLEMENTATIONS at the end of this document)"},
        // {"comand", command, "Usage: command [N]\nRepeats command number N (from historic list)"},
        // {"open", open, ""},
        // {"close",close, ""},
        // {"dup",dup, ""},
        // {"listopen",listopen, ""},
        {"infosys",infosys, ""},
        {"help", ayuda,"Usage: help [cmd]\n\"help\" displays a list of available commands. \"help cmd\" gives a brief help on the usage of command \"cmd\""},
        {"quit", __exit,"Usage: fin\nEnds the shell"},
        {"exit",__exit,"Usage: salir\nEnds the shell"},
        {"bye",__exit,"Usage: bye\nEnds the shell"},
        //P1        
        {"makefile", makefile, "creates a file"},
        {"makedir", makedir, "creates a directory"},
        {"listfile", listfile, "gives information on files or directories"},
        {"cwd", cwd, "prints current working directory"},
        {"listdir", listdir, "lists directories contents"},
        // {"reclist", reclist, "lists directories recursively (subdirectories after)"},
        // {"revlist", revlist, "lists directories recursively (subdirectories before)"},
        {"erase", erase, "deletes files and/or empty directories"},
        {"delrec", delrec, "deletes files and/or non empty directories recursively"},
        // {"create", create, "Usage: create [-f] [name]\nCreates files or directories.\n\n"},
        // {"stat", _stat, "Usage: create [name]\nCreates files or directories.\n\n"},
        // {"list", list, "Usage: list [name]\nGives information on files or directories\n\n"},--
        // {"delete", _delete, "Usage: delete [name]\ndeletes files and/or empty directories\n\n"},
        // {"deltree", deltree, "Usage: deltree [name]\ndeletes files and/or non empty directories recursively\n\n"},
        //P2
        {"allocate", allocate, ""},
        // {"deallocate", deallocate, ""},
        {"memfill", memfill, ""},
        {"memdump", memdump, ""},
         {"memory", memory, ""},
        // {"readfile", readfile, ""},
        // {"writefile", writefile, ""},
        // {"read", read, ""},
        // {"write", write, ""},
        {"recurse", recurse, ""},
        //P3
        {NULL, NULL,"you shouldn't be able to read this."}
};

int ayuda(char *tokens[], int ntokens) {
    
    if(ntokens == 1){
        int i = 0;    
        while(cmds[i].cmd_name != NULL){
            printf("%s ", cmds[i].cmd_name);
            i++;
        }
        printf("\n");
        return 0;
    }else{
        int j = 0;
        while(cmds[j].cmd_name != NULL){
            if(!strcmp(tokens[1],cmds[j].cmd_name)){
                printf("%s", cmds[j].cmd_help);
                return 0;
            }
        j++;
        }
        perror("Command not found");
        return 0;
    }
    
}
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

int processCmd(char *tokens[], int ntokens,char *arg[],char *env[]) {
    bool command_not_found = true; 
    //Iterate through command list
    for(int i=0; cmds[i].cmd_name != NULL; i++) {
        if(strcmp(tokens[0],cmds[i].cmd_name) == 0){
            command_not_found = false;
        return cmds[i].cmd_fun(tokens, ntokens);
        }
    }
    if(command_not_found){
        printf("Unrecognized command\n");
        return 0;
    }
    return 1;
}
void saveCmd(char *line){
    //reservamos tamaño línea para newCommand
    char* newCommand = malloc(MAX_LINE);
    //copiamos contenido de line en newCommand
    if(newCommand == NULL){
        return;
    }
    strcpy(newCommand,line);
    CmdListCmd cmdToSave = { .line = newCommand};
    insertCmdListCmd(cmdToSave,&commandList);
    //add free
}
int hist(char *tokens[], int ntokens, char *arg[], char *env[]){

    //bool n_commands_present = false;

    if(isEmptyCmdList(commandList)){
        printf("La lista de comandos está vacía.");
        return 0;
    }else if (ntokens == 1){
        CmdListPosition currentNode = commandList;
        int index = 0;

        while(currentNode->next != NULL){
            printf("%d->%s",index,currentNode->command.line);
            currentNode = currentNode->next;
            index++;
        }
        printf("%d->%s",index,currentNode->command.line);
        return 0;
    }else if(ntokens == 2){
        
        if(isNumber(tokens[1])){
            
            CmdListPosition currentNode = commandList;
            long repeated_command = strtol(tokens[1],NULL,10);

            while(currentNode->next !=NULL && repeated_command != 0){
                currentNode = currentNode->next;
                repeated_command--;
                
            }
            saveCmd(currentNode->command.line);
            int ntokens = parseString(currentNode->command.line,tokens);
            processCmd(tokens,ntokens, NULL, NULL);
            return 0;
        }else{
            if(tokens[1][0] == '-'){
                //long number_of_last_commands = strtol(tokens[1][1],NULL,10);
                //printf("Muestra los últimos %ld comandos", number_of_last_commands);
                return 0;
            }
        }
    }
    return 0;
}

int main(int argc, char *argv[], char * envp[]){
    createEmptyCmdList(&commandList);

    char line[MAX_LINE];
    char *tokens[MAX_TOKENS];
    int ntokens;
    int end = 0;
    
    while(!end) {
        imprimirPrompt();
        fgets(line,MAX_LINE,stdin);
        //hay que meter strcpy
        saveCmd(line);
        ntokens = parseString(line, tokens);
        end = processCmd(tokens, ntokens, argv,envp);
    }

    return 0;
}
