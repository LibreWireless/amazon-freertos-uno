/**
    Handle multiple socket connections with select and fd_set on Linux
*/

#include "linked_list.h"
#include "lib.h"
#include "stdlib.h"
#include "stdio.h"
#include "string.h"

void lock_list(linked_list_info *list_name)
{
    if(list_name->lock_fn != NULL)
    {
        list_name->lock_fn(list_name);
    }
}

void unlock_list(linked_list_info *list_name)
{
    if(list_name->unlock_fn != NULL)
    {
        list_name->unlock_fn(list_name);
    }
}

void list_node_constructor(linked_list_info *list_name, void* node, void* element)
{
    if(list_name->constructor != NULL)
    {
        list_name->constructor(node, element);
    }
}

void list_node_destructor(linked_list_info *list_name, void* node)
{
    if(list_name->destructor != NULL)
    {
        list_name->destructor(node);
    }
}

void list_node_copy(linked_list_info *list_name, void *dst, void *src)
{
    if(list_name->copy_fn != NULL)
    {
        list_name->copy_fn(dst, src);
    }
}

//#define USE_INTERNAL_RAM_FOR_LINKED_LIST_NODE

#ifdef USE_INTERNAL_RAM_FOR_LINKED_LIST_NODE
#include "os_port.h"
#include "os_port_freertos.h"
#endif

void* linked_list_node_alloc(int len)
{
    char *ptr;
#ifdef USE_INTERNAL_RAM_FOR_LINKED_LIST_NODE
    ptr=osAllocMem(len);
#else
    ptr=malloc(len);
#endif
    if(ptr==NULL)
    {
        fatal("linked list node alloc fail...");
    }
    return ptr;
}

void linked_list_node_free(void*ptr)
{
#ifdef USE_INTERNAL_RAM_FOR_LINKED_LIST_NODE
    osFreeMem(ptr);
#else
    free(ptr);
#endif
}


void* linked_list_create_node(linked_list_info *list_name, void *info)
{
    void *node=(void*)linked_list_node_alloc(list_name->elem_size);
    list_node_constructor(list_name, node, info);
    linked_list *ptr=(linked_list*)node;
    ptr->next = NULL;
    return node;
}


void add_to_list(linked_list_info *list_name, void *info)
{
    void *node;
    linked_list *ptr;
    node=linked_list_create_node(list_name, info);
    //list_name->print_elem_fn(ptr);
    lock_list(list_name);
    if(list_name->list == NULL)
    {
        printf("add: list empty\n");
        list_name->list=node;
    }
    else
    {
        ptr=list_name->list;
        while(ptr->next!=NULL)
        {
            ptr=ptr->next;
        }
        ptr->next=node;
    }
    unlock_list(list_name);
}


void remove_from_list(linked_list_info *list_name, void *item, void*copy)
{
    if(list_name->list == NULL)
    {
        fatal("remove fail");
    }
    else
    {
        linked_list *ptr, *prev;
        lock_list(list_name);
        ptr=list_name->list;
        while(ptr!=NULL)
        {
            if(1==list_name->compare_elem_fn(ptr, item))
            {
                if(ptr==list_name->list)
                {
                    list_name->list = ptr->next;
                }
                else
                {
                    prev->next=ptr->next;
                }
                unlock_list(list_name);
                if(copy!=NULL)
                {
                    /*give a copy */
                    list_node_copy(list_name, copy,ptr);
                }
                //list_name->print_elem_fn(ptr);
                list_node_destructor(list_name, ptr);
                linked_list_node_free(ptr);
                return;
            }
            else
            {
                prev=ptr;
                ptr=ptr->next;
            }
        }
        unlock_list(list_name);
        printf("remove fail. item not found..");
        print_list(list_name);
        list_name->print_elem_fn(item);
        fatal("remove fail. item not found..");
    }
}



void print_list(linked_list_info *list_name)
{
    printf("\n---print list start------\n");
    lock_list(list_name);
    if(list_name->list == NULL)
    {
        printf("list empty..\n");
    }
    else
    {
        linked_list *ptr;
        ptr=list_name->list;
        while(ptr!=NULL)
        {
            list_name->print_elem_fn(ptr);
            ptr=ptr->next;
        }
    }
    unlock_list(list_name);
    printf("---print list end------\n\n");
}

