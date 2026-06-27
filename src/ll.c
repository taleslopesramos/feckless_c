#include "ll.h"

LL ll_init()
{
    LL ll;
    ll.length = 0;
    ll.head = NULL;
    ll.tail = NULL;
    return ll;
}

void ll_delete(LL *linked_list)
{
    if (linked_list->head == NULL || linked_list->tail == NULL)
        return;

    Node *iter = linked_list->tail;

    while (iter->prev != NULL)
    {
        iter = iter->prev;
        free(iter->next->data);
        free(iter->next);
    }

    free(iter->data);
    free(iter);
    return;
}

void ll_clone(LL *dest, LL *orig)
{
    if (orig->length == 0 || orig->head == NULL)
    {
        return;
    }

    Node *iter = orig->head;
    size_t index_count = 0;
    while (iter != NULL && index_count != orig->length)
    {
        ll_push(dest, iter->item_size, iter->data);
        iter = iter->next;
        index_count += 1;
    }
}

void ll_add_first_item(LL *linked_list, size_t item_size, void *item)
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = malloc(item_size);
    new_node->item_size = item_size;
    memcpy(new_node->data, item, item_size);

    new_node->prev = NULL;
    new_node->next = NULL;

    linked_list->head = new_node;
    linked_list->tail = new_node;
    linked_list->length += 1;
}

void ll_push(LL *linked_list, size_t item_size, void *item)
{
    if (linked_list->head == NULL)
    {
        ll_add_first_item(linked_list, item_size, item);
        return;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = malloc(item_size);
    new_node->item_size = item_size;
    memcpy(new_node->data, item, item_size);

    linked_list->tail->next = new_node;
    new_node->prev = linked_list->tail;

    linked_list->tail = new_node;
    linked_list->tail->next = NULL;

    linked_list->length += 1;
}

void ll_shift(LL *linked_list, size_t item_size, void *item)
{
    if (linked_list->head == NULL)
    {
        ll_add_first_item(linked_list, item_size, item);
        return;
    }

    Node *new_node = (Node *)malloc(sizeof(Node));
    new_node->data = malloc(item_size);
    memcpy(new_node->data, item, item_size);

    new_node->prev = NULL;
    new_node->next = linked_list->head;
    linked_list->head = new_node;
    linked_list->length += 1;
}

void ll_for_each(LL *linked_list, void func(Node *item, size_t index))
{
    if (linked_list->length == 0 || linked_list->head == NULL)
    {
        return;
    }

    Node *iter = linked_list->head;
    size_t index_count = 0;
    while (iter != NULL && index_count != linked_list->length)
    {
        func(iter, index_count);
        iter = iter->next;
        index_count += 1;
    }
}

Node *ll_get_at(LL *linked_list, size_t at)
{
    if (at >= linked_list->length || linked_list->head == NULL)
    {
        return NULL;
    }

    Node *iter = linked_list->head;
    size_t index_count = 0;
    while (iter != NULL && index_count != at)
    {
        iter = iter->next;
        index_count += 1;
    }

    return iter;
}

bool ll_remove_at(LL *linked_list, size_t at)
{
    Node *elem = ll_get_at(linked_list, at);
    if (elem == NULL)
    {
        return false;
    }

    if(elem->prev == NULL && elem->next == NULL) 
    {
        linked_list->head = NULL;
        linked_list->tail = NULL;
    }
    else if (elem->prev == NULL)
    {
        linked_list->head = linked_list->head->next;
        linked_list->head->prev = NULL;
    }
    else if(elem->next == NULL) {
        linked_list->tail = linked_list->tail->prev;
        linked_list->tail->next = NULL;
    }   
    else
    {
        Node *prev = elem->prev;
        Node *next = elem->next;
        prev->next = next;
        next->prev = prev;
    }

    linked_list->length -= 1;

    free(elem->data);
    free(elem);
    return true;
}
