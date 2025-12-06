#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

// Robust RSS parser that reads the full feed into memory.
void check_arch_news() {
    print_header("Latest Arch Linux News");

    const char *cmd = "curl -sf https://archlinux.org/feeds/news/";
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        printf("%s  [Unable to fetch news]%s\n", COLOR_YELLOW, COLOR_RESET);
        return;
    }

    // Read entire output into memory
    size_t capacity = 16384; // Start with 16KB
    size_t size = 0;
    char *buffer = malloc(capacity);
    if (!buffer) {
        pclose(fp);
        return;
    }

    char chunk[1024];
    while (fgets(chunk, sizeof(chunk), fp) != NULL) {
        size_t len = strlen(chunk);
        if (size + len + 1 > capacity) {
            capacity *= 2;
            char *new_buf = realloc(buffer, capacity);
            if (!new_buf) {
                free(buffer);
                pclose(fp);
                return;
            }
            buffer = new_buf;
        }
        strcpy(buffer + size, chunk);
        size += len;
    }
    pclose(fp);

    if (size == 0) {
        free(buffer);
        return; // Silent fail or empty
    }

    // Parse the buffer
    int count = 0;
    int max_items = 3;
    char *cursor = buffer;

    while (count < max_items) {
        // Find next <item>
        char *item_start = strstr(cursor, "<item>");
        if (!item_start) break;

        // Find <title> after <item>
        char *title_start = strstr(item_start, "<title>");
        if (!title_start) break;
        
        title_start += 7; // Skip <title>
        
        char *title_end = strstr(title_start, "</title>");
        if (!title_end) break;

        // Extract title
        size_t title_len = title_end - title_start;
        if (title_len < 256) {
            char title[256];
            strncpy(title, title_start, title_len);
            title[title_len] = '\0';
            printf("  %s- %s%s\n", COLOR_BLUE, title, COLOR_RESET);
            count++;
        }

        // Move cursor past this item to find the next one
        cursor = title_end;
    }

    if (count > 0) {
        printf("\n  %sCheck https://archlinux.org/news/ for details.%s\n", COLOR_CYAN, COLOR_RESET);
    } else {
        printf("  %s[No news items found]%s\n", COLOR_YELLOW, COLOR_RESET);
    }

    free(buffer);
}
