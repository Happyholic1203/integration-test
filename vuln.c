#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

#include "vuln.h"

static const char * const name_str = "name:";
/*
 * This function is obviously broken
 */
bool person_info_parse_file(person_info_t * person_info, const char * const in, size_t in_len) {
    int last_pos = 0;
    
    int name_strlen = strlen(name_str);
    // Ensure 'name:' is there
    for (int i = 0; i < name_strlen; i++) {
        if (i >= in_len || in[i] != name_str[i]) {
            return false;
        }
        last_pos = i;
    }

    last_pos++; // Move to after semicolon

    // Skip whitespace after colon
    for (; last_pos < in_len && isspace(in[last_pos]); last_pos++);

    strncpy(person_info->name, in + last_pos, in_len - last_pos);

    return true;
}