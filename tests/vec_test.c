// tests/test_vec.c
#include <criterion/criterion.h>
#include "../src/vec.h"

Test(vec, starts_empty) {
    Vec v = vec_init(10, sizeof(int));
    vec_add(&v, &(int){123});
    
    cr_assert_eq(v.length, 1);
    cr_assert_eq(v.total_size, 10);
    cr_assert_not_null(v.data);

    vec_delete(&v);
}

Test(vec, add_item_on_empty) {
    Vec v = vec_init(2, sizeof(int));
    bool result = vec_add(&v, &(int){123});

    cr_assert_eq(result, true);
    cr_assert_eq(v.length, 1, "expected length to be 1, got %zu", v.length);
    cr_assert_eq(v.total_size, 2, "expected total_size to be 2, got %zu", v.total_size);
    cr_assert_not_null(v.data);

    vec_delete(&v);
}

Test(vec, resize_on_add) {
    Vec v = vec_init(2, sizeof(int));
    cr_assert_eq(v.length, 0,"expected length to be 0, got %zu", v.length);
    cr_assert_eq(v.total_size, 2, "expected total_size to be 2, got %zu", v.length);

    bool add_res = false;
    add_res = vec_add(&v, &(int){123});
    cr_assert_eq(v.length, 1,"expected length to be 1, got %zu", v.length);
    cr_assert_eq(v.total_size, 2, "expected total_size to be 2, got %zu", v.length);
    cr_assert_eq(add_res, true);

    add_res = vec_add(&v, &(int){321});
    cr_assert_eq(v.length, 2,"expected length to be 2, got %zu", v.length);
    cr_assert_eq(v.total_size, 2, "expected total_size to be 2, got %zu", v.length);
    cr_assert_eq(add_res, true);

    add_res = vec_add(&v, &(int){157});
    cr_assert_eq(v.length, 3,"expected length to be 3, got %zu", v.length);
    cr_assert_eq(v.total_size, 4, "expected total_size to be 4, got %zu", v.length);
    cr_assert_eq(add_res, true);

    cr_assert_eq(VEC_AT_AS(&v, int, 0), 123);
    cr_assert_eq(VEC_AT_AS(&v, int, 1), 321);
    cr_assert_eq(VEC_AT_AS(&v, int, 2), 157);

    vec_delete(&v);
}

Test(vec, insert_on_index) {
    Vec v = vec_init(2, sizeof(int));
    vec_insert(&v, 0, &(int){123});
    vec_insert(&v, 0, &(int){321});

    cr_assert_eq(v.length, 2);
    cr_assert_eq(v.total_size, 2);
    cr_assert_not_null(v.data);

    cr_assert_eq(VEC_AT_AS(&v, int, 0), 321);
    cr_assert_eq(VEC_AT_AS(&v, int, 1), 123);

    vec_delete(&v);
}

Test(vec, resize_on_insert) {
    Vec v = vec_init(2, sizeof(int));
    vec_insert(&v, 0, &(int){123});
    vec_insert(&v, 0, &(int){321});
    vec_insert(&v, 0, &(int){157});

    cr_assert_eq(v.length, 3);
    cr_assert_eq(v.total_size, 4);
    cr_assert_not_null(v.data);

    cr_assert_eq(VEC_AT_AS(&v, int, 0), 157);
    cr_assert_eq(VEC_AT_AS(&v, int, 1), 321);
    cr_assert_eq(VEC_AT_AS(&v, int, 2), 123);

    vec_delete(&v);
}

Test(vec, clone_data) {
    Vec v1 = vec_init(4, sizeof(int));
    Vec v2 = vec_init(4, sizeof(int));

    vec_add(&v1, &(int){123});
    vec_add(&v1, &(int){321});
    vec_add(&v1, &(int){157});

    vec_clone(&v2, &v1);

    cr_assert_neq(v1.data, v2.data);
    cr_assert_eq(v2.item_size, v1.item_size);
    cr_assert_eq(v2.length, v1.length);
    cr_assert_eq(v2.total_size, v1.total_size);

    cr_assert_eq(VEC_AT_AS(&v2, int, 0), 123);
    cr_assert_eq(VEC_AT_AS(&v2, int, 1), 321);
    cr_assert_eq(VEC_AT_AS(&v2, int, 2), 157);

    vec_delete(&v1);
    vec_delete(&v2);
}