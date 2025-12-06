#include <stdio.h>
#include "utils.h"

// Returns 0-100
int calculate_score(int updates, int orphans, int failed_services, int pacnew_count) {
    int score = 100;
    
    // Deductions
    score -= (updates * 2);        // -2 per pending update
    score -= (orphans * 5);        // -5 per orphan
    score -= (failed_services * 15); // -15 per failed service
    score -= (pacnew_count * 10);  // -10 per config conflict
    
    if (score < 0) score = 0;
    return score;
}

void print_score_card(int score) {
    const char *color = COLOR_GREEN;
    char grade = 'A';

    if (score < 90) { color = COLOR_GREEN; grade = 'A'; } // A-
    if (score < 80) { color = COLOR_YELLOW; grade = 'B'; }
    if (score < 60) { color = COLOR_YELLOW; grade = 'C'; }
    if (score < 40) { color = COLOR_RED; grade = 'D'; }
    if (score < 20) { color = COLOR_RED; grade = 'F'; }

    printf("\n%s========================================%s\n", COLOR_BOLD, COLOR_RESET);
    printf("  System Health Score: %s%d%% (Grade: %c)%s\n", color, score, grade, COLOR_RESET);
    printf("%s========================================%s\n", COLOR_BOLD, COLOR_RESET);
}
