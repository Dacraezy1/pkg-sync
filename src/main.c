#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "modules/utils.h"
#include "modules/pacconf.h"
#include "modules/news.h"
#include "modules/services.h"
#include "modules/interactive.h"
#include "modules/score.h"
#include "modules/forensics.h"

// Refactored checks to return counts instead of just printing

int count_cmd_lines(const char *cmd) {
    FILE *fp = popen(cmd, "r");
    if (!fp) return 0;
    int count = 0;
    char line[1024];
    while (fgets(line, sizeof(line), fp)) {
        if (strlen(line) > 1) count++;
    }
    pclose(fp);
    return count;
}

#define VERSION "1.0.0"

int main(int argc, char *argv[]) {
    if (argc > 1 && (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-v") == 0)) {
        printf("pkg-sync v%s\n", VERSION);
        return 0;
    }

    printf("\n%s%s=== pkg-sync: Interactive System Manager v%s ===%s\n", COLOR_BOLD, COLOR_BLUE, VERSION, COLOR_RESET);

    // --- 1. Gather Metrics ---
    printf("Analyzing system state...\n");
    
    check_arch_news(); 
    check_pacman_timeline(); // Forensics
    check_lock_file();       // Forensics

    // Repo Updates
    int repo_updates = count_cmd_lines("checkupdates");
    printf("  %-20s: %d pending\n", "Repo Updates", repo_updates);

    // AUR Updates
    int aur_updates = count_cmd_lines("yay -Qu");
    printf("  %-20s: %d pending\n", "AUR Updates", aur_updates);

    // Orphans
    int orphans = count_cmd_lines("pacman -Qdt");
    printf("  %-20s: %d found\n", "Orphans", orphans);

    // Failed Services
    int failed_svcs = count_cmd_lines("systemctl list-units --state=failed --no-legend");
    if (failed_svcs > 0) printf("  %s%-20s: %d failed!%s\n", COLOR_RED, "Services", failed_svcs, COLOR_RESET);
    else printf("  %-20s: %d failed\n", "Services", failed_svcs);

    // Pacnew
    int pacnews = count_cmd_lines("find /etc -name \"*.pacnew\" -o -name \"*.pacsave\" 2>/dev/null");
    if (pacnews > 0) printf("  %s%-20s: %d conflicts!%s\n", COLOR_RED, "Config Files", pacnews, COLOR_RESET);
    else printf("  %-20s: %d conflicts\n", "Config Files", pacnews);


    // --- 2. Score ---
    int total_updates = repo_updates + aur_updates;
    int score = calculate_score(total_updates, orphans, failed_svcs, pacnews);
    print_score_card(score);


    // --- 3. Interactive Fixes ---

    // Updates
    if (total_updates > 0) {
        if (ask_user("Install all updates now?")) {
            execute_fix("yay -Syu");
        }
    }

    // Orphans
    if (orphans > 0) {
        if (ask_user("Remove orphaned packages?")) {
            execute_fix("yay -Yc"); // yay's clean orphan command, or 'pacman -Rns $(pacman -Qdtq)'
        }
    }

    // Pacnew (Advanced, just list them for now as interactive merge is complex)
    if (pacnews > 0) {
        if (ask_user("List config conflicts details?")) {
            check_pacnew_files(); // Reuse the printing function
            printf("\n%sTip: Use 'pacdiff' to merge these.%s\n", COLOR_YELLOW, COLOR_RESET);
        }
    }

    // Failed Services
    if (failed_svcs > 0) {
        if (ask_user("List failed services?")) {
            check_failed_services(); // Reuse printing function
        }
    }

    // Zombie Lock Fix (Forensics)
    if (access("/var/lib/pacman/db.lck", F_OK) != -1) {
        // Check if running again to be safe
        if (system("pgrep -x pacman >/dev/null 2>&1") != 0) {
            if (ask_user("Remove zombie pacman lock file?")) {
                execute_fix("sudo rm /var/lib/pacman/db.lck");
            }
        }
    }

    printf("\n%sSystem check complete.%s\n", COLOR_GREEN, COLOR_RESET);
    return 0;
}
