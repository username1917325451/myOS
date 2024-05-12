#include "print.h"
#include "init.h"
#include "fork.h"
#include "stdio.h"
#include "syscall.h"
#include "assert.h"
#include "shell.h"
#include "console.h"
#include "ide.h"
#include "stdioKernel.h"

void init(void);

int main(void)
{
    put_str("I am kernel\n");
    init_all();

    // uint32_t file_size = 10496;
    // uint32_t sec_cnt = DIV_ROUND_UP(file_size, 512);
    // struct disk *sda = &channels[0].devices[0];
    // void *prog_buf = sys_malloc(file_size);
    // ide_read(sda, 300, prog_buf, sec_cnt);
    // int32_t fd = sys_open("/prog_no_arg", O_CREAT | O_RDWR);
    // if (fd != -1)
    // {
    //     if (sys_write(fd, prog_buf, file_size) == -1)
    //     {
    //         printk("file write error!\n");
    //         while (1);
    //     }
    // }
    // void *buf = sys_malloc(550);
    // strcat(buf, "4399");
    // sys_write(fd, buf, 5);
    // sys_close(fd);

    cls_screen();
    // printk("buf:\n%s", buf);
    // uint32_t a = 0, b = 3, c = -3, d = 2;
    // printf("the max is : %d\n", std_max(4, a, b, c, d));
    // printf("the min is : %d\n", std_min(4, a, b, c, d));
    // printf("the abs of -3, 0 and 3 is : %d %d %d\n", std_abs(&c), std_abs(&a), std_abs(&b));
    console_put_str("[rabbit@localhost /]$ ");
    thread_exit(running_thread(), true);
    return 0;
}

/* init进程 */
void init(void)
{
    uint32_t ret_pid = fork();
    if (ret_pid)
    { // 父进程
        int status;
        int child_pid;
        /* init在此处不停的回收僵尸进程 */
        while (1)
        {
            child_pid = wait(&status);
            printf("I`m init, My pid is 1, I recieve a child, It`s pid is %d, status is %d\n", child_pid, status);
        }
    }
    else
    { // 子进程
        my_shell();
    }
    panic("init: should not be here");
}

