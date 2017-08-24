#ifndef BITFORCE_H
#define BITFORCE_H

#include "bitforce_core.h"
#include "bitforce_filter.h"

static bitforce_t *
bitforce_new()
{
    bitforce_t *ctx = (bitforce_t *) malloc(sizeof(bitforce_t));
    if (!ctx) {
        return NULL;
    }
    memset(ctx, 0, sizeof(bitforce_t));
    return ctx;
}

static void
bitforce_delete(bitforce_t *ctx)
{
    if (ctx) {
        free(ctx);
    }
}

#endif
