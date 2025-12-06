#ifndef UTILS_H
#define UTILS_H

#define COLOR_RED     "\x1b[31m"
#define COLOR_GREEN   "\x1b[32m"
#define COLOR_YELLOW  "\x1b[33m"
#define COLOR_BLUE    "\x1b[34m"
#define COLOR_CYAN    "\x1b[36m"
#define COLOR_RESET   "\x1b[0m"
#define COLOR_BOLD    "\x1b[1m"

void print_header(const char *title);
void print_error(const char *msg);
int run_and_print(const char *cmd, const char *empty_msg, const char *line_prefix);

#endif
