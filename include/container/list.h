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
typedef list_t *list_handle_t;
typedef struct {
  list_handle_t list;
  int list_element_idx;
} list_iter_t;

/**
 * Initializes list. Creates a dynamic array size of 2.
 * @return pointer to list
 */
list_handle_t list_init();

/**
 * Destroy list
 * @param list pointer to list
 */
void list_destroy(list_handle_t list);

/**
 * Get the iterator to iterate from the beginning
 * @param list pointer to list
 * @return iterator for the first element
 */
list_iter_t list_begin(list_handle_t list);

/**
 * Get the iterator to iterate from the end
 * @param list pointer to list
 * @return iterator for the last element
 */
list_iter_t list_end(list_handle_t list);

/**
 * Get value of the current element from the iterator
 * @param iter list itertor
 * @return element value
 */
double list_iter_val(list_iter_t iter);

/**
 * Get next iterator
 * @param iter list iterator
 * @return element value
 */
list_iter_t list_iter_next(list_iter_t iter);

/**
 * Get itertor of non-existent element
 * @param list pointer to list
 * @return null iterator
 */
list_iter_t list_iter_null(list_handle_t list);

/**
 * Checks equality of two iterators. Lists should be the same.
 * @param iter1 first itertor
 * @param iter2 second itertor
 * @return true if they are equal
 */
bool list_iter_equal(list_iter_t iter1, list_iter_t iter2);

/**
 * Inserts value before element that iterator points to
 * @param iter list iterator
 * @param val value
 */
void list_insert_before(list_iter_t iter, double val);

/**
 * Inserts value before element that iterator points to
 * @param iter list iterator
 * @param val value
 */
void list_insert_after(list_iter_t iter, double val);

/**
 * Removes the element that iterator points to
 * @param iter list itertor
 * @return value of deleted element
 */
double list_remove(list_iter_t iter);

/**
 * Pushes value to the back of the list
 * @param list pointer to list
 * @param val value to push
 */
void list_push_back(list_handle_t list, double val);

/**
 * Pushes value to the front of the list
 * @param list pointer to list
 * @param val value to push
 */
void list_push_front(list_handle_t list, double val);
/**
 * Reverses list
 * @param list pointer to list
 */
void list_reverse(list_handle_t list);

/**
 * Checks if list is empty
 * @param list pointer to list
 * @return true if list is empty
 */
bool list_is_empty(list_handle_t list);

#endif //LIST_H
