#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <stdbool.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#include "common/common.h"
#include "./p1-filesystems.h"
#include "./ayuda/ayudaP1.c"

int exec_getcwd(){
    char cwd[1024];
    if(getcwd(cwd,sizeof(cwd)) != NULL) {
        printf("%s\n",cwd);
        return 0;
    }
    perror("getcwd error");
    return 1;
}



int makefile(char *tokens[], int ntokens) {
    if(ntokens == 1){
    //makefile
        exec_getcwd();
        return 0;
    }else if(ntokens == 2){
    //makefile [name]
        FILE *fptr;
        fptr = fopen(tokens[1], "w");
        fclose(fptr);
        return 0;
    }else{
    //wrong syntax
        throwWrongSyntaxError("makefile");
        return 1;
    }
}

int makedir(char *tokens[], int ntokens){
    if(ntokens == 1){
    //makedir
        exec_getcwd();
        return 0;
    }else if(ntokens == 2){
        struct stat st = {0};
        if(stat(tokens[1],&st) == -1){
            mkdir(tokens[1],0700);
        }else{
            perror("");
            return 1;
        }
        
        return 0;
    }else{
    //wrong syntax
        throwWrongSyntaxError("makedir");
        return 1;
    }
}

int listfile(char *tokens[], int ntokens){
    switch (ntokens)
    {
    case 1:
        exec_getcwd();
        break;
    default:
    
    bool _long = false;
    bool _acc = false;
    bool _link = false;

    _long = has_token(tokens, ntokens, "-long");
    _acc = has_token(tokens, ntokens, "-acc");
    _link = has_token(tokens, ntokens, "-link");

    int number_of_options = (int)_long +(int)_acc + (int)_link;
    struct stat filestat;
    struct passwd *ownr;
    struct group *group;

    char path[128];
    
    for(int i=number_of_options+1; i < ntokens ;i++){
        strcpy(path,tokens[i]);
        stat(path, &filestat);

        ownr = getpwuid(filestat.st_uid);
        group = getgrgid(filestat.st_gid);

        char filename[8];
        strcpy(filename, getLastSegmentFromPath(path));
        
        //long stat
        if(_long){
            printf("%s %ld %ld %s %s %s %lld %s\n", ctime(&filestat.st_atime),(long)filestat.st_nlink, (long)filestat.st_ino,ownr->pw_name,group->gr_name,ConvierteModo2(filestat.st_mode),(long long)filestat.st_size, filename);
        }else{
            printf("%ld %s\n",filestat.st_size, filename);
        }
    
    }

        break;
    }
    return 0;
}
int cwd(char *tokens[], int ntokens){
    if(exec_getcwd() == 0){
        return 0;
    }
    return 1;
}
int listdir(char *tokens[], int ntokens){
    return 0;
}
int reclist(char *tokens[], int ntokens){
    return 0;
}
int revlist(char *tokens[], int ntokens){
    return 0;
}
int erase(char *tokens[], int ntokens){
    return 0;
}
int delrec(char *tokens[], int ntokens){
    return 0;
}