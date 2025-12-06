#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include "utils.h"

// Helper to check if a process is running
int is_pacman_running() {
    // Simple check using pgrep. Returns 0 if found (system() exit code).
    // system("pgrep -x pacman") returns 0 if found, 1 if not.
    int ret = system("pgrep -x pacman > /dev/null 2>&1");
    return (ret == 0);
}

void check_lock_file() {
    print_header("Pacman Lock Status");
    
    if (access("/var/lib/pacman/db.lck", F_OK) != -1) {
        // Lock exists
        if (is_pacman_running()) {
            printf("  %s[i] Pacman is currently running (db.lck present).%s\n", COLOR_BLUE, COLOR_RESET);
        } else {
            printf("  %s[!] ZOMBIE LOCK DETECTED! (db.lck exists but pacman is not running)%s\n", COLOR_RED, COLOR_RESET);
            printf("      %sUpdate operations will fail until this is removed.%s\n", COLOR_YELLOW, COLOR_RESET);
            // Return value or state could be used for interactive fixer later
        }
    } else {
        printf("%sPacman database is unlocked.%s\n", COLOR_GREEN, COLOR_RESET);
    }
}

void check_pacman_timeline() {
    print_header("System Timeline (Last 48h)");
    
    FILE *fp = fopen("/var/log/pacman.log", "r");
    if (!fp) {
        print_error("Could not read /var/log/pacman.log");
        return;
    }

    // Get current time
    time_t now = time(NULL);
    struct tm *tm_now = localtime(&now);
    
    // We need to parse lines like: "[2023-10-27T09:30:00-0500] [ALPM] upgraded linux (6.5->6.6)"
    // This is complex to parse strictly by time without strptime (which can be tricky with timezones).
    // simplified approach: Check the DATE string.
    // If today is 2023-10-27, we look for lines containing 2023-10-27 and 2023-10-26.
    
    char today_str[20];
    char yesterday_str[20];
    
    strftime(today_str, sizeof(today_str), "%Y-%m-%d", tm_now);
    
    // Go back 24h
    now -= (24 * 60 * 60);
    tm_now = localtime(&now);
    strftime(yesterday_str, sizeof(yesterday_str), "%Y-%m-%d", tm_now);

    int upgraded = 0;
    int installed = 0;
    int removed = 0;
    
    char line[512];
    // Optimization: Instead of reading the whole file, we could seek to end and read back, 
    // but logs are usually text. We'll read all (fast enough for typical logs) or use tail logic.
    // For simplicity/robustness in C without external deps, we read forward.
    
    while (fgets(line, sizeof(line), fp)) {
        // Check if line starts with date
        if (strstr(line, today_str) || strstr(line, yesterday_str)) {
            if (strstr(line, "[ALPM] upgraded")) upgraded++;
            else if (strstr(line, "[ALPM] installed")) installed++;
            else if (strstr(line, "[ALPM] removed")) removed++;
        }
    }
    fclose(fp);

    if (upgraded == 0 && installed == 0 && removed == 0) {
        printf("%sNo package activity in the last 48 hours.%s\n", COLOR_CYAN, COLOR_RESET);
    } else {
        printf("  %sUpgraded:%s  %d\n", COLOR_BLUE, COLOR_RESET, upgraded);
        printf("  %sInstalled:%s %d\n", COLOR_GREEN, COLOR_RESET, installed);
        printf("  %sRemoved:%s   %d\n", COLOR_RED, COLOR_RESET, removed);
        
        if (upgraded > 20) {
             printf("\n  %s(Heavy update activity recently - check logs if system is unstable)%s\n", COLOR_YELLOW, COLOR_RESET);
        }
    }
}
