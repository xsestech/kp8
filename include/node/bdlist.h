//
// Created by Alex on 19.04.2024.
//

#ifndef BIDIRECTIONAL_LIST_H
#define BIDIRECTIONAL_LIST_H

#include <math.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct bdlist_node bdlist_node_t;
typedef struct bdlist_node* bdlist_handle_t;

/**
 * Init list
 * @return pointer to first node
 */
bdlist_handle_t bdlist_init();

/**
 * Destroys the list
 * @param bdlist root node of the list
 */

void bdlist_destroy(bdlist_handle_t bdlist);

/**
 * Pushes value to the back of the linked list
 * @param bdlist root node
 * @param value value to push
 */
void bdlist_push_back(bdlist_handle_t bdlist, double value);
/**
 * Pops value from back of the list
 * @param bdlist root node of the list
 * @return poped value(NAN if list is empty)
 */
double bdlist_pop_back(bdlist_handle_t bdlist);

/**
 * Pushes value to front of list
 * @param bdlist_ptr pointer to root node of the linked list
 * @param value value to push to front of list
 */
void bdlist_push_front(bdlist_handle_t* bdlist_ptr, double value);
/**
 * Pops value from front of the list
 * @param bdlist_ptr pointer to root node of the linked list
 * @return poped value(NAN if list is empty)
 */
double bdlist_pop_front(bdlist_handle_t* bdlist_ptr);
/**
 * Checks if list is empty
 * @param bdlist root node of the list
 * @return true if empty
 */
bool bdlist_is_empty(bdlist_handle_t bdlist);
/**
 * Iteratate though list from beggining
 * @example for(){ {
 * @param bdlist list
 * @return pointer to next node
 */
bdlist_handle_t bdlist_iter_begin(bdlist_handle_t bdlist);
bdlist_handle_t bdlist_iter_end(bdlist_handle_t bdlist);
double bdlist_get_value(bdlist_handle_t bdlist);


#endif //BIDIRECTIONAL_LIST_H
