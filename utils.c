#include "utils.h"
#include <string.h>

void strip_newline(char *s) {
    size_t i = strlen(s);
    if (i==0) return;
    if (s[i-1]=='\n' || s[i-1]=='\r') s[i-1] = '\0';
    // handle CRLF
    i = strlen(s);
    if (i>0 && s[i-1]=='\r') s[i-1] = '\0';
}

