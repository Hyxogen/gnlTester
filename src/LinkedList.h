//
// Created by Daan Meijer on 11/1/21.
//

#ifndef TESTER_LINKEDLIST_H
#define TESTER_LINKEDLIST_H

#include "../include/tester.h"

typedef struct S_LinkedList {
	void *m_Content;
	struct S_LinkedList *m_Next;
} LinkedList;

LinkedList *CreateElement(void *content);

void AddBack(LinkedList **list, LinkedList *element);

void RemoveElements(LinkedList **list, t_bool (*equal)(const void *, const void *), const void *sample);

size_t GetSize(const LinkedList *list);

void ClearList(LinkedList **list);
#endif //TESTER_LINKEDLIST_H
