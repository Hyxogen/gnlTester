//
// Created by Daan Meijer on 11/1/21.
//

#include "LinkedList.h"
#include <stdlib.h>
#include "../include/tester.h"
#include "Logger.h"

LinkedList *CreateElement(void *content) {
	LinkedList *ret;

	ret = malloc(sizeof(LinkedList));
	if (!ret)
		return (NULL);
	ret->m_Content = content;
	ret->m_Next = NULL;
	return (ret);
}

LinkedList *GetLastElement(LinkedList *linkedList) {
	LinkedList *ret;

	ret = NULL;
	while (linkedList->m_Next)
		linkedList = linkedList->m_Next;
	return (linkedList);
}

LinkedList *FindFirst(LinkedList *list, t_bool (*equal)(const void *, const void *), const void *sample) {
	while (list) {
		if (equal(list->m_Content, sample))
			return (list);
		list = list->m_Next;
	}
	return (NULL);
}

void AddBack(LinkedList **list, LinkedList *element) {
	if (!*list) {
		*list = element;
		return;
	}

	LinkedList *temp;
	temp = (*list);
	while (temp->m_Next)
		temp = temp->m_Next;
	temp->m_Next = element;
}

void RemoveElements(LinkedList **list, t_bool (*equal)(const void *, const void *), const void *sample) {
	LinkedList *previous;
	LinkedList *current;

	previous = NULL;
	current = *list;
	while (current) {
		if (!equal(current->m_Content, sample)) {
			previous = current;
			current = current->m_Next;
			continue;
		}
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

void ClearList(LinkedList **list) {
	LinkedList *tmp;

	while (*list) {
		tmp = (*list)->m_Next;
		free(*list);
		*list = tmp;
	}
}

void ClearListWithElements(LinkedList **list, void (*clear)(void *)) {
	LinkedList *tmp;

	while (*list) {
		tmp = (*list)->m_Next;
		clear((*list)->m_Content);
		free(*list);
		*list = tmp;
	}
}

void ForEachElement(LinkedList *list, void (*func)(const void *)) {
	while (list) {
		func(list->m_Content);
		list = list->m_Next;
	}
}