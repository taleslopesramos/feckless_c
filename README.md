# Feckless C

A minimal library with some half-assed utilities for C.

Modules: a generic dynamic array (`Vec`) and a doubly linked list (`LL`).

## Vec

A type-erased growable array. You pick the element type at initialization via `item_size`; the vector stores a contiguous block of bytes and grows by doubling capacity when full.

| Function | Description |
|----------|-------------|
| `vec_init(initial_size, item_size)` | Allocate a vector with room for `initial_size` elements |
| `vec_delete(vec)` | Free the backing storage |
| `vec_resize(vec, new_size)` | Grow capacity to `new_size` (no-op if already large enough) |
| `vec_clone(dest, orig)` | Clone a vector origin vector to a destiny vector |
| `vec_set(vec, index, item)` | Copy an element into a slot |
| `vec_add(vec, item)` | Append an element, resizing if needed |
| `vec_insert(vec, index, item)` | Insert at `index`, shifting later elements right |
| `vec_at(vec, index)` | Pointer to the element at `index` |

Use `VEC_AT_AS(vec, type, index)` to read an element with the correct type:

```c
#include "vec.h"

Vec v = init_vec(4, sizeof(int));
vec_add(&v, &(int){42});
vec_add(&v, &(int){99});

int first = VEC_AT_AS(&v, int, 0);  // 42

delete_vec(&v);
```

## LL

A type-erased doubly linked list. Each node stores a copy of the bytes you pass in (`item_size` + `data`). Elements are indexed from `0` at the head.

| Function | Description |
|----------|-------------|
| `ll_init()` | Create an empty list (`head`, `tail`, `length`) |
| `ll_delete(ll)` | Free all nodes and their data |
| `ll_clone(dest, orig)` | Deep-copy `orig` into `dest` |
| `ll_push(ll, item_size, item)` | Append a copy at the tail |
| `ll_shift(ll, item_size, item)` | Prepend a copy at the head |
| `ll_get_at(ll, index)` | Pointer to the node at `index`, or `NULL` |
| `ll_remove_at(ll, index)` | Remove the node at `index`; returns `true` on success |
| `ll_for_each(ll, func)` | Call `func(node, index)` for each node, head to tail |

```c
#include "ll.h"

LL list = ll_init();

ll_push(&list, sizeof(int), &(int){42});
ll_push(&list, sizeof(int), &(int){99});

int value = *(int *)ll_get_at(&list, 0)->data;  // 42

ll_remove_at(&list, 0);
ll_delete(&list);
```

## Project layout

```
src/          Library source (vec.c, vec.h, ll.c, ll.h)
tests/        Criterion test suites
build/        Compiled objects and test binary (generated)
Makefile      Build and test targets
```

## Requirements

- A C11 compiler (`cc` / GCC / Clang)
- [Criterion](https://github.com/Snaipe/Criterion) — testing framework (`libcriterion`)

On Arch Linux:

```bash
sudo pacman -S criterion
```

## Testing

```bash
make test
```

Or run the binary directly after building:

```bash
./build/tests
```