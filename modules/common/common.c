#ifndef COMMON_C
    #define COMMON_C
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
void printCurrentDirectory(){
    char cwd[100] = "current working directory";
    getcwd(cwd, 100);
    printf("%s\n",cwd);
}

int has_token(char*tokens[], int ntokens, char* target_token){
    for(int i = 0; i < ntokens; i++){
        if(strcmp(tokens[i],target_token) == 0)
        return 1;
    }
    return 0;
}

void notImplemented(char* funcname){
    printf("%s %s\n",funcname,strerror(errno));
}

int isNumber(char *token) {
    char *endptr;

    strtol(token, &endptr, 10);

    if(*endptr == '\0'){
        if(token[0] == '-') {
            return 0;
        }
        return 1;
    }
    return 0;
}
char* getLastSegmentFromPath(char path[]){
    char* token;
    token = strtok(path,"/");
    char* previousFilename;
    while(token != NULL){
        previousFilename = token;
        token = strtok(NULL,"/");
    }
    return previousFilename;
}
void throwWrongSyntaxError(char* cmdName){
    perror(strcat("Wrong syntax for command ",cmdName));
}
#endif