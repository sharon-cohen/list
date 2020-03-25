#include "list.h"

struct List {
    Element* array;
    int count;
    int maxSize;

    void (*freeElement)(Element);
    void (*printElement)(Element);
    int (*compare)(Element,Element);
};

List createList(int size, void (*freeElement)(Element), void (*printElement)(Element), int (*compare)(Element,Element)) {
    if (size < 1) return NULL;

    List newList = (List*)malloc(1*sizeof(struct List));
    if (NULL == newList) return NULL;

    newList->array = (Element*)calloc(size, sizeof(Element));
    if (NULL == newList->array) {
        free(newList);
        return NULL;
    }

    newList->count = 0;
    newList->maxSize = size;
    newList->freeElement = freeElement;
    newList->printElement = printElement;
    newList->compare = compare;

    return newList;
}

void freeList(List list) {
    if (NULL == list) return;
    if (NULL == list->freeElement) {
        free(list->array);
        free(list);
        return;
    }

    for (int i = 0; i < list->count; ++i)
        list->freeElement(list->array[i]);
    free(list->array);
    free(list);
}

void printList(List list) {
    if (NULL == list || NULL == list->printElement) return;

    for (int i = 0; i < list->count; ++i)
        list->printElement(list->array[i]);
    printf("\n");
}

void addElement(List list, Element ele) {
    if (NULL == list || NULL == ele || list->count == list->maxSize) return;

    list->array[list->count++] = ele;
}

void shiftLeft(List list, int index) {
    if (NULL == list || 0 > index || list->count <= index) return;

    for (int i = index; i < list->count-1; ++i)
        list->array[i] = list->array[i+1];
}

void removeElement(List list, int index) {
    if (NULL == list || 0 > index || list->count <= index) return;

    if (NULL != list->freeElement)
        list->freeElement(list->array[index]);
    
    shiftLeft(list, index);
    --list->count;
}

int findElement(List list, Element ele) {
    if (NULL == list || NULL == ele) return -1;

    for (int i = 0; i < list->count; ++i)
        if (0 == list->compare(ele, list->array[i]))
            return i;
    
    return -1;
}
