#include "slist.h"

#include <stdlib.h>

typedef struct Node{
    char * data;
    void * next;
} Node;

typedef struct {
    size_t size;
    Node * head;
} Slist;

void * slist_create(size_t itemSize) {
    Slist * slist = malloc(sizeof(Slist));
    slist->size = itemSize;
    slist->head->data = NULL;
    slist->head->next = NULL;
    return slist;
}

void _clear(Node * node, void(*destroy)( void * )) {
    if (node == NULL) return;
    if (destroy!=NULL) destroy(node->data);
    _clear(node->next, destroy);
}

void slist_destroy(void * slist, void(*destroy)( void * )) {
    if (slist == NULL) return;
    Slist * list = (Slist *)slist;
    _clear(list->head, destroy);
    free(slist);
}

void slist_clear(void * slist, void(*destroy)( void * )) {
    Slist * list = (Slist *)slist;
    _clear(list->head,destroy);
    list->head = NULL;
}

void * slist_init(void * slist, size_t itemSize, void(*destroy)(void*)) {
    Slist * list = (Slist *)slist;
    slist_clear(slist, destroy);
    list->size = itemSize;
    return list;
}

size_t slist_count(const void * slist) {
    Slist * list = (Slist *)slist;
    if (list == NULL) return INVALID;
    size_t count = 0;
    Node * node = list->head;
    while (node != NULL) {
        count++;
        node = node->next;
    }
    return count;
}

void * slist_item(void * slist, size_t i) {
    Slist * list = (Slist *)slist;
    if (list == NULL) return NULL;
    Node * node = list->head;
    while (i > 0 && node != NULL) { // вернёт NULL, если i > slist_count(slist)
        node = node->next;
        i--;
    }
    return node;
}

void * slist_prepend(void * slist) {
    Slist * list = (Slist *)slist;
    Node * node = malloc(sizeof(Node));
    node->data = malloc(list->size);
    node->next = list->head;
    list->head = node;
    return node->data;
}

void slist_remove(void * slist, void(*destroy)( void * )) {
    Slist * list = (Slist *)slist;
    if (list == NULL) return;
    Node * node = list->head;
    if (node == NULL) return;
    list->head = node->next;
    if (destroy != NULL) destroy(node->data);
    free(node);
}

size_t slist_first(const void * slist) {
    Slist * list = (Slist *)slist;
    if (list == NULL) return INVALID;
    return (size_t)list->head; // приведение указателя к целому числу
}

size_t slist_next(const void * slist, size_t item_id) {
    Node * node = (Node *)item_id; // приведение целого числа к указателю
    if (node == NULL) return INVALID;
    return (size_t)node->next;
}

size_t slist_stop(const void * slist) {
    if (slist == NULL) return INVALID;
    Slist * list = (Slist *)slist;
    if (list->head == NULL) return INVALID;
    Node * node = list->head;
    while (node->next != NULL) {
        node = node->next;
    }
    return (size_t)node;
}

void * slist_current(const void * slist, size_t item_id) {
    return (Node *)item_id;
}

void * slist_insert(void * slist, size_t item_id) {
    return NULL;
}

void slist_erase(void * slist, size_t item_id, void(*destroy)( void * )) {

}