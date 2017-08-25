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
    for (int i = 0; i < 128; i++) {
        test_int_eq(bitforce_bitset_get(&b1, i), 0);
        test_int_eq(bitforce_bitset_get(&b2, i), 1);
    }
    /**/
    bitforce_bitset_set(&b1, 0);
    test_int_eq(b1.size, BITFORCE_BITSET_SIZE_ALIGNMENT);
    test_int_eq(bitforce_bitset_get(&b1, 0), 1);
    for (int i = 0; i < 128; i++) {
        if (i == 0) {
            test_int_eq(bitforce_bitset_get(&b1, i), 1);
        } else {
            test_int_eq(bitforce_bitset_get(&b1, i), 0);
        }
    }
    bitforce_bitset_set(&b1, 31);
    test_int_eq(b1.size, 4);
    for (int i = 0; i < 128; i++) {
        if (i == 0 || i == 31) {
            test_int_eq(bitforce_bitset_get(&b1, i), 1);
        } else {
            test_int_eq(bitforce_bitset_get(&b1, i), 0);
        }
    }
    bitforce_bitset_set(&b1, 63);
    test_int_eq(b1.size, 4);
    for (int i = 0; i < 128; i++) {
        if (i == 0 || i == 31 || i == 63) {
            test_int_eq(bitforce_bitset_get(&b1, i), 1);
        } else {
            test_int_eq(bitforce_bitset_get(&b1, i), 0);
        }
    }
    bitforce_bitset_set(&b1, 64);
    test_int_eq(b1.size, 4);
    for (int i = 0; i < 128; i++) {
        if (i == 0 || i == 31 || i == 63 || i == 64) {
            test_int_eq(bitforce_bitset_get(&b1, i), 1);
        } else {
            test_int_eq(bitforce_bitset_get(&b1, i), 0);
        }
    }
    bitforce_bitset_set(&b1, 127);
    test_int_eq(b1.size, 4);
    for (int i = 0; i < 128; i++) {
        if (i == 0 || i == 31 || i == 63 || i == 64 || i == 127) {
            test_int_eq(bitforce_bitset_get(&b1, i), 1);
        } else {
            test_int_eq(bitforce_bitset_get(&b1, i), 0);
        }
    }
    bitforce_bitset_set(&b1, 128);
    test_int_eq(b1.size, 4);
    for (int i = 0; i < 196; i++) {
        if (i == 0 || i == 31 || i == 63 || i == 64 || i == 127 || i == 128) {
            test_int_eq(bitforce_bitset_get(&b1, i), 1);
        } else {
            test_int_eq(bitforce_bitset_get(&b1, i), 0);
        }
    }
    bitforce_bitset_set(&b1, 511);
    test_int_eq(b1.size, 8);
    /**/
    bitforce_bitset_unset(&b1, 31);
    for (int i = 0; i < 196; i++) {
        if (i == 0 || i == 63 || i == 64 || i == 127 || i == 128) {
            test_int_eq(bitforce_bitset_get(&b1, i), 1);
        } else {
            test_int_eq(bitforce_bitset_get(&b1, i), 0);
        }
    }
    bitforce_bitset_unset(&b1, 128);
    for (int i = 0; i < 196; i++) {
        if (i == 0 || i == 63 || i == 64 || i == 127) {
            test_int_eq(bitforce_bitset_get(&b1, i), 1);
        } else {
            test_int_eq(bitforce_bitset_get(&b1, i), 0);
        }
    }
}
END;

BEGIN_TEST(test_bitforce_bitset_operations)
{
    bitforce_bitset_t b1;
    bitforce_bitset_init(&b1, 0);
    for (int i = 0; i < 128; i += 2) {
        bitforce_bitset_set(&b1, i);
    }
    bitforce_bitset_t b2;
    bitforce_bitset_init(&b2, 1);
    /*  and  */
    bitforce_bitset_and(&b1, &b2);
    for (int i = 0; i < 128; i++) {
        if (i % 2 == 0) {
            test_int_eq(bitforce_bitset_get(&b1, i), 1);
        } else {
            test_int_eq(bitforce_bitset_get(&b1, i), 0);
        }
    }
    /*  or */
    bitforce_bitset_or(&b1, &b2);
    for (int i = 0; i < 128; i++) {
        test_int_eq(bitforce_bitset_get(&b1, i), 1);
    }
    /**/
    bitforce_bitset_t b3;
    bitforce_bitset_init(&b3, 0);
    for (int i = 0; i < 128; i += 2) {
        bitforce_bitset_set(&b3, i);
    }
    /*  xor  */
    bitforce_bitset_xor(&b1, &b3);
    for (int i = 0; i < 128; i++) {
        if (i % 2 == 0) {
            test_int_eq(bitforce_bitset_get(&b1, i), 0);
        } else {
            test_int_eq(bitforce_bitset_get(&b1, i), 1);
        }
    }
}
END;

int
main(int argc, char **argv)
{
    RUN_TEST(test_bitforce_bitset);
    RUN_TEST(test_bitforce_bitset_operations);

    exit(0);
}
