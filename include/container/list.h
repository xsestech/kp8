//
// Created by Alex on 03.05.2024.
//

#ifndef LIST_H
#define LIST_H

#define LIST_INIT_CAPACITY 20

#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

typedef struct list_t list_t;
typedef struct list_element_t list_element_t;
typedef list_t* list_handle_t;
typedef struct  {
  list_handle_t list;
  int list_element_idx;
} list_iter_t;


list_handle_t list_init();
void list_destroy(list_handle_t list);
list_iter_t list_begin(list_handle_t list);
list_iter_t list_end(list_handle_t list);
double list_iter_val(list_iter_t iter);
list_iter_t list_iter_next(list_iter_t iter);
list_iter_t list_iter_null(list_handle_t list);
bool list_iter_equal(list_iter_t iter1, list_iter_t iter2);
bool list_insert_before(list_iter_t iter, double val);
double list_remove(list_iter_t iter);
void list_push_back(list_handle_t list, double val);
void list_push_front(list_handle_t list, double val);
void list_reverse(list_handle_t list);
bool list_is_empty(list_handle_t list);


#endif //LIST_H
