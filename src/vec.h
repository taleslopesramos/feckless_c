#if !defined(FECKLESS_C_VEC)
#define FECKLESS_C_VEC

#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define VEC_AT_AS(vec, type, index) \
    (*(type *)vec_at((vec), (index)))

typedef struct Vec
{
    void *data;
    size_t item_size;
    size_t total_size;
    size_t length;
} Vec;

Vec vec_init(size_t initial_size, size_t item_size);
void vec_delete(Vec *vec);
bool vec_resize(Vec *vec, size_t new_size);
void vec_clone(Vec *dest, Vec *orig);

bool vec_set(Vec *vec, size_t index, void* item);
bool vec_add(Vec *vec, void* item);
bool vec_insert(Vec *vec, size_t index, void* item);
void* vec_at(Vec *vec, size_t index);

#endif // FECKLESS_C_VEC