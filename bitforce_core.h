#ifndef BITFORCE_CORE_H
#define BITFORCE_CORE_H

#include <stdint.h>

#define BITFORCE_CACHE_LINE_SIZE 64

#define bitforce_align_ptr(_p, _s) (uintptr_t *) (((uintptr_t) (_p) + ((uintptr_t) _s - 1)) & ~((uintptr_t) _s - 1))

enum bitforce_filter_type_e
{
    BITFORCE_FILTER_EMPTY = 0,
    BITFORCE_FILTER_BOOL,
    BITFORCE_FILTER_EQ_INT,
    BITFORCE_FILTER_EQ_STR,
    BITFORCE_FILTER_RANGE_INT,
    BITFORCE_FILTER_RANGE_STR
};

enum bitforce_limit_type_e
{
    BITFORCE_LIMIT_NONE = 0,
    BITFORCE_LIMIT_ALLOW,
    BITFORCE_LIMIT_REJECT
};

typedef struct
{
    int intex;
    enum bitforce_filter_type_e type;
} bitforce_filter_t;

typedef struct
{
    int filters_count;
    int filters_size;
    bitforce_filter_t *filters;

} bitforce_t;

#endif

