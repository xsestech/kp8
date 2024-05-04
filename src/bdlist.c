//
// Created by Alex on 19.04.2024.
//

#include "node/bdlist.h"

#include <assert.h>

struct bdlist_node {
  double data;
  bdlist_node_t *prev;
  bdlist_node_t *next;
};

/**
 * Puts node on heap
 * @param node struct with data, that we need to malloc
 * @return pointer to malloced node
 * @internal
 */
bdlist_node_t *bdlist_malloc_node(bdlist_node_t node) {
  bdlist_node_t *new_node = malloc(sizeof(bdlist_node_t));
  assert(new_node);
  new_node->data = node.data;
  new_node->next = node.next;
  new_node->prev = node.prev;
  return new_node;
}

/** I don't want to create another structure, so I will store pointer to last node in first
 * So, there will be some euristics in pushing and poping algorithims
 * @return pointer to first node
 */
bdlist_handle_t bdlist_init() {
  return bdlist_malloc_node((bdlist_node_t){NAN, NULL, NULL});
}

void bdlist_destroy(bdlist_handle_t bdlist) {
  if(bdlist == NULL) return;
  while(bdlist->next != NULL){
    bdlist_handle_t temp = bdlist->next;
    free(bdlist);
    bdlist = temp;
  }
  free(bdlist);
}
/**
 * To push back we need to add link in last node to new node
 * and add link to root node to it
 * @param bdlist root node
 * @param value value to push
 */
void bdlist_push_back(bdlist_handle_t bdlist, double value) {
  if (bdlist->data != bdlist->data) {
    bdlist->data = value;
    return;
  }
  if (bdlist->next == NULL) {
    bdlist_node_t *new_node = bdlist_malloc_node((bdlist_node_t){value, bdlist, NULL});
    bdlist->next = new_node;
    bdlist->prev = new_node;
    return;
  }
  bdlist_node_t *new_node = bdlist_malloc_node((bdlist_node_t){value, bdlist->prev, NULL});
  bdlist->prev->next = new_node;
  bdlist->prev = new_node;
}

/**
 * To delete last node we need to break the chain.
 * In previous node to last we delete link to last node.
 * In root node we replace link to previous to last node.
 * @param bdlist root node of the list
 * @return poped value(NAN if list is empty)
 */
double bdlist_pop_back(bdlist_handle_t bdlist) {
  if (bdlist->data != bdlist->data) {
    return NAN;
  }
  if (bdlist->next == NULL) {
    double temp_data = bdlist->data;
    bdlist->data = NAN;
    return temp_data;
  }
  bdlist_node_t *last_node = bdlist->prev;
  bdlist->prev = last_node->prev;
  last_node->prev->next = NULL; // Delete link to poped node
  double temp_data = last_node->data;
  free(last_node);
  return temp_data;
}
/**
 * To push front we need to add link in new node to last node,
 * add link in root node to it, and replace root node
 * @param bdlist_ptr pointer root node of the linked list
 * @param value value to push to front of list
 */
void bdlist_push_front(bdlist_handle_t *bdlist_ptr, double value) {
  bdlist_handle_t bdlist = *bdlist_ptr;
  if (bdlist->data != bdlist->data) {
    bdlist->data = value;
    return;
  }
  if (bdlist->next == NULL) {
    bdlist_node_t *new_node = bdlist_malloc_node((bdlist_node_t){value, bdlist, bdlist});
    bdlist->prev = new_node;
    *bdlist_ptr = new_node;
    return;
  }
  bdlist_node_t *new_node = bdlist_malloc_node((bdlist_node_t){value, NULL, bdlist});
  bdlist->prev = new_node;
  *bdlist_ptr = new_node;
}
/**
 * To pop front next node needs to becaome root node.
 * So, we create link in next node to prev node and
 * replace root node with it.
 * @param bdlist_ptr pointer root node of the linked list
 * @return poped value(NAN if list is empty)
 */
double bdlist_pop_front(bdlist_handle_t *bdlist_ptr) {
  bdlist_handle_t bdlist = *bdlist_ptr;
  if (bdlist->data != bdlist->data) {
    return NAN;
  }
  if (bdlist->next == NULL) {
    double temp_data = bdlist->data;
    bdlist->data = NAN;
    return temp_data;
  }
  bdlist_node_t *next_node = bdlist->next;
  next_node->prev = bdlist->prev;
  double temp_data = bdlist->data;
  free(bdlist);
  *bdlist_ptr = next_node;
  return temp_data;
}

bool bdlist_is_empty(bdlist_handle_t bdlist) {
  return bdlist->data != bdlist->data;
}
bdlist_handle_t bdlist_iter_begin(bdlist_handle_t bdlist) {
  return bdlist->next;
}
bdlist_handle_t bdlist_iter_end(bdlist_handle_t bdlist) {
  return bdlist->prev;
}

double bdlist_get_value(bdlist_handle_t bdlist) {
  return bdlist->data;
}
