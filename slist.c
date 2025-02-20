#include "slist.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    char * data;
    struct Node * next;
} Node;

typedef struct {
    size_t size;
    Node * head;
} Slist;

void * slist_create(size_t itemSize) {
    Slist * slist = malloc(sizeof(Slist));
    slist->size = itemSize;
    slist->head=NULL;
    return slist;
}

void _clear(Node * node, void(*destroy)( void * )) {
    if (node == NULL) return;
    if (destroy!=NULL) destroy(node->data);
    _clear(node->next, destroy);
    free(node);
}

void slist_destroy(void * slist, void(*destroy)( void * )) {
    if (slist == NULL) return;
    Slist * list = (Slist *)slist;
    _clear(list->head, destroy);
    free(slist);
}

void slist_clear(void * slist, void(*destroy)( void * )) {
    _clear(((Slist *)slist)->head,destroy);
}

void * slist_init(void * slist, size_t itemSize, void(*destroy)(void*)) {
    slist_clear((Slist *)slist, destroy);
    ((Slist *)slist)->size = itemSize;
    return slist;
}

size_t slist_count(const void * slist) {
    if (slist == NULL) return INVALID;
    size_t count = 0;
    Node * node = ((Slist *)slist)->head;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

void * slist_item(void * slist, size_t i) {
    if (slist == NULL) return NULL;
    Node * node = ((Slist *)slist)->head;
    while (i > 0 && node != NULL) { // вернёт NULL, если i > slist_count(slist)
        node = node->next;
        i--;
    }
    if (node == NULL) return NULL;
    return node->data;
}

void * slist_prepend(void * slist) {
    Node * node = malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->data = malloc(((Slist *)slist)->size);
    if (node->data == NULL) return NULL;
    node->next = ((Slist *)slist)->head;
    ((Slist *)slist)->head = node;
    return node->data;
}

void slist_remove(void * slist, void(*destroy)( void * )) {
    if (slist == NULL) return;
    Node * node = ((Slist *)slist)->head;
    if (node == NULL) return;
    ((Slist *)slist)->head = node->next;
    if (destroy != NULL) destroy(node->data);
    free(node);
}

size_t slist_first(const void * slist) {
    if (slist == NULL || ((Slist *)slist)->head == NULL) return INVALID;
    return (size_t)((Slist *)slist)->head; // приведение указателя к целому числу
}

size_t slist_next(const void * slist, size_t item_id) {
    Node * node = (Node *)item_id; // приведение целого числа к указателю
    if (node == NULL || node->next == NULL) return INVALID;
    return (size_t)node->next;
}

size_t slist_stop(const void * slist) {
    if (slist == NULL) return INVALID;
    if (((Slist *)slist)->head == NULL) return INVALID;
    Node * node = ((Slist *)slist)->head;
    while (node->next != NULL) {
        node = node->next;
    }
    return (size_t)node;
}

void * slist_current(const void * slist, size_t item_id) {
    return (Node *)item_id;
}

void * slist_insert(void * slist, size_t item_id) {
    Node* current = (Node *)item_id;
    Node* new = malloc(sizeof(Node));
    new->next = current;
    current->next = new;

    return slist;
}

void slist_erase(void * slist, size_t item_id, void(*destroy)( void * )) {
    Node* current = ((Slist *)slist)->head;
    if (current == NULL) return;
    while ((size_t)(current->next) != item_id) {
        if (NULL == current) return;
        current = current->next;
    }
    Node* _del = current->next;
    current = current->next->next;
    if (destroy != NULL) destroy(_del->data);
    free(_del);
}