#include "tests.h"

#include <assert.h>
#include <math.h>

#include "slist.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int array[8];
    float d_variable;
} Value;

#define null NULL
#define create slist_create
#define destroy slist_destroy
#define clear slist_clear
#define count slist_count
#define item slist_item
#define prepend slist_prepend
#define remove slist_remove
#define first slist_first
#define next slist_next
#define stop slist_stop
#define current slist_current
#define insert slist_insert
#define erase slist_erase

void test_nullContainer_stop_OK() {
    assert(slist_stop(NULL) == (size_t)NULL);
}

void test_nullContainer_firstEqualsStop_OK() {
    assert(slist_first(NULL) == slist_stop(NULL));
}

void test_nullContainer_current_FAIL() {
    assert(slist_current(NULL, slist_stop(NULL)) == NULL);
}

void test_nullContainer_nextStopEqualsStop_OK() {
    assert(slist_next(NULL, slist_stop(NULL)) == slist_stop(NULL));
}

void test_nullContainer_forwardLoop_OK() {
    for (size_t i = slist_first(NULL); i != slist_stop(NULL); i = slist_next(NULL, i)) {}
}

void test_nullContainer_insert_FAIL() {
    assert(slist_insert(NULL, slist_stop(NULL)) == NULL);
}

void test_nullContainer_erase_OK() {
    slist_erase(NULL, slist_stop(NULL), NULL);
}

void test_nullContainer_eraseWithoutDtor_OK() {
    slist_erase(NULL, slist_stop(NULL), NULL);
}

void test_emptyContainer_prepend_count_item_OK() {
    void *list = slist_create(sizeof(int));
    assert(slist_prepend(list) != NULL);
    assert(slist_count(list) == 1);
    slist_destroy(list, NULL);
}

void test_emptyContainer_current_FAIL() {
    void *list = slist_create(sizeof(int));
    assert(slist_current(list, slist_stop(list)) == NULL);
    slist_destroy(list, NULL);
}

void test_emptyContainer_insert_count_item_OK() {
    void *list = slist_create(sizeof(int));
    assert(slist_insert(list, slist_stop(list)) != NULL);
    assert(slist_count(list) == 1);
    slist_destroy(list, NULL);
}

void test_emptyContainer_erase_OK() {
    void *list = slist_create(sizeof(int));
    slist_erase(list, slist_stop(list), NULL);
    slist_destroy(list, NULL);
}

void test_emptyContainer_eraseWithoutDtor_OK() {
    void *list = slist_create(sizeof(int));
    slist_erase(list, slist_stop(list), NULL);
    slist_destroy(list, NULL);
}


void test_singleElementContainer_destroy_OK() {
    void *list = slist_create(sizeof(int));
    slist_prepend(list);
    slist_destroy(list, NULL);
}

void test_singleElementContainer_item_OK() {
    void *list = slist_create(sizeof(int));
    int *elem = (int *)slist_prepend(list);
    assert(elem != NULL);
    assert(slist_item(list, 0) == elem);
    slist_destroy(list, NULL);
}

void test_singleElementContainer_itemSubZero_FAIL() {
    void *list = slist_create(sizeof(int));
    slist_prepend(list);
    assert(slist_item(list, -1) == NULL);
    slist_destroy(list, NULL);
}

void test_singleElementContainer_itemOutsideRange_FAIL() {
    void *list = slist_create(sizeof(int));
    slist_prepend(list);
    assert(slist_item(list, 1) == NULL);
    slist_destroy(list, NULL);
}

void test_twoElementContainer_create_destroy() {
    void *list = slist_create(sizeof(int));
    slist_prepend(list);
    slist_prepend(list);
    slist_destroy(list, NULL);
}

void run_tests() {
    test_nullContainer_stop_OK();
    test_nullContainer_firstEqualsStop_OK();
    test_nullContainer_current_FAIL();
    test_nullContainer_nextStopEqualsStop_OK();
    test_nullContainer_forwardLoop_OK();
    test_nullContainer_insert_FAIL();
    test_nullContainer_erase_OK();
    test_nullContainer_eraseWithoutDtor_OK();
    test_emptyContainer_prepend_count_item_OK();
    test_emptyContainer_current_FAIL();
    test_emptyContainer_insert_count_item_OK();
    test_emptyContainer_erase_OK();
    test_emptyContainer_eraseWithoutDtor_OK();
    test_singleElementContainer_destroy_OK();
    test_singleElementContainer_item_OK();
    test_singleElementContainer_itemSubZero_FAIL();
    test_singleElementContainer_itemOutsideRange_FAIL();
    test_twoElementContainer_create_destroy();
    printf("All tests passed!\n");
}