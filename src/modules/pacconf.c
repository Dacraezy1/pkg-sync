#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void check_pacnew_files() {
    print_header("Configuration Health (.pacnew/.pacsave)");
    
    // Find .pacnew and .pacsave files in /etc
    // Using 'find' is robust and standard.
    // 2>/dev/null to silence permission denied errors if run without sudo (though usually readable)
    const char *cmd = "find /etc -name \"*.pacnew\" -o -name \"*.pacsave\" 2>/dev/null";
    
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        print_error("Failed to search for config files");
        return;
    }

    char path[1024];
    int count = 0;

    while (fgets(path, sizeof(path), fp) != NULL) {
        path[strcspn(path, "\n")] = 0;
        if (strlen(path) > 0) {
            count++;
            printf("  %s%s%s\n", COLOR_YELLOW, path, COLOR_RESET);
        }
    }
    pclose(fp);

    if (count == 0) {
        printf("%sNo config file conflicts found.%s\n", COLOR_GREEN, COLOR_RESET);
    } else {
        printf("\n  %sACTION REQUIRED: Merge these files manually or use 'pacdiff'.%s\n", COLOR_RED, COLOR_RESET);
    }
}
