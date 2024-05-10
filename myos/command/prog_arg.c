#include "stdio.h"
#include "syscall.h"
#include "string.h"
#include "stdint.h"
#include "assert.h"
#include "buildin_cmd.h"
int main(int argc, char **argv)
{
    int arg_idx = 0;
    while (arg_idx < argc)
    {
        printf("argv[%d] is %s\n", arg_idx, argv[arg_idx]);
        arg_idx++;
    }
    if(arg_idx < 2)
    {
        printf("prog_arg : the argc is less than two!\n");
        return -1;
    }
    int pid = fork();
    if (pid)
    {
        int delay = 900000;
        while (delay--)
            ;
        printf("\n      I`m father prog, my pid:%d, I will show process list\n", getpid());
        ps();
        int32_t status;
        int32_t child_pid = wait(&status); // 此时子进程若没有执行exit,my_shell会被阻塞,不再响应键入的命令
        if (child_pid == -1)
        { // 按理说程序正确的话不会执行到这句,fork出的进程便是shell子进程
            panic("my_shell: no child\n");
        }
        printf("child_pid %d, it's status: %d\n", child_pid, status);
    }
    else
    {
        char abs_path[512] = {0};
        printf("\n      I`m child prog, my pid:%d, I will exec %s right now\n", getpid(), argv[1]);
        
        if (argv[1][0] != '/')
        {
            getcwd(abs_path, 512);
            if(strcmp(abs_path, "/") != 0)
            {
                strcat(abs_path, "/");
            }
            strcat(abs_path, argv[1]);
        }
        else
        {
            strcpy(abs_path, argv[1]);
        }
        // printf("this abs_path : %s\n", abs_path);
        execv(abs_path, ++argv);
    }
    // while (1)
    //     ;
    return 0;
}

