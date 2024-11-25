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


void copyArgs(char *src[], char *dst[], int srcSize) {
    int j = 1;  // Destination array index
    for (int i = 1; i < srcSize; i++) {  // Start from index 1, skip the first string
        if (strcmp(src[i], "-hid") != 0) {  // Skip strings with value "-hid"
            dst[j] = src[i];
            j++;
        }
    }
    dst[j] = NULL;  // End the destination array with a NULL pointer
}

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
    //TODO FIX si el fichero no existe => error por no encontrarlo
    //TODO fix siempre 
    for(int i=number_of_options+1; i < ntokens ;i++){
        strcpy(path,tokens[i]);
        lstat(path, &filestat);

        ownr = getpwuid(filestat.st_uid);
        group = getgrgid(filestat.st_gid);

        char shownPath[128];
        //link
        if(_link && S_ISLNK(filestat.st_mode)){

            char realpath[64];
            readlink(path, realpath, 30);
            snprintf(shownPath,256,"%s -> %s",path, realpath);
        }else{
            strcpy(shownPath, path); 
        }
        time_t shownTime = (time_t)malloc(sizeof(time_t));
        if(_acc){
            shownTime = filestat.st_atime;
        }else{
            shownTime = filestat.st_mtime;
        }
        
        //long stat
        if(_long){
            printf("%s  %10ld\t%ld\t%s\t%s\t%s\t%lld\t%s\n", ctime(&shownTime),(long)filestat.st_nlink, (long)filestat.st_ino,ownr->pw_name,group->gr_name,ConvierteModo2(filestat.st_mode),(long long)filestat.st_size, shownPath);
        }else{
            printf("%10ld  %s\n",filestat.st_size, shownPath);
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
    bool _long = false;
    bool _link = false;
    bool _acc = false; 
    bool _hid = false; 

    _long = has_token(tokens, ntokens, "-long");
    _link = has_token(tokens, ntokens, "-link");
    _acc = has_token(tokens, ntokens, "-acc");
    _hid = has_token(tokens, ntokens, "-hid");

    
    int number_of_options = (int)_long + (int)_link + (int)_acc+(int)_hid;
    
    if(ntokens == 1){
        exec_getcwd();
    }else{
        for(int i = 1+number_of_options; i < ntokens; i++){
            char dirname[100];
            strcpy(dirname,tokens[i]);
            printf("%s",tokens[i]);
            //open dir
            DIR *d;
            struct dirent *dir;
            if((d = opendir(dirname)) == NULL){
                perror("opendir");
                continue;
            }
            
            if(d){
                printf("%s%s\n","********",dirname);
                
                while(( dir = readdir(d)) != NULL){
                    struct stat st; 
                    if(lstat(dir->d_name, &st) == -1){
                        perror("stat");
                    }
                    char path[128];
                    char* stat_tokens[50];
                    stat_tokens[0] = "listfile";
                    copyArgs(tokens,stat_tokens,ntokens);
                    int stat_ntokens = ntokens-(int)_hid;
                    strcpy(path, dir->d_name);
                    strcpy(stat_tokens[stat_ntokens-1], path);
                    if(_hid || dir->d_name[0] != '.'){
                        listfile(stat_tokens,stat_ntokens);
                    }
                }
            }
        }
    }
    
    return 0;
}
int reclist(char *tokens[], int ntokens){
    return 0;
}
int revlist(char *tokens[], int ntokens){
    return 0;
}
int erase(char *tokens[], int ntokens){
    
    if(ntokens == 1){
        exec_getcwd;
        return 0;
    }
    for(int i=1;i<ntokens;i++){
        if(remove(tokens[i]) == -1){
            perror("remove");
        }
    }
    return 0;
}
bool is_dir(char* path){
    struct stat st; 
    lstat(path,&st);
    return S_ISDIR(st.st_mode);
}
int delrec(char *tokens[], int ntokens){
    if(ntokens == 1){
        exec_getcwd();
    }else{
        for(int i = 1; i <ntokens; i++){
            if(is_dir(tokens[i])){
                DIR *d;
                struct dirent *dir;
                d = opendir(tokens[i]);
                if(d) {
                    while((dir = readdir(d)) != NULL){
                        if(strcmp(dir->d_name,".") && strcmp(dir->d_name,"..")!= 0){
                            
                        }
                    }
                }
            }else{

            }
        }
    }
    return 0;
}