void* get_node(linked_list_info *list_name, void *search_item, char* caller)
{
    if(list_name->list == NULL)
    {
        fatal("list empty..\n");
    }
    else
    {
        linked_list *ptr;
        lock_list(list_name);
        ptr=list_name->list;
        while(ptr!=NULL)
        {
            if(1==list_name->compare_elem_fn(ptr, search_item))
            {
                unlock_list(list_name);
                return ptr;
            }
            ptr=ptr->next;
        }
    }
    unlock_list(list_name);
    printf("\nget node failed. caller=%s\n",caller);
    print_list(list_name);
    list_name->print_elem_fn(search_item);
    fatal("get node failed..");
    return NULL;
}

void do_for_each_node(linked_list_info *list_name,
        DO_FOR_EACH_NODE_FN fn, void* params)
{
    if(fn == NULL) fatal("do_for_each_node: cb = null");
    lock_list(list_name);
    if(list_name->list == NULL)
    {
        printf("\ndo_for_each_node: list empty..\n");
    }
    else
    {
        linked_list *temp,*ptr;
        ptr=list_name->list;
        while(ptr!=NULL)
        {
            printf("\ncalling 0x%p cb on entry 0x%p",fn,ptr);
            temp=ptr->next;
            fn(ptr,params);
            ptr=temp;
        }
    }
    unlock_list(list_name);
}



void linked_list_init(linked_list_info *list_name, int node_size, void* pvt,
                      PRINT_ELEM_FUN print_element,
                      COMPARE_ELEM_FUN compare_nodes,
                      CONSTRUCTOR_FUN node_constructor,
                      DESTRUCTOR_FUN node_destructor,
                      ELEM_COPY_FUN node_copy,
                      LOCK_INIT_FUN lock_init,
                      LOCK_FUN list_lock,
                      UNLOCK_FUN list_unlock
                     )
{
    memset(list_name, 0, sizeof(linked_list_info));
    list_name->pvt = pvt;
    list_name->elem_size = node_size;

    list_name->print_elem_fn = print_element;
    list_name->compare_elem_fn=compare_nodes;
    list_name->constructor=node_constructor;
    list_name->destructor=node_destructor;
    list_name->copy_fn=node_copy;

    if(lock_init != NULL)
    {
        list_name->lock_init = lock_init;
        lock_init(list_name);
    }
    list_name->lock_fn=list_lock;
    list_name->unlock_fn=list_unlock;
}


#if 0

typedef struct test_list_struct_s {
    linked_list *list;
    int value;
} test_list_struct;



static void print_element(void* item)
{
    test_list_struct *ptr = (test_list_struct *)item;
    printf("element: %d\n",ptr->value);
}


static int compare_nodes(void* cur_item, void* item)
{
    if((((test_list_struct*)cur_item)->value)==(((test_list_struct*)item)->value))
        return 1;
    else
        return 0;
}

linked_list_info test_list_head;

void linked_list_test()
{
    printf("entry\n");
    memset(&test_list_head, 0, sizeof(test_list_head));
    test_list_head.elem_size = sizeof(test_list_head);
    test_list_head.print_elem_fn = print_element;
    test_list_head.compare_elem_fn=compare_nodes;

    printf("calling print_list\n");
    print_list(&test_list_head);


    test_list_struct info= {0};
    info.value = 5;
    add_to_list(&test_list_head, &info);

    info.value = 6;
    add_to_list(&test_list_head, &info);

    info.value = 7;
    add_to_list(&test_list_head, &info);

    info.value = 8;
    add_to_list(&test_list_head, &info);

    info.value = 6;
    remove_from_list(&test_list_head, &info, NULL);

    info.value = 5;
    remove_from_list(&test_list_head, &info, NULL);

    print_list(&test_list_head);

    info.value = 8;
    remove_from_list(&test_list_head, &info, NULL);

    print_list(&test_list_head);

    info.value = 7;
    remove_from_list(&test_list_head, &info, NULL);

    print_list(&test_list_head);

    info.value = 6;
    add_to_list(&test_list_head, &info);

    print_list(&test_list_head);

    info.value = 5;
    add_to_list(&test_list_head, &info);

    print_list(&test_list_head);

}

#endif
