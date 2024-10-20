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