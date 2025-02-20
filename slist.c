#include "slist.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct Node{
    char * data;
    struct Node * next;
} Node;

typedef struct {
    size_t size;
    size_t item_size;
    Node * head;
} Slist;

void * slist_create(size_t itemSize) {
    Slist * slist = malloc(sizeof(Slist));
    if (NULL == slist) return NULL;
    slist->item_size = itemSize;
    slist->size = 0;
    slist->head=NULL;
    return slist;
}

Node * create_node(const size_t item_size) {
    Node * new = malloc(sizeof(Node));
    if (new == NULL) return NULL;
    new->data = malloc(item_size);
    if (new->data == NULL) {
        free(new);
        return NULL;
    }
    return new;
}

Node * delete_node(Node * node, void(*destroy)( void * )) {
    if (node == NULL) return NULL;
    Node * next = node->next;
    free(node->data);
    free(node);
    return next;
}

void slist_destroy(void * slist, void(*destroy)( void * )) {
    if (slist == NULL) return;
    slist_clear(((Slist *)slist)->head, destroy);
    free(slist);
}

void slist_clear(void * slist, void(*destroy)( void * )) {
    if (slist == NULL) return;
    Node* current = ((Slist *)slist)->head;
    while (current != NULL) {
        current = delete_node(current, destroy);
    }
    ((Slist *)slist)->head = NULL;
    ((Slist *)slist)->size = 0;
}

void * slist_init(void * slist, size_t itemSize, void(*destroy)(void*)) {
    slist_clear((Slist *)slist, destroy);
    ((Slist *)slist)->item_size = itemSize;
    return slist;
}

size_t slist_count(const void * slist) {
    if (slist == NULL) return INVALID;
    return ((Slist *)slist)->size;
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
    if (slist == NULL) return NULL;
    Node * node = malloc(sizeof(Node));
    if (node == NULL) return NULL;
    node->data = malloc(((Slist *)slist)->item_size);
    if (node->data == NULL) {
        free(node);
        return NULL;
    }
    node->next = ((Slist *)slist)->head;
    ((Slist *)slist)->head = node;
    ((Slist *)slist)->size += 1;
    return node->data;
}

void slist_remove(void * slist, void(*destroy)( void * )) {
    if (slist == NULL) return;
    Node * node = delete_node(((Slist *)slist)->head, destroy);
    ((Slist *)slist)->head = node;
    ((Slist *)slist)->size -= 1;
}

size_t slist_first(const void * slist) {
    if (slist == NULL || ((Slist *)slist)->head == NULL) return slist_stop(slist);
    return (size_t)((Slist *)slist)->head; // приведение указателя к целому числу
}

size_t slist_next(const void * slist, size_t item_id) {
    Node * node = (Node *)item_id; // приведение целого числа к указателю
    if (node == NULL || node->next == NULL) return slist_stop(slist);
    return (size_t)node->next;
}

size_t slist_stop(const void * slist) {
    return (size_t)NULL;
}

void * slist_current(const void * slist, size_t item_id) {
    if (slist == NULL) return NULL;
    return ((Node *)item_id)->data;
}

void * slist_insert(void * slist, size_t item_id) {
    if (slist == NULL) return NULL;
    Node* current = (Node *)item_id;
    if (item_id == slist_stop(slist)){
        ((Slist *)slist)->head = create_node((((Slist *)slist)->item_size));
        ((Slist *)slist)->size += 1;
    }
    Node* new = create_node((((Slist *)slist)->item_size));
    if (new == NULL) return NULL;
    new->next = current->next;
    current->next = new;
    return new->data;
}

void slist_erase(void * slist, size_t item_id, void(*destroy)( void * )) {
    if (slist == NULL) return;
    Node* current = ((Slist *)slist)->head;
    if (current == NULL) return;
    while ((size_t)(current->next) != item_id) {
        if (NULL == current) return;
        current = current->next;
    }
    Node* _del = current->next;
    current = current->next->next;
    delete_node(_del, destroy);
}