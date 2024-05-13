#include "syscall.h"
#include "stdio.h"
#include "string.h"
#include "fs.h"

// 读取文件 不支持 输出重定向
int main(int argc, char **argv)
{
    if (argc > 2)
    {
        printf("cat: only support atmost 1 argument.\neg: cat filename\n");
        exit(-2);
    }
    if (argc == 1)
    {
        char buf[512] = {0};
        // 从管道读取数据
        int sz = 0;
        sz = read(0, buf, 512);
        write(1, buf, sz);
        exit(0);
    }
    int buf_size = 1024;
    char abs_path[512] = {0};
    void *buf = malloc(buf_size);
    if (buf == NULL)
    {
        printf("cat: malloc memory failed\n");
        return -1;
    }
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
    int fd = open(abs_path, O_RDONLY);
    if (fd == -1)
    {
        // 文件不存在就创建文件
        fd = open(abs_path, O_CREAT | O_RDONLY);
        return 0;
        if(fd == -1)
        {
            printf("cat: open: open %s failed\n", argv[1]);
            return -1;
        }
    }
    // printf("cat the file : %s\n", abs_path);
    int read_bytes = 0;
    while (1)
    {
        read_bytes = read(fd, buf, buf_size);
        // printf("cat : read %dbytes from file  %s\n", read_bytes, buf);
        if (read_bytes == -1)
        {
            break;
        }
        write(1, buf, read_bytes);
        // printf("cat : write %dbytes\n", cn);
    }
    free(buf);
    close(fd);
    return 66;
}
