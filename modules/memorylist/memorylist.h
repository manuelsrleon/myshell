
typedef struct MemoryListNode *MemoryListPosition;
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#ifndef MEMORYLIST_H
    #define MEMORYLIST_H   
    #include "../common/common.h"

typedef struct MemoryListNode *MemoryListPosition;

typedef struct MemoryListElement {
    char* element;
}MemoryListElement;

struct MemoryListNode {
    MemoryListElement element;
    MemoryListPosition next;
};

typedef MemoryListPosition MemoryList;

void createEmptyMemoryList(MemoryList* MemoryList);

bool isEmptyMemoryList(MemoryList MemoryList);

int insertMemoryListElement(MemoryListElement command, MemoryList* MemoryList);

//MemoryListPosition first(MemoryList MemoryList);

//MemoryListPosition last(MemoryList MemoryList);

//MemoryListPosition next(MemoryListPosition position, MemoryList MemoryList);

//MemoryListPosition previous(MemoryListPosition position, MemoryList MemoryList);


//MemoryListItem getMemoryListElement(MemoryListPosition position, MemoryList MemoryList);

//MemoryListPosition findMemoryListItem(MemoryListElement Memory, MemoryList MemoryList);

#endif