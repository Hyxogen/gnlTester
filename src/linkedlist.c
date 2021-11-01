//
// Created by Daan Meijer on 11/1/21.
//

#include "linkedlist.h"
#include <stdlib.h>
#include "../include/tester.h"

LinkedList *CreateElement(void *content) {
    LinkedList *ret;

    ret = malloc(sizeof(LinkedList));
    if (!ret)
        return (NULL);
    ret->m_Content = content;
    return (ret);
}

void AddBack(LinkedList **list, LinkedList *element) {
    if (!*list) {
        *list = element;
        return element;
    }

    LinkedList *temp;
    temp = (*list);
    while (temp->m_Next)
        temp = temp->m_Next;
    temp->m_Next = element;
}

void RemoveElements(LinkedList **list, t_bool (*func)(void *content)) {
    LinkedList *previous;
    LinkedList *current;

    previous = NULL;
    current = *list;
    while (current) {
        if (!func(current))
            continue;
        if (previous) {
            previous->m_Next = current->m_Next;
            free(current);
            current = previous->m_Next;
        } else {
            *list = current->m_Next;
            free(current);
            current = *list;
        }
    }
}

size_t GetSize(const LinkedList *list) {
    size_t size;

    size = 0;
    while (list) {
        size++;
        list = list->m_Next;
    }
    return (size);
}