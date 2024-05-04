//
// Created by Alex on 03.05.2024.
//
#include "container/list.h"

#include <math.h>

struct list_element_t {
  double value;
  int prev;
  int next;
};

struct list_t {
  int first;
  int last;
  size_t capacity;
  size_t size;
  int top_element_empty;
  list_element_t *container;
};

/**
 * Logariphmic list growth
 * @param old_capacity capacity, that needs to be increased
 * @return new capacity
 * @internal
 */
size_t list_new_capacity(size_t old_capacity) {
  if (!old_capacity) {
    return 2;
  }
  return old_capacity << 1;
}

/**
 * Increases list size to new capacity
 * @param list pointer to list
 * @param new_capacity new capacity
 * @internal
 */
void list_grow(list_handle_t list) {
  size_t old_capacity = list->capacity;
  size_t new_capacity = list_new_capacity(old_capacity);
  size_t new_data_size = new_capacity * sizeof(*(list->container));
  if (list->container) {
    list->container = realloc(list->container, new_data_size);
  } else {
    list->container = malloc(new_data_size);
  }
  assert(list->container);
  for (int i = old_capacity; i < new_capacity - 1; i++) {
    list->container[i].next = i + 1;
  }
  list->container[new_capacity - 1].next = -1;
  if (old_capacity != 0) {
    list->container[list->top_element_empty].next = (int) old_capacity;
  }
  list->capacity = new_capacity;
}

list_handle_t list_init() {
  list_handle_t list = malloc(sizeof(list_t));
  list->capacity = 0;
  list->size = 0;
  list->first = -1;
  list->last = -1;
  list->top_element_empty = 0;
  list->container = NULL;
  list_grow(list);
  return list;
}

void list_destroy(list_handle_t list) {
  free(list->container);
  free(list);
}

list_iter_t list_begin(list_handle_t list) {
  return (list_iter_t){list, list->first};
}

list_iter_t list_end(list_handle_t list) {
  return (list_iter_t){list, list->last};
}

double list_iter_val(list_iter_t iter) {
  return iter.list->container[iter.list_element_idx].value;
}

list_iter_t list_iter_next(list_iter_t iter) {
  return (list_iter_t){iter.list, iter.list->container[iter.list_element_idx].next};
}
list_iter_t list_iter_prev(list_iter_t iter) {
  return (list_iter_t){iter.list, iter.list->container[iter.list_element_idx].prev};
}

list_iter_t list_iter_null(list_handle_t list) {
  return (list_iter_t){list, -1};
}

bool list_iter_equal(list_iter_t iter1, list_iter_t iter2) {
  if (iter1.list != iter2.list) {
    return false;
  }
  if (iter1.list_element_idx != iter2.list_element_idx) {
    return false;
  }
  return true;
}
void list_insert_before(list_iter_t iter, double val) {
  list_handle_t list = iter.list;
  if (list->container[list->top_element_empty].next == -1) {
    list_grow(iter.list);
  }
  if (list_iter_equal(iter, list_iter_null(list)) && list->top_element_empty == 0) {
    list->top_element_empty = list->container[0].next;
    list->container[0] = (list_element_t){val, -1, -1};
    list->first = 0;
    list->last = 0;
    list->size++;
    return;
  }
  if (list->container[iter.list_element_idx].prev == -1) {
    list->first = list->top_element_empty;
  }
  int new_top_elem_empty = list->container[list->top_element_empty].next;
  list->container[list->top_element_empty] = (list_element_t){
    val, list->container[iter.list_element_idx].prev, iter.list_element_idx
  };
  list->container[iter.list_element_idx].prev = list->top_element_empty;
  list->top_element_empty = new_top_elem_empty;
  list->size++;
}

void list_insert_after(list_iter_t iter, double val) {
  list_handle_t list = iter.list;
  if (list->container[list->top_element_empty].next == -1) {
    list_grow(iter.list);
  }
  if (list_iter_equal(iter, list_iter_null(list)) && list->top_element_empty == 0) {
    list->top_element_empty = list->container[0].next;
    list->container[0] = (list_element_t){val, -1, -1};
    list->first = 0;
    list->last = 0;
    list->size++;
    return;
  }
  if (list->container[iter.list_element_idx].next == -1) {
    list->last = list->top_element_empty;
  }
  int new_top_elem_empty = list->container[list->top_element_empty].next;
  list->container[list->top_element_empty] = (list_element_t){
    val, iter.list_element_idx, list->container[iter.list_element_idx].next
  };
  list->container[iter.list_element_idx].next = list->top_element_empty;
  list->top_element_empty = new_top_elem_empty;
  list->size++;
}

double list_remove(list_iter_t iter) {
  list_handle_t list = iter.list;

  if (list_iter_equal(iter, list_iter_null(list))) {
    return NAN;
  }
  list_element_t elem = list->container[iter.list_element_idx];
  if (elem.next == -1) {
    list->last = elem.prev;
  }
  if (elem.prev != -1) {
    list->container[elem.prev].next = elem.next;
  }
  list->container[iter.list_element_idx].next = list->top_element_empty;
  list->top_element_empty = iter.list_element_idx;
  list->size--;
  return elem.value;
}
void list_push_back(list_handle_t list, double val) {
  list_insert_after(list_end(list), val);
}
void list_push_front(list_handle_t list, double val) {
  list_insert_before(list_end(list), val);
}

bool list_is_empty(list_handle_t list) {
  return list->size == 0;
}
void list_reverse(list_handle_t list) {
  int current_idx = list->first;
  while (current_idx != -1) {
    int tmp_idx = list->container[current_idx].next;
    list->container[current_idx].next = list->container[current_idx].prev;
    list->container[current_idx].prev = tmp_idx;
    current_idx = tmp_idx;
  }
  int tmp_first = list->first;
  list->first = list->last;
  list->last = tmp_first;
}
