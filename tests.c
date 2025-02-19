#include "tests.h"
#include <stdio.h>

int test_slist_create() {
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
    printf("passed test: %llu", count_success / (sizeof(all_tests)/sizeof(NULL)));
};