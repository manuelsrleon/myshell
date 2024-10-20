#define AUTHOR_1_N "Manuel Santamariña Ruiz de León"
#define AUTHOR_1_L "manuel.santamarina"

int authors(char *tokens[], int ntokens);
int pid(char *tokens[], int ntokens);
int ppid(char *tokens[], int ntokens);
int cd(char *tokens[], int ntokens);
int infosys(char *tokens[], int ntokens);
int date(char* tokens[], int ntokens);

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