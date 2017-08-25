#ifndef BITFORCE_BITSET_H
#define BITFORCE_BITSET_H

#include <stdint.h>
#include <string.h>

#include "bitforce_core.h"

#define BITFORCE_BITSET_SIZE_ALIGNMENT 4

typedef struct
{
    uint64_t default_value;
    int size;
    uint64_t *data;
    uint64_t *bitset;
} bitforce_bitset_t;

static inline void
bitforce_bitset_init(bitforce_bitset_t *bs, int default_value)
{
    memset(bs, 0, sizeof(bitforce_bitset_t));
    bs->default_value = default_value ? ~0LLU : 0;
}

static inline void
bitforce_bitset_delete(bitforce_bitset_t *bs)
{
    if (bs && bs->data) {
        free(bs->data);
    } 
}

static inline void
bitforce_bitset_expand(bitforce_bitset_t *bs, int size)
{
    if (size > bs->size) {
        size = bitforce_align(size, BITFORCE_BITSET_SIZE_ALIGNMENT);
        uint64_t *data = (uint64_t *) malloc(sizeof(uint64_t) * size + BITFORCE_CACHE_LINE_SIZE);
        if (!data) {
            fprintf(stderr, "can't mallo");
            exit(1);
        }
        uint64_t *bitset = bitforce_align_ptr(data, BITFORCE_CACHE_LINE_SIZE);
        if (bs->size) {
            memcpy(bitset, bs->bitset, sizeof(uint64_t) * bs->size);
            free(bs->data);
        }
        memset(&bitset[bs->size], bs->default_value ? 0xff : 0, sizeof(uint64_t) * (size - bs->size));
        bs->size = size;
        bs->data = data;
        bs->bitset = bitset;
    }
}

static inline int
bitforce_bitset_get(bitforce_bitset_t *bs, int index)
{
    if (index >= sizeof(uint64_t) * 8 * bs->size) {
        return bs->default_value & 1;
    }
    return !!(bs->bitset[index / 64] & (1LLU << (index % 64)));
}

static inline void
bitforce_bitset_set(bitforce_bitset_t *bs, int index)
{
    bitforce_bitset_expand(bs, index / 64 + 1);
    bs->bitset[index / 64] |= 1LLU << (index % 64);
}

static inline void
bitforce_bitset_unset(bitforce_bitset_t *bs, int index)
{
    bitforce_bitset_expand(bs, index / 64 + 1);
    bs->bitset[index / 64] &= ~(1LLU << (index % 64));
}

static inline void
bitforce_bitset_set_value(bitforce_bitset_t *bs, int index, int value)
{
    bitforce_bitset_expand(bs, index / 64 + 1);
    if (value) {
        bs->bitset[index / 64] |= 1LLU << (index % 64);
    } else {
        bs->bitset[index / 64] &= ~(1LLU << (index % 64));
    }
}

static inline void
bitforce_bitset_inverse(bitforce_bitset_t *bs)
{
    bs->default_value = ~bs->default_value;
    uint64_t *p = bs->bitset;
    uint64_t *end = p + bs->size;
    for (; p < end; p++) {
        *p = ~*p;
    }
}

static inline void
bitforce_bitset_and(bitforce_bitset_t *bs1, bitforce_bitset_t *bs2)
{
    bitforce_bitset_expand(bs1, bs2->size);
    for (int i = 0; i < bs2->size; i++) {
        bs1->bitset[i] &= bs2->bitset[i];
    }
    for (int i = bs2->size; i < bs1->size; i++) {
        bs1->bitset[i] &= bs2->default_value;
    }
}

static inline void
bitforce_bitset_or(bitforce_bitset_t *bs1, bitforce_bitset_t *bs2)
{
    for (int i = 0; i < bs2->size; i++) {
        bs1->bitset[i] |= bs2->bitset[i];
    }
    for (int i = bs2->size; i < bs1->size; i++) {
        bs1->bitset[i] |= bs2->default_value;
    }
}

static inline void
bitforce_bitset_xor(bitforce_bitset_t *bs1, bitforce_bitset_t *bs2)
{
    bitforce_bitset_expand(bs1, bs2->size);
    for (int i = 0; i < bs2->size; i++) {
        bs1->bitset[i] ^= bs2->bitset[i];
    }
    for (int i = bs2->size; i < bs1->size; i++) {
        bs1->bitset[i] ^= bs2->default_value;
    }
}

#endif

static inline void
bitforce_bitset_dump(bitforce_bitset_t *bs)
{
    char buf[sizeof(uint64_t) * 8];
    printf("size: %d, default_value: %d, bitset: \n", bs->size, bs->default_value ? 1 : 0);
    for (int i = 0; i < bs->size; i++) {
        for (int n = 0; n < sizeof(uint64_t) * 8; n++) {
            buf[n] = bs->bitset[i] & (1LLU << n) ? '1' : '0';
        }
        printf("    %d: %.*s\n", i, (int) (sizeof(uint64_t) * 8), buf);
    }
}
