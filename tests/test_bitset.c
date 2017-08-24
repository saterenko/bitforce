#include "test.h"
#include "../bitforce_bitset.h"

BEGIN_TEST(test_bitforce_bitset)
{
    bitforce_bitset_t b1;
    bitforce_bitset_init(&b1, 0);
    test_int_eq(b1.size, 0);
    test_int_eq(b1.default_value, 0);
    test_ptr_eq(b1.data, NULL);
    test_ptr_eq(b1.bitset, NULL);
    /**/
    bitforce_bitset_t b2;
    bitforce_bitset_init(&b2, 1);
    test_int_eq(b2.size, 0);
    test_int_eq(b2.default_value, 0xffffffffffffffff);
    test_ptr_eq(b2.data, NULL);
    test_ptr_eq(b2.bitset, NULL);
    /**/
    test_int_eq(bitforce_bitset_get(&b1, 0), 0);
    test_int_eq(bitforce_bitset_get(&b1, 127), 0);
    test_int_eq(bitforce_bitset_get(&b2, 0), 1);
    test_int_eq(bitforce_bitset_get(&b2, 127), 1);
    /**/
    bitforce_bitset_set(&b1, 0);
    test_int_eq(b1.size, 1);
    test_int_eq(bitforce_bitset_get(&b1, 0), 1);
    bitforce_bitset_set(&b1, 31);
    test_int_eq(b1.size, 1);
    test_int_eq(bitforce_bitset_get(&b1, 31), 1);
    bitforce_bitset_set(&b1, 63);
    test_int_eq(b1.size, 1);
    test_int_eq(bitforce_bitset_get(&b1, 63), 1);
    bitforce_bitset_set(&b1, 64);
    test_int_eq(b1.size, 2);
    test_int_eq(bitforce_bitset_get(&b1, 64), 1);
    bitforce_bitset_set(&b1, 127);
    test_int_eq(b1.size, 2);
    test_int_eq(bitforce_bitset_get(&b1, 127), 1);
    bitforce_bitset_set(&b1, 128);
    test_int_eq(b1.size, 3);
    test_int_eq(bitforce_bitset_get(&b1, 128), 1);
    /**/
    bitforce_bitset_unset(&b1, 31);
    test_int_eq(bitforce_bitset_get(&b1, 31), 0);
    bitforce_bitset_unset(&b1, 128);
    test_int_eq(bitforce_bitset_get(&b1, 128), 0);
    /**/
    bitforce_bitset_set_value(&b1, 31, 1);
    test_int_eq(bitforce_bitset_get(&b1, 31), 1);
    bitforce_bitset_set_value(&b1, 31, 0);
    test_int_eq(bitforce_bitset_get(&b1, 31), 0);
}
END;

BEGIN_TEST(test_bitforce_bitset_operations)
{
    bitforce_bitset_t b1;
    bitforce_bitset_init(&b1, 0);
    bitforce_bitset_set(&b1, 1);
    bitforce_bitset_set(&b1, 63);
    bitforce_bitset_set(&b1, 64);
    bitforce_bitset_set(&b1, 127);
    bitforce_bitset_t b2;
    bitforce_bitset_init(&b2, 1);
    /**/
    bitforce_bitset_and(&b1, &b2);
    test_int_eq(bitforce_bitset_get(&b1, 1), 1);
    test_int_eq(bitforce_bitset_get(&b1, 63), 1);
    test_int_eq(bitforce_bitset_get(&b1, 64), 1);
    test_int_eq(bitforce_bitset_get(&b1, 127), 1);
}
END;

int
main(int argc, char **argv)
{
    RUN_TEST(test_bitforce_bitset);
    RUN_TEST(test_bitforce_bitset_operations);
    exit(0);
}
