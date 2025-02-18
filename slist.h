#ifndef BLIST_H
#define BLIST_H

#include <stddef.h>  // size_t

// INVALID -- код ошибки для невалидных ситуаций.
static const size_t INVALID = ~((size_t)0);

// slist_create -- Создать новый пустой односвязный список. Размер элемента -- itemSize байт.
void * slist_create(size_t itemSize);

// slist_destroy -- Удалить существующий односвязный список. Если указана функция destroy, то вызвать её для каждого удаляемого элемента.
void slist_destroy(void * slist, void(*destroy)( void * ));

// slist_init -- Инициализировать односвязный список новыми параметрами. Если slist содержит элементы, то сначала удалить все элементы, потом инициализировать односвязный список с учетом новых параметров. Размер элемента -- itemSize байт. Если указана функция destroy, то вызвать её для каждого удаляемого элемента.
void * slist_init(void * slist, size_t itemSize, void(*destroy)(void*));

// slist_clear -- Удалить все элементы из односвязного списка. Если указана функция destroy, то вызвать её для каждого удаляемого элемента.
void slist_clear(void * slist, void(*destroy)( void * ));

// slist_count -- Количество элементов в списке. В случае, если slist равен NULL, возвращает INVALID константу.
size_t slist_count(const void * slist);

// slist_item -- Получить элемент по индексу в списке.
void * slist_item(void * slist, size_t i);

// slist_prepend -- Добавить элемент в голову односвязного списка. В случае успеха, функция возвращает указатель на добавленный элемент, иначе -- NULL.
void * slist_prepend(void * slist);

// slist_remove -- Удалить элемент из головы односвязного списка. Если указана функция destroy, то вызвать её для удаляемого элемента.
void slist_remove(void * slist, void(*destroy)( void * ));

// slist_first -- Идентификатор для первого элемента из односвязного списка. Идентификатор может стать невалидным при модификации списка.
size_t slist_first(const void * slist);

// slist_next -- По идентификатору текущего элемента получить идентификатор следующего элемента списка.
size_t slist_next(const void * slist, size_t item_id);

// slist_stop -- Идентификатор, получаемый при попытке обратиться к элементу за пределами списка.
size_t slist_stop(const void * slist);

// slist_current -- Получить указатель на элемент списка по его идентификатору.
void * slist_current(const void * slist, size_t item_id);

// slist_insert -- Вставка нового элемента списка после указанного по идентификатору. Когда список пустой, для успешной вставки элемента в качестве item_id должен указываться идентификатор, возвращаемый функцией slist_stop. В остальных случаях, item_id должен однозначно соответствовать элементу списка. В случае успеха, функция возвращает указатель на вставленный элемент, иначе -- NULL.
void * slist_insert(void * slist, size_t item_id);

// slist_erase -- Удаление элемента по его идентификатору. Если указана функция destroy, то вызвать её для удаляемого элемента. После удаления элемента из списка, идентификаторы любых элементов из этого массива могут стать невалидным.
void slist_erase(void * slist, size_t item_id, void(*destroy)( void * ));

#endif //BLIST_H