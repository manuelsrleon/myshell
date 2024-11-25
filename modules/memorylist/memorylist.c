#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "memorylist.h"
#include <stdio.h>
typedef struct MemoryListNode *MemoryListPosition;

typedef MemoryListPosition MemoryList;

void createEmptyMemoryList(MemoryList* list){
    *list = NULL;
}

bool createMemoryNode(MemoryListPosition *position){
    *position = malloc(sizeof(struct MemoryListNode));
    if(*position == NULL) return false;
    else return true;
}

bool isEmptyMemoryList(MemoryList memoryList){
    return (memoryList == NULL);
}

int insertMemoryListElement(MemoryListElement element, MemoryList *memoryList){
    MemoryListPosition newNode;
    if(!createMemoryNode(&newNode)){
        return 1;
    }else{
        newNode->element = element;
        newNode->next = NULL;
        if(isEmptyMemoryList(*memoryList)){//Si la lista está vacía
            *memoryList = newNode;
        }else{//Si no está vacía
            //Recorremos la lista hasta encontrar el último elemento
            MemoryListPosition currentPosition = *memoryList;
            // for(currentPosition = *memoryList; currentPosition->next != NULL; currentPosition = currentPosition->next){
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