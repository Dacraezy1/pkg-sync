#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

#define BUFFER_SIZE 1024

void print_header(const char *title) {
    printf("\n%s%s=== %s ===%s\n", COLOR_BOLD, COLOR_CYAN, title, COLOR_RESET);
}

void print_error(const char *msg) {
    fprintf(stderr, "%sError: %s%s\n", COLOR_RED, msg, COLOR_RESET);
}

int run_and_print(const char *cmd, const char *empty_msg, const char *line_prefix) {
    FILE *fp;
    char path[BUFFER_SIZE];
    int count = 0;

    fp = popen(cmd, "r");
    if (fp == NULL) {
        print_error("Failed to run command");
        return -1;
    }

    while (fgets(path, sizeof(path), fp) != NULL) {
        path[strcspn(path, "\n")] = 0;
        if (strlen(path) > 0) {
            count++;
            printf("%s%s%s\n", line_prefix, path, COLOR_RESET);
        }
    }

    if (count == 0) {
        printf("%s%s%s\n", COLOR_GREEN, empty_msg, COLOR_RESET);
    }

    pclose(fp);
    return count;
}

