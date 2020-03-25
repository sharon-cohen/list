#pragma once

#include <stdlib.h>

typedef struct List* List;
typedef void* Element;

List createList(int size, void (*freeElement)(Element), void (*printElement)(Element), int (*compare)(Element,Element));
void freeList(List list);
void printList(List list);
void addElement(List list, Element ele);
void removeElement(List list, int index);
int findElement(List list, Element ele);