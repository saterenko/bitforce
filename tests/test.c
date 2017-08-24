#include <stdio.h>
#include <stdlib.h>

#include "../bitforce.h"

#define MAX_ELEMENTS 10

typedef struct
{
    int is_skip_video;
    int categories_size;
    int categories[MAX_ELEMENTS];
    int countries_size;
    int countries[MAX_ELEMENTS];
    int domains_size;
    char *domains[MAX_ELEMENTS];
    int width;
    int height;
    int duration;
    int bitrate;
    char *mime_type;

} element_t;

int
main(int argc, char **argv)
{
    bitforce_t *bf = bitforce_new();
    bitforce_filter_t *categories_filter = bitforce_filter_new(bf, BITFORCE_FILTER_EQ_INT);
    bitforce_filter_t *mime_type_filter = bitforce_filter_new(bf, BITFORCE_FILTER_EQ_STR);
    /**/
    for (int i = 0; i < 1000; i++) {
        int n = random() % 32;
        bitforce_filter_set(categories_filter, i, BITFORCE_LIMIT_ALLOW, &n, 0, NULL);
        bitforce_filter_set(mime_type_filter, i, BITFORCE_LIMIT_ALLOW, "image/jpeg", 10);
    }
    /**/
    bitforce_query_t *query = bitforce_query_new(bf);
    bitforce_query_add_int(query, categories_filter, 10);
    bitforce_query_add_int(query, categories_filter, 20);
    bitforce_query_add_int(query, categories_filter, 30);
    bitforce_query_add_str(query, categories_filter, "image/jpeg", 10);
    bitforce_query_add_str(query, categories_filter, "image/png", 9);
    bitforce_query_add_str(query, categories_filter, "image/gif", 9);
    bitforce_res_t *res = bitforce_find(query);
    if (!res) {
        printf("error, res == NULL\n");
        exit(1);
    }
    printf("res.size: %d\n", res->size);
    for (int i = 0; i < res->size; i++) {
        printf("  [%d]: index: %d, ptr: %x\n", res->els[i].index, res->els[i].ptr);
    }
    bitforce_res_delete(res);
    bitforce_query_delete(query);
    bitforce_delete(bf);

    // bitforce_filter_t *skip_video_filter = bitforce_filter_new("skip_video_filter", BITFORCE_FILTER_BOOL);
    // bitforce_filter_t *countries_filter = bitforce_filter_new("countries_filter", BITFORCE_FILTER_EQ_INT);
    // bitforce_filter_t *domains_filter = bitforce_filter_new("domains_filter", BITFORCE_FILTER_EQ_STR);
    // bitforce_filter_t *width_filter = bitforce_filter_new("width_filter", BITFORCE_FILTER_EQ_INT);
    // bitforce_filter_t *height_filter = bitforce_filter_new("height_filter", BITFORCE_FILTER_EQ_INT);
    // bitforce_filter_t *duration_filter = bitforce_filter_new("duration_filter", BITFORCE_FILTER_RANGE_INT);
    // bitforce_filter_t *bitrate_filter = bitforce_filter_new("bitrate_filter", BITFORCE_FILTER_RANGE_INT);
    // bitforce_filter_t *mime_type_filter = bitforce_filter_new("mime_type_filter", BITFORCE_FILTER_EQ_STR);

}
