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
#include <pwd.h>

int getuid_cmd(char* tokens[], int ntokens){
    //getuid
    if(ntokens == 1){
        uid_t r_uid = getuid(); //get real credential
        uid_t e_uid = geteuid(); //get effective credential
        struct passwd* r_passwd = getpwuid(r_uid); 
        struct passwd* e_passwd = getpwuid(e_uid);
        printf("Real credential: %d, (%s)\n",r_uid, r_passwd->pw_name);
        printf("Effective credential:  %d, (%s)\n",e_uid, e_passwd->pw_name);

    }else{
        throwWrongSyntaxError("getuid");
        return 0;
    }
    return 0;
}
int setuid_cmd(char* tokens[], int ntokens) { 

    bool opt_l = has_token(tokens,ntokens,"-l");
    if(ntokens == 2) { //setuid id 
        uid_t uid = strtoul(tokens[1],NULL,10);
        if(setuid(uid) != 0){
            perror("setuid");
        }
    }else if(ntokens==3 && opt_l){ //setuid -l id

        struct passwd* l_pw;
        if((l_pw = getpwnam(tokens[2])) == NULL){
            perror("setuid");
        }

        if(setuid(l_pw->pw_uid) != 0){
            perror("setuid");
        };
    }else{
        perror("setuid");
    }
    return 0;
}
int showvar_cmd(char* tokens[], int ntokens);
int changevar_cmd(char* tokens[], int ntokens);
int subsvar_cmd(char* tokens[], int ntokens);
int environ_cmd(char* tokens[], int ntokens);
int fork_cmd(char* tokens[], int ntokens){
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork failed");
        return 0;
    } else if (pid == 0) {
        // In child process
        printf("Executing process %d\n",getpid());
    } else {
        // In parent process
        int status;
        waitpid(pid, &status, 0); // Wait for the child to finish
        return 0;
    }
    return 0;
}
int search_cmd(char* tokens[], int ntokens);
int exec_cmd(char* tokens[], int ntokens);
int execpri_cmd(char* tokens[], int ntokens);
int fg_cmd(char* tokens[], int ntokens);
int fgpri_cmd(char* tokens[], int ntokens);
int back_cmd(char* tokens[], int ntokens);
int backpri_cmd(char* tokens[], int ntokens);
int listjobs_cmd(char* tokens[], int ntokens);
int deljobs_cmd(char* tokens[], int ntokens);
