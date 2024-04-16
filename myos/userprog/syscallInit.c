#include "syscallInit.h"
#include "syscall.h"
#include "stdint.h"
#include "print.h"
#include "thread.h"
#include "console.h"
#include "string.h"
#include "memory.h"

/* 返回当前任务的pid */
uint32_t sys_getpid(void) {
   return running_thread()->pid;
}

/* 打印字符串str(未实现文件系统前的版本) */
uint32_t sys_write(char* str) {
   console_put_str(running_thread()->name);
   console_put_str(" : ");
   console_put_str(str);
   // 测试每个用户进程申请到的第一块虚拟内存的位置
   if(running_thread()->pgdir != NULL){
      void *p = get_user_pages(1);
      console_put_str(running_thread()->name);
      console_put_str(" : ");
      console_put_int(p);
      console_put_char('\n');
   }
   return strlen(str);
}

/* 初始化系统调用 */
void syscall_init(void) {
   put_str("syscall_init start\n");
   syscall_table[SYS_GETPID] = sys_getpid;
   syscall_table[SYS_WRITE] = sys_write;
   put_str("syscall_init done\n");
}