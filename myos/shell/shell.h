#ifndef __KERNEL_SHELL_H
#define __KERNEL_SHELL_H
#include "fs.h"
void print_prompt(void);
void my_shell(void);
void cmd_execute(uint32_t argc, char **argv);

extern char final_path[MAX_PATH_LEN];

#endif

