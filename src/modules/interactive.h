#ifndef INTERACTIVE_H
#define INTERACTIVE_H

// Prompts the user (y/n). Returns 1 for yes, 0 for no.
int ask_user(const char *question);

// Wrapper to run commands interactively (system() instead of popen())
void execute_fix(const char *command);

#endif
