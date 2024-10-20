#ifndef COMMON_H
    #define COMMON_H
struct cmd {
    char *cmd_name;
    int (*cmd_fun)();
    char *cmd_help;
};

void notImplemented();
void printCurrentDirectory();
int has_token(char* tokens[], int ntokens, char* targetToken);
int isNumber(char *token);
void throwWrongSyntaxError(char* cmdName);
char* getLastSegmentFromPath(char path[]);
#endif