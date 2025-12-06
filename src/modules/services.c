#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

void check_failed_services() {
    print_header("Failed System Services");
    
    // systemctl list-units --state=failed --no-legend
    const char *cmd = "systemctl list-units --state=failed --no-legend";
    
    FILE *fp = popen(cmd, "r");
    if (fp == NULL) {
        print_error("Failed to query systemd");
        return;
    }

    char line[1024];
    int count = 0;

    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strcspn(line, "\n")] = 0;
        // Extract just the service name (first column)
        char *space = strchr(line, ' ');
        if (space) *space = '\0';
        
        if (strlen(line) > 0) {
            count++;
            printf("  %s%s%s (failed)\n", COLOR_RED, line, COLOR_RESET);
        }
    }
    pclose(fp);

    if (count == 0) {
        printf("%sAll services healthy.%s\n", COLOR_GREEN, COLOR_RESET);
    }
}
