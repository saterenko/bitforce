#ifndef BITFORCE_FILTER_H
#define BITFORCE_FILTER_H

#include "bitforce_core.h"

static inline bitforce_filter_t *
bitforce_filter_new(bitforce_t *ctx, enum bitforce_filter_type_e type)
{
    if (ctx->filters_count + 1 >= ctx->filter_size) {
        if (ctx->filter_size) {
            int size = (ctx->filters_size << 1) - (ctx->filters_size >> 1);
            bitforce_filter_t *filters = (bitforce_filter_t *) malloc(sizeof(bitforce_filter_t) * size);
            if (!filters) {
                return NULL;
            }
            memcpy(filters, ctx->filters, sizeof(bitforce_filter_t) * ctx->filters_size);
            memset(&filters[ctx->filters_size], 0, sizeof(bitforce_filter_t) * (size - ctx->filters_size));
            free(ctx->filters);
            ctx->filters_size = size;
            ctx->filters = filters;
        } else {
            ctx->filters = (bitforce_filter_t *) malloc(sizeof(bitforce_filter_t) * 8);
            if (!ctx->filters) {
                return NULL;
            }
            memset(ctx->filters, 0, sizeof(bitforce_filter_t) * 8);
            ctx->filters_size = 8;
        }
    }
    ctx->filters[ctx->filters_count].type = type;
    return &ctx->filters[ctx->filters_count++];
}

static inline int
bitforce_filter_set_bool(bitforce_filter_t *filter, int index, int *value, void *ptr)
{
    return 0;
}

static inline int
bitforce_filter_set(bitforce_filter_t *filter, int index, void *value, int value_size, void *ptr)
{
    switch (filter->type) {
        case BITFORCE_FILTER_EMPTY:
            break;
        case BITFORCE_FILTER_BOOL:
            return bitforce_filter_set_bool(filter, index, (int *) value, ptr);
        case BITFORCE_FILTER_EQ_INT:
            return bitforce_filter_set_bool(filter, index, (int *) value, ptr);
        case BITFORCE_FILTER_EQ_STR:
            return bitforce_filter_set_bool(filter, index, (int *) value, ptr);
        case BITFORCE_FILTER_RANGE_INT:
            return bitforce_filter_set_bool(filter, index, (int *) value, ptr);
        case BITFORCE_FILTER_RANGE_STR:
            return bitforce_filter_set_bool(filter, index, (int *) value, ptr);
    }
}

#endif
