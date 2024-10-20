#include <stdbool.h>
typedef struct Author{
    char* name; 
    char* login;
    bool honourable;
} Author;

int autores(char *tokens[], int ntokens, struct Author* authors[], int nauthors);
int pid(char *tokens[], int ntokens);
int date(char *tokens[], int ntokens);
int __time(char *tokens[], int ntokens);
int _chdir(char *tokens[], int ntokens);
int hist(char *tokens[], int ntokens);
int command(char *tokens[], int ntokens);
int open(char *tokens[], int ntokens);
int _close(char *tokens[], int ntokens);
int dupefd(char *tokens[], int ntokens);
int listopen(char *tokens[], int ntokens);
int infosys(char *tokens[], int ntokens);
int help(char *tokens[], int ntokens);
int quit(char *tokens[], int ntokens);