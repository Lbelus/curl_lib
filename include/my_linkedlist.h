#ifndef __LINKEDLIST_
#define __LINKEDLIST_

#include <main_header.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef NODE_S
#define NODE_S
struct node 
{
    void* token;
    struct node* head;
    struct node* next;
};
typedef struct node node_t;
#endif

node_t* create_node(void* token);
void    insert_at_head(node_t** head, node_t* node_to_insert);
void    print_llist(node_t* head);
void    free_llist(node_t* head);

#ifdef __cplusplus
}
#endif

#endif
