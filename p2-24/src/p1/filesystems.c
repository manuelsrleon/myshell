#include "filesystems.h"
#include <stdbool.h>
#include <stdio.h>
#include <sys/stat.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>
#include <dirent.h>

#include "../ayuda/ayudaP1.c"

void printCurrentDirectory(){
    char cwd[100] = "current working directory";
    getcwd(cwd, 100);
    printf("%s\n",cwd);
}
bool escarpeta(char *name){

    struct stat st;
    lstat(name,&st);
    return S_ISDIR(st.st_mode);

}

void debug_tokens(char *tokens[], int ntokens){
    for(int i = 0; i < ntokens; i++){
        printf("%s",tokens[i]);
    }
}

int has_token(char*tokens[], int ntokens, char* target_token){
    for(int i = 0; i < ntokens; i++){
        if(strcmp(tokens[i],target_token) == 0)
        return 1;
    }
    return 0;
}

int find_token(char*tokens[], int ntokens, char* target_token){
    for(int i = 0; i < ntokens; i++){
        if(strcmp(tokens[i],target_token) == 0)
        return i;
    }
    return -1;
}

int createFile(char *name){
    FILE *fd; 
    fd = fopen(name,"w");

    if(fd == NULL){
        printf("Failed to create file %s",name);
        perror("fopen");
        return 1;
    }

    fclose(fd);
    return 0;
}

int createDirectory(char *dirname){
    if(mkdir(dirname, 0755) == 0){
        return 0;
    } else {
        printf("Can't create directory %s\n",dirname);
        perror("mkdir");
        return 1;
    }
}
int create(char *tokens[], int ntokens){
    
    
    if(ntokens == 1){
        printCurrentDirectory();
        return 0;
    }
    bool file_mode = has_token(tokens,ntokens,"-f");

    int filename_start_index = 1;

    if(file_mode){
        filename_start_index = 2;
    }

    for(int i = filename_start_index; i < ntokens; i++){
        if(file_mode){
            /*Creates file ntokens[i<]*/
            createFile(tokens[i]);
        }else{
            /*Creates directory*/
            createDirectory(tokens[i]);
        }
        
    }
    return 0;
}

int _stat(char *tokens[], int ntokens){
    
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
    
    return 0;
}

int list(char *tokens[], int ntokens){

    bool _reca = false;
    bool _recb = false;
    bool _hid = false;

    _reca = has_token(tokens, ntokens, "-reca");
    _recb = has_token(tokens, ntokens, "-recb");
    _hid = has_token(tokens, ntokens, "-hid");

    bool _long = false;
    bool _link = false;
    bool _acc = false; 

    _long = has_token(tokens, ntokens, "-long");
    _link = has_token(tokens, ntokens, "-link");
    _acc = has_token(tokens, ntokens, "-acc");

    int number_of_options = _reca + _recb + _hid + _long + _link + _acc;

    char dirname[100];
    strcpy(dirname,tokens[number_of_options+1]);
    if(ntokens==1){
        //print current working directory
    }else{
        //arg name list current directory

        DIR *d;
        struct dirent *dir; 

        d = opendir(dirname);
        
        if(d){
            //prints out current dir
            printf("%s","===========.\n");
            while((dir = readdir(d)) != NULL){
             struct stat st;
             if(lstat(dir->d_name, &st) == -1){
                perror("stat");
                //TODO listado -long
             };

            //prints out name, depending on if it's hidden or not.
            if(_hid){
                    printf("\t  %s \n" ,dir->d_name);
                }else if(dir->d_name[0]!='.'){
                    printf("\t  %s \n",dir->d_name);
                }
            }
            return 0;
        }else{
            perror("opendir");
            return 1;
        }

    }
    return 1;
}
int _delete(char *tokens[], int ntokens){

    if(ntokens == 1){
        printCurrentDirectory();
        return 0;
    }
    
    for(int i=1;i<ntokens;i++){
        remove(tokens[i]);
    }
    return 0;
}

void deltree_innerfunc(char *name){
    if(escarpeta(name)){
        DIR *d;
        struct dirent *dir;
        d = opendir(name);
        if (d) {
            while ((dir = readdir(d)) != NULL) {
                if(strcmp(dir->d_name,".")!=0 && strcmp(dir->d_name,"..")!=0){
                    chdir(name);
                    if(escarpeta(dir->d_name)){

                        deltree_innerfunc(dir->d_name);
                        rmdir(dir->d_name);
                    } else{
                        remove(dir->d_name);
                    }
                    chdir("..");
                }
            }
            closedir(d);
            rmdir(name);
        }
    }
}



int deltree(char *tokens[], int ntokens){
    if(ntokens == 1){
        printCurrentDirectory();
    }else{
        for(int i=1;i<ntokens;i++){
        deltree_innerfunc(tokens[i]);
    }
    }
    return 0;
}

