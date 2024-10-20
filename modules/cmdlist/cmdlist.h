
typedef struct CmdListNode *CmdListPosition;
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef CMDLIST_H
    #define CMDLIST_H   
    #include "../common/common.h"

typedef struct CmdListNode *CmdListPosition;

typedef struct CmdListCmd {
    char* line;
}CmdListCmd;

struct CmdListNode {
    CmdListCmd command;
    CmdListPosition next;
};

typedef CmdListPosition CmdList;

void createEmptyCmdList(CmdList* CmdList);

bool isEmptyCmdList(CmdList CmdList);

int insertCmdListCmd(CmdListCmd command, CmdList* CmdList);

//CmdListPosition first(CmdList CmdList);

//CmdListPosition last(CmdList CmdList);

//CmdListPosition next(CmdListPosition position, CmdList cmdList);

//CmdListPosition previous(CmdListPosition position, CmdList CmdList);


//CmdListItem getCmdListCmd(CmdListPosition position, CmdList CmdList);

//CmdListPosition findCmdListItem(CmdListCmd cmd, CmdList cmdList);

#endif