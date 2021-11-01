//
// Created by Daan Meijer on 11/1/21.
//

#ifndef TESTER_LINKEDLIST_H
#define TESTER_LINKEDLIST_H

#include "../include/tester.h"

typedef struct S_LinkedList {
    void *m_Content;
    S_LinkedList* m_Next;
} LinkedList;

LinkedList* CreateElement(void *content);
void AddBack(LinkedList **list, LinkedList *element);
void RemoveElements(LinkedList **list, t_bool (*func)(void *content));
size_t GetSize(const LinkedList *list);

#endif //TESTER_LINKEDLIST_H
