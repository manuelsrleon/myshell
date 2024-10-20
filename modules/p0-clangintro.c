#define AUTHOR_1_N "Manuel Santamariña Ruiz de León"
#define AUTHOR_1_L "manuel.santamarina"
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "common/common.c"
#include "sys/utsname.h"
#include "./p0-clangintro.h"

int authors(char *tokens[], int ntokens) {
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
            
        if(opt_names && !opt_login){
            printf(AUTHOR_1_N);
        }else if(opt_login){
            printf(AUTHOR_1_L);
        }else{
            printf(AUTHOR_1_N);
            printf(" (%s)",AUTHOR_1_L);
        }
    }else{
        perror("Comando no reconocido\n"); 
        return 1;
    }
    printf("\n");
    return 0;
}

int pid(char *tokens[], int ntokens){
    printf("%d\n",getpid());
    return 0;
}

int ppid(char *tokens[], int ntokens){
    printf("%d\n",getppid());
    return 0;
}
int cd(char *tokens[], int ntokens){
    //get dir. second.
    char* dir = tokens[1];
    //0 == SUCCESS
    int chdir_result = chdir(dir);

    if(chdir_result == 0){
        //successful
        return 0;
    }else if (chdir_result == -1){
        perror("There has been a problem when changing directories.");
        return 1;
    }else{
        return 1;
    }
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

int date(char* tokens[], int ntokens){
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    bool opt_time = has_token(tokens,ntokens, "-t");
    bool opt_date = has_token(tokens,ntokens, "-d");

    //date
    if(!opt_time && !opt_date){
        printf("%02d/%02d/%d\n", tm.tm_mday, tm.tm_mon + 1,  tm.tm_year + 1900);
        printf("%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    //date -d 
    if(opt_date){
        printf("%02d/%02d/%d\n", tm.tm_mday, tm.tm_mon + 1,  tm.tm_year + 1900);
    }
    //date -t
    if(opt_time){
        printf("%02d:%02d:%02d\n", tm.tm_hour, tm.tm_min, tm.tm_sec);
    }
    return 0;
    
}

/*int _open(char* tokens[], int ntokens){
    //open
    bool opt_cr = has_token(tokens,ntokens, "cr");
    bool opt_ap = has_token(tokens,ntokens, "ap");
    bool opt_ex = has_token(tokens,ntokens, "ex");
    bool opt_ro = has_token(tokens,ntokens, "ro");
    bool opt_wo = has_token(tokens,ntokens, "wo");
    bool opt_tr = has_token(tokens,ntokens, "tr");
    //open [file] mode
    
    if( ntokens == 3 ){
        char* filename = tokens[1];
        return 0;
    }
    return 1;
}

int _close(char* tokens[], int ntokens){
    
    if(ntokens == 2){
        int fd = tokens[1];
        return 0;
    }
    return 1;
}

int _dup(char* tokens[], int ntokens){
    return 0;
}*/