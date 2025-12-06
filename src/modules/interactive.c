#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "utils.h"

int ask_user(const char *question) {
    char input[16];
    printf("%s%s [y/N]: %s", COLOR_YELLOW, question, COLOR_RESET);
    
    if (fgets(input, sizeof(input), stdin) == NULL) {
        return 0;
    }
    
    return (tolower(input[0]) == 'y');
}

void execute_fix(const char *command) {
    printf("%sRunning: %s%s\n", COLOR_BLUE, command, COLOR_RESET);
    // Use system() to allow the command to take over stdin/stdout (needed for sudo password)
    int ret = system(command);
    if (ret == 0) {
        printf("%s%s[✔] Fix applied successfully.%s\n", COLOR_BOLD, COLOR_GREEN, COLOR_RESET);
    } else {
        printf("%s%s[✘] Fix failed or cancelled.%s\n", COLOR_BOLD, COLOR_RED, COLOR_RESET);
    }
}

