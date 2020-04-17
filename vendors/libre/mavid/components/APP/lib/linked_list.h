


#ifndef __LINKED_LIST_H_

#define __LINKED_LIST_H_

#include "os_port.h"
#include "os_port_freertos.h"

typedef struct linked_list_s {
    struct linked_list_s *next;
} linked_list;

typedef int  (*COMPARE_ELEM_FUN)(void*, void*);
typedef void (*PRINT_ELEM_FUN)(void*);
typedef void (*CONSTRUCTOR_FUN)(void*, void*);
typedef void (*DESTRUCTOR_FUN)(void*);
typedef void (*ELEM_COPY_FUN)(void*, void*);
typedef void (*LOCK_INIT_FUN)(void*);
typedef void (*LOCK_FUN)(void*);
typedef void (*UNLOCK_FUN)(void*);

typedef struct linked_list_info_s {
    linked_list *list;
    int elem_size;
    COMPARE_ELEM_FUN compare_elem_fn;
    PRINT_ELEM_FUN print_elem_fn;
    CONSTRUCTOR_FUN constructor;
    DESTRUCTOR_FUN destructor;
    ELEM_COPY_FUN copy_fn;
    OsMutex lock;
    LOCK_INIT_FUN lock_init;
    LOCK_FUN lock_fn;
    UNLOCK_FUN unlock_fn;
    void* pvt;
} linked_list_info;

typedef void (*DO_FOR_EACH_NODE_FN)(void*, void*);

void linked_list_init(linked_list_info *, int, void*,
                      PRINT_ELEM_FUN,
                      COMPARE_ELEM_FUN,
                      CONSTRUCTOR_FUN,
                      DESTRUCTOR_FUN,
                      ELEM_COPY_FUN,
                      LOCK_INIT_FUN,
                      LOCK_FUN,
                      UNLOCK_FUN
                     );

void add_to_list(linked_list_info *list_name, void *info);

void remove_from_list(linked_list_info *list_name, void *item, void*copy);

void print_list(linked_list_info *list_name);

void* get_node(linked_list_info *list_name, void *search_item, char* caller);

void lock_list(linked_list_info *list_name);

void unlock_list(linked_list_info *list_name);

void* linked_list_create_node(linked_list_info *list_name, void *info);

void do_for_each_node(linked_list_info *list_name,
        DO_FOR_EACH_NODE_FN fn, void* params);
#endif /* __LINKED_LIST_H_ */
