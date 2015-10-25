#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void find_and_replace(char *str, char *find, char *replace) {
    char *p = str;
    while((p = strcasestr(p, find)) != NULL) {
        sprintf(p + strlen(replace), "%s", p + strlen(find));
        strncpy(p, replace, strlen(replace));
        p += strlen(replace);
    }
}

int main() {
    char str[80], find[20], replace[20];
    strcpy(str, "The quick brown fox jumped over the lazy dog");
    strcpy(find, "the");
    strcpy(replace, "a");
    find_and_replace(str, find, replace);
    printf("%s\n", str);
}
