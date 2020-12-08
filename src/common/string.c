#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "string.h"

string *string_new(const char *str) {
    size_t len = strlen(str);
    string *str1 = malloc(sizeof(string));
    if (str1 == NULL) {
        goto allocate_string_fail;
    }
    char *value = malloc(len + 1);
    if (value == NULL) {
        goto allocate_value_fail;
    }
    memcpy(value, str, len);
    value[len] = '\0';
    str1->length = len;
    str1->value = value;
    return str1;
allocate_value_fail:
    free(str1);
    fprintf(stderr, "Create char array fail.");
allocate_string_fail:
    fprintf(stderr, "Create string fail.");
    return NULL;
}

void string_delete(string *str) {
    str->length = 0;
    free((char *) str->value);
    str->value = NULL;
    free(str);
}
