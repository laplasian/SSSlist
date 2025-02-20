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

int test_slist_create() {
    //Создаем односвязный список с элементами типа Value;
    void* slist = slist_create(sizeof(Value));

    assert(0 == slist_count(slist));
    assert(slist_stop(slist) == slist_first(slist));

    //Создаем объект для односвязного списка
    Value value = { {1, 2, 3, 4, 5, 6, 7, 8}, 0.f };

    //Добавляем новый элемент в односвязный список
    Value* insertedValue = (Value*)slist_prepend(slist);

    //Инициализируем добавленный элемент
    *insertedValue = value;

    Value* item = (Value*)slist_item(slist, 0);

    for (size_t i = 0; 8 > i; ++i) {
        assert(item->array[i] == value.array[i]);
    }

    assert(fabsf(item->d_variable - value.d_variable) < 1e-10f);
    assert(NULL == slist_item(slist, 1));

    assert(slist_next(slist, slist_first(slist)) == slist_stop(slist));

    slist_destroy(slist, NULL);


    return 1;
}
int test_slist_destroy() {
    return 1;
}
int test_slist_init() {
    return 1;
}
int test_slist_clear() {
    return 1;
};
int test_slist_count() {
    return 1;
};
int test_slist_item() {
    return 1;
};
int test_slist_prepend() {
    return 1;
};
int test_slist_remove() {
    return 1;
};
int test_slist_first() {
    return 1;
};
int test_slist_next() {
    return 1;
};
int test_slist_stop() {
    return 1;
};
int test_slist_current() {
    return 1;
};
int test_slist_insert() {
    return 1;
};
int test_slist_erase() {
    return 1;
};
int test_users_mood() {
    return 1;
};

typedef int (Test)();

Test* all_tests[] = {
    &test_slist_create,
    &test_slist_clear,
    &test_slist_count,
    &test_slist_current,
    &test_slist_destroy,
    &test_slist_erase,
    &test_slist_first,
    &test_slist_insert,
    &test_slist_init,
    &test_slist_item,
    &test_slist_next,
    &test_slist_prepend,
    &test_slist_remove,
    &test_slist_stop,
    &test_users_mood,
};

void run_tests() {
    int count_success = 0;
    for (int i = 0; i < sizeof(all_tests)/sizeof(NULL); i++) {
        count_success += (*all_tests[i])();
    }
    printf("passed test: %llu\n", count_success / (sizeof(all_tests)/sizeof(NULL)));
};