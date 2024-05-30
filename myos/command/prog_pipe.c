#include "stdio.h"
#include "syscall.h"
#include "string.h"
#include "stdint.h"
#include "assert.h"
int main(int argc, char **argv)
{
    int32_t fd[2] = {-1};
    pipe(fd);
    int32_t pid = fork();
    if (pid)
    {                 // 父进程
        close(fd[0]); // 关闭输入
        write(fd[1], "Hi, my son, I love you!", 24);
        printf("\nI`m father, my pid is %d\n", getpid());
        int32_t status;
        int32_t child_pid = wait(&status); // 此时子进程若没有执行exit,my_shell会被阻塞,不再响应键入的命令
        if (child_pid == -1)
        { // 按理说程序正确的话不会执行到这句,fork出的进程便是shell子进程
            panic("my_shell: no child\n");
        }
        return 8;
    }
    else
    {
        close(fd[1]); // 关闭输出
        char buf[32] = {0};
        read(fd[0], buf, 24);
        printf("\nI`m child, my pid is %d\n", getpid());
        printf("I`m child, my father said to me: \"%s\"\n", buf);
        return 9;
    }
}