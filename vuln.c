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
    
    // Copy the name into person_info->name
    int name_start = last_pos;
    int name_len = 0;
    
    // Count characters until we hit whitespace or end of string
    int temp_pos = last_pos;
    while (temp_pos < in_len && !isspace(in[temp_pos])) {
        temp_pos++;
        name_len++;
    }
    
    // Copy the name, ensuring we don't exceed MAX_STRLEN
    if (name_len >= MAX_STRLEN) {
        name_len = MAX_STRLEN - 1;
    }
    
    strncpy(person_info->name, in + name_start, name_len);
    person_info->name[name_len] = '\0'; // Ensure null termination

    return true;
}