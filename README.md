# Feckless C

A minimal library with some half-assed utilities for C.

Right now the only module is a generic dynamic array (`Vec`).

## Vec

A type-erased growable array. You pick the element type at initialization via `item_size`; the vector stores a contiguous block of bytes and grows by doubling capacity when full.

| Function | Description |
|----------|-------------|
| `init_vec(initial_size, item_size)` | Allocate a vector with room for `initial_size` elements |
| `delete_vec(vec)` | Free the backing storage |
| `vec_resize(vec, new_size)` | Grow capacity to `new_size` (no-op if already large enough) |
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

## Project layout

```
src/          Library source (vec.c, vec.h)
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