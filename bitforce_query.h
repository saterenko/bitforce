#ifndef BITFORCE_QUERY_H
#define BITFORCE_QUERY_H

#include <string.h>

#include "bitforce_core.h"
#include "bitforce_filter.h"

typedef struct
{
    bitforce_t *ctx;
} bitforce_query_t;

typedef struct
{
} bitforce_res_t;

static bitforce_query_t *
bitforce_query_new(bitforce_t *ctx)
{
    bitforce_query_t *q = (bitforce_query_t *) malloc(sizeof(bitforce_query_t));
    if (!q) {
        return NULL;
    }
    memset(q, 0, sizeof(bitforce_query_t));
    return q;
}

static void
bitforce_query_delete(bitforce_query_t *query)
{
    if (q) {
        free(q);
    }
}

static int
bitforce_query_add_int(bitforce_query_t *query, bitforce_filter_t *filter, int value)
{

}

static int
bitforce_query_add_str(bitforce_query_t *query, bitforce_filter_t *filter, const char *value, int value_size)
{

}

static bitforce_res_t *
bitforce_find(bitforce_query_t *query)
{

}

static void
bitforce_res_delete(bitforce_res_t *res)
{

}


#endif
