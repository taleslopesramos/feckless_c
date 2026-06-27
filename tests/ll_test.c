// tests/ll_test.c
#include <criterion/criterion.h>
#include "../src/ll.h"
#include <stdio.h>

Test(ll, init)
{
    LL ll = ll_init();

    ll_delete(&ll);
}

Test(ll, push_data_with_pointer)
{
    LL ll = ll_init();

    int *value = malloc(sizeof(int));
    *value = 123;

    ll_push(&ll, sizeof(int), value);

    cr_assert_not_null(ll.head);
    cr_assert_not_null(ll.tail);

    cr_assert_neq(ll.tail->data, value);

    cr_assert_eq(ll.head, ll.tail);

    free(value);
    ll_delete(&ll);
}

Test(ll, push_data_with_constant)
{
    LL ll = ll_init();

    ll_push(&ll, sizeof(int), &(int){123});

    cr_assert_not_null(ll.head);
    cr_assert_not_null(ll.tail);
    cr_assert_eq(ll.head, ll.tail);
    cr_assert_eq(*((int *)ll.head->data), 123);
    cr_assert_eq(ll.head->item_size, sizeof(int));

    ll_delete(&ll);
}

Test(ll, push_homogeneous_dataset)
{
    LL ll = ll_init();

    ll_push(&ll, sizeof(int), &(int){123});
    cr_assert_eq(*((int *)ll.tail->data), 123);
    cr_assert_eq(ll.tail->item_size, sizeof(int));

    ll_push(&ll, sizeof(int), &(int){123});
    cr_assert_eq(*((int *)ll.tail->data), 123);
    cr_assert_eq(ll.tail->item_size, sizeof(int));

    ll_push(&ll, sizeof(int), &(int){123});
    cr_assert_eq(*((int *)ll.tail->data), 123);
    cr_assert_eq(ll.tail->item_size, sizeof(int));

    ll_delete(&ll);
}

Test(ll, push_heterogeneous_dataset)
{
    LL ll = ll_init();

    struct my_struct
    {
        char key;
        char value;
    };

    struct my_struct example = {
        .key = 'a',
        .value = 'b',
    };

    ll_push(&ll, sizeof(int), &(int){123});
    cr_assert_eq(*((int *)ll.tail->data), 123);

    ll_push(&ll, sizeof(double), &(double){123.123});
    cr_assert_eq(*((double *)ll.tail->data), 123.123);

    ll_push(&ll, sizeof(struct my_struct), &example);
    struct my_struct tail_data = *((struct my_struct *)ll.tail->data);
    cr_assert_eq(tail_data.key, 'a');
    cr_assert_eq(tail_data.value, 'b');

    ll_delete(&ll);
}

Test(ll, remove_item_when_head_eq_tails)
{
    LL ll = ll_init();

    ll_push(&ll, sizeof(int), &(int){123});
    cr_assert_eq(ll.length, 1);

    ll_remove_at(&ll, 0);
    cr_assert_eq(ll.length, 0);

    ll_delete(&ll);
}

Test(ll, remove_tail_item)
{
    LL ll = ll_init();

    ll_push(&ll, sizeof(int), &(int){123});
    cr_assert_eq(ll.length, 1);

    ll_push(&ll, sizeof(int), &(int){157});
    cr_assert_eq(ll.length, 2);

    ll_remove_at(&ll, 1);
    cr_assert_eq(ll.length, 1);
    cr_assert_eq(*((int *)ll.tail->data), 123);

    ll_delete(&ll);
}

Test(ll, remove_head_item)
{
    LL ll = ll_init();

    ll_push(&ll, sizeof(int), &(int){123});
    cr_assert_eq(ll.length, 1);

    ll_push(&ll, sizeof(int), &(int){157});
    cr_assert_eq(ll.length, 2);

    bool res = ll_remove_at(&ll, 0);
    cr_assert_eq(res, true);
    cr_assert_eq(ll.length, 1);
    cr_assert_eq(*((int *)ll.tail->data), 157);

    ll_delete(&ll);
}

Test(ll, remove_middle_item)
{
    LL ll = ll_init();

    ll_push(&ll, sizeof(int), &(int){123});
    cr_assert_eq(ll.length, 1);

    ll_push(&ll, sizeof(int), &(int){157});
    cr_assert_eq(ll.length, 2);

    ll_push(&ll, sizeof(int), &(int){157});
    cr_assert_eq(ll.length, 3);

    bool res = ll_remove_at(&ll, 1);
    cr_assert_eq(res, true);

    ll_delete(&ll);
}

void assert_3(Node *item, size_t index)
{
    if (index == 0)
    {
        cr_assert_eq((*(int *)item->data), 123);
    }
    else if (index == 1)
    {
        cr_assert_eq((*(int *)item->data), 157);
    }
    else if (index == 2)
    {
        cr_assert_eq((*(int *)item->data), 777);
    }
}

Test(ll, for_each)
{
    LL ll = ll_init();

    ll_push(&ll, sizeof(int), &(int){123});
    ll_push(&ll, sizeof(int), &(int){157});
    ll_push(&ll, sizeof(int), &(int){777});

    ll_for_each(&ll, assert_3);

    ll_delete(&ll);
}

Test(ll, clone)
{
    LL ll1 = ll_init(), ll2 = ll_init();

    ll_push(&ll1, sizeof(int), &(int){123});
    ll_push(&ll1, sizeof(int), &(int){157});
    ll_push(&ll1, sizeof(int), &(int){777});

    ll_clone(&ll2, &ll1);

    cr_assert_neq(ll2.head->data, ll1.head->data);
    cr_assert_neq(ll_at(&ll2, 1)->data, ll_at(&ll1, 1)->data);
    cr_assert_neq(ll2.tail->data, ll1.tail->data);

    cr_assert_eq((*(int *)ll2.head->data), (*(int *)ll1.head->data));
    cr_assert_eq((*(int *)ll_at(&ll2, 1)->data), (*(int *)ll_at(&ll1, 1)->data));
    cr_assert_eq((*(int *)ll2.tail->data), (*(int *)ll1.tail->data));

    ll_delete(&ll1);
    ll_delete(&ll2);
}