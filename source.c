#include <stdio.h>

#include "list.h"

void printInt(int* p) {
    printf("%d ", *p);
}

int compareInt(int* p1, int* p2) {
    return *p1 - *p2;
}

int main() {
    List mylist = createList(10,free,printInt,compareInt);

    for (int i = 20; i < 31; ++i) {
        int* p = (int*)malloc(sizeof(int));
        *p = i;
        addElement(mylist, p);
    }

    printList(mylist);
    removeElement(mylist, 4);
    printList(mylist);
    freeList(mylist);

    return 0;
}