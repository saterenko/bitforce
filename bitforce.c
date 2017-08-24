#include "bitforce.h"

bitforce_t *
bitforce_new()
{

}

void
bitforce_delete(bitforce_t *bf)
{

}

bitforce_filter_t *
bitforce_filter_new(bitforce_t *bf, const char *name, enum bitforce_filter_type_e type)
{

}

bitforce_query_t *
bitforce_query_new(bitforce_t *bf)
{

}

void
bitforce_query_delete(bitforce_query_t *query)
{

}

int
bitforce_query_add_int(bitforce_query_t *query, bitforce_filter_t *filter, int value)
{

}

int
bitforce_query_add_str(bitforce_query_t *query, bitforce_filter_t *filter, const char *value, int value_size)
{

}

bitforce_res_t *
bitforce_find(bitforce_query_t *query)
{

}

void
bitforce_res_delete(bitforce_res_t *res)
{
    
}
