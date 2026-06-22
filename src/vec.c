#include "./vec.h"
#include "vec.h"
#include <stdlib.h>

Vec init_vec(size_t initial_size, size_t item_size)
{
    void *data = (void *)malloc(initial_size * item_size);

    if (data == NULL)
    {
        return (Vec) {
            .data = NULL,
            .item_size = 0,
            .total_size = 0,
            .length = 0};
    }

    return (Vec){
        .data = data,
        .item_size = item_size,
        .total_size = initial_size,
        .length = 0};
}

void delete_vec(Vec *vec)
{
    free(vec->data);
}

bool vec_resize(Vec *vec, size_t new_size)
{
    if (new_size <= vec->total_size)
    {
        return false;
    }

    vec->data = realloc(vec->data, new_size * vec->item_size);

    vec->total_size = new_size;
    return true;
}

bool vec_if_full_double_size(Vec *vec)
{
    if(vec->length < vec->total_size)
        return true;
    
    if (vec->length >= vec->total_size)
    {
        bool was_resized = vec_resize(vec, vec->total_size * 2);
        if (!was_resized)
            return false;
        else 
            return true;
    }

    return false;
}

bool vec_set(Vec *vec, size_t index, void *item)
{
    if (vec == NULL || item == NULL)
    {
        return false;
    }

    if (index >= vec->total_size)
    {
        return false;
    }

    char *dest = (char *)vec_at(vec, index);
    memcpy(dest, item, vec->item_size);

    return true;
}

bool vec_add(Vec *vec, void *item)
{
    if (!vec_if_full_double_size(vec))
        return false;

    vec_set(vec, vec->length, item);
    vec->length += 1;
    return true;
}

bool vec_insert(Vec *vec, size_t index, void *item)
{
    if (!vec_if_full_double_size(vec))
        return false;

    if (index >= vec->total_size)
    {
        return false;
    }

    int count = vec->total_size - index - 1;
    memmove(vec_at(vec, index + 1), vec_at(vec, index), (count)*vec->item_size);

    vec_set(vec, index, item);
    vec->length += 1;

    return true;
}

void *vec_at(Vec *vec, size_t index)
{
    if (vec == NULL || vec->data == NULL)
    {
        return NULL;
    }

    if (index > vec->total_size)
    {
        return NULL;
    }

    return (char *)vec->data + (index * vec->item_size);
}
