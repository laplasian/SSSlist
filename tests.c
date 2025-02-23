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

int multitest() {
    //Создаем односвязный список с элементами типа Value;
    void* slist = slist_create(sizeof(Value));

    assert(0 == slist_count(slist));
    assert(slist_stop(slist) == slist_first(slist));

    ///
    assert(stop(null) == 0);
    assert(first(null) == stop(null));
    assert(current(null, stop(null)) == null);
    assert(next(null, stop(null)) == stop(null));
    for(size_t i = first(null); i != stop(null); i = next(null, i)) { }
    assert(insert(null, stop(null)) == null);

    ///

    //Создаем объект для односвязного списка
    Value value = { {1, 2, 3, 4, 5, 6, 7, 8}, 0.f };

    //Добавляем новый элемент в односвязный список
    Value* insertedValue = (Value*)slist_prepend(slist);

    //Инициализируем добавленный элемент
    *insertedValue = value;

    Value* _item = (Value*)slist_item(slist, 0);

    assert(current(slist, stop(slist)) == null);
    void* _item2 = insert(slist, stop(slist));
    assert(_item2 != null);


    for (size_t i = 0; 8 > i; ++i) {
        assert(_item->array[i] == value.array[i]);
    }

    assert(fabsf(_item->d_variable - value.d_variable) < 1e-10f);
    assert(NULL == slist_item(slist, 1));


    //assert(slist_next(slist, slist_first(slist)) == slist_stop(slist));

    slist_destroy(slist, NULL);

    return 1;
};


void run_tests() {
    multitest();
};