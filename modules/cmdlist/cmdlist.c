#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "cmdlist.h"
#include <stdio.h>
typedef struct CmdListNode *CmdListPosition;

typedef CmdListPosition CmdList;

void createEmptyCmdList(CmdList* list){
    *list = NULL;
}

bool createNode(CmdListPosition *position){
    *position = malloc(sizeof(struct CmdListNode));
    if(*position == NULL) return false;
    else return true;
}

bool isEmptyCmdList(CmdList cmdList){
    return (cmdList == NULL);
}

int insertCmdListCmd(CmdListCmd command, CmdList *cmdList){
    CmdListPosition newNode;
    if(!createNode(&newNode)){
        return 1;
    }else{
        newNode->command = command;
        newNode->next = NULL;
        if(isEmptyCmdList(*cmdList)){//Si la lista está vacía
            *cmdList = newNode;
        }else{//Si no está vacía
            //Recorremos la lista hasta encontrar el último elemento
            CmdListPosition currentPosition = *cmdList;
            // for(currentPosition = *cmdList; currentPosition->next != NULL; currentPosition = currentPosition->next){
            // }
            while(currentPosition->next != NULL){
            
                currentPosition = currentPosition->next;
                
            }
            currentPosition->next = newNode;
            return 0;
        }
        return 1;
    }
}