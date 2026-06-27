#if !defined(FECKLESS_C_LINKED_LIST)
#define FECKLESS_C_LINKED_LIST
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct Node
{
    struct Node *next;
    struct Node *prev;
    size_t item_size;
    void *data;
} Node;

typedef struct LL
{
    Node *head;
    Node *tail;
    size_t length;
} LL;

LL ll_init();
void ll_delete(LL *linked_list);
void ll_clone(LL *dest, LL *orig);

void ll_add_first_item(LL *linked_list, size_t item_size, void *item);
void ll_push(LL *linked_list, size_t item_size, void *item);
void ll_shift(LL *linked_list, size_t item_size, void *item);

void ll_for_each(LL *linked_list, void func(Node *item, size_t index));

Node *ll_get_at(LL *linked_list, size_t at);
bool ll_remove_at(LL *linked_list, size_t at);


#endif // FECKLESS_C_LINKED_LIST