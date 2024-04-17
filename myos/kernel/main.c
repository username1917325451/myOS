#include "print.h"
#include "init.h"
#include "thread.h"
#include "interrupt.h"
#include "console.h"
#include "process.h"
#include "syscallInit.h"
#include "syscall.h"
#include "stdio.h"
#include "memory.h"

void k_thread_a(void*);
void k_thread_b(void*);
void u_prog_a(void);
void u_prog_b(void);

int main(void) {
   put_str("I am kernel\n");
   init_all();
   process_execute(u_prog_a, "u_prog_a");
   process_execute(u_prog_b, "u_prog_b");
   intr_enable();
   thread_start("k_thread_a", 31, k_thread_a, "I am thread_a");
   thread_start("k_thread_b", 31, k_thread_b, "I am thread_b ");
   while(1);
   return 0;
}

/* 在线程中运行的函数 */
void k_thread_a(void* arg) {     
   char* para = arg;
   void* addr = sys_malloc(33);
   console_put_str(" I am thread_a, sys_malloc(33), addr is 0x");
   console_put_int((int)addr);
   console_put_char('\n');
   while(1);
}

/* 在线程中运行的函数 */
void k_thread_b(void* arg) {     
   char* para = arg;
   void* addr = sys_malloc(63);
   console_put_str(" I am thread_b, sys_malloc(63), addr is 0x");
   console_put_int((int)addr);
   console_put_char('\n');
   while(1);
}

/* 测试用户进程 */
void u_prog_a(void) {
   char* name = "prog_a";
   // printf(" I am %s, my pid:%d%c", name, getpid(),'\n');
   void* addr = malloc(5670);
   printf("%s%x\n",  "I am u_prog_a, malloc(5670), addr is 0x", (uint32_t)addr);
   addr = malloc(1234);
   printf("%s%x\n",  "I am u_prog_a, malloc(1234), addr is 0x", (uint32_t)addr);
   while(1);
}

/* 测试用户进程 */
void u_prog_b(void) {
   char* name = "prog_b";
   printf(" I am %s, my pid:%d%c", name, getpid(), '\n');
   void* addr = malloc(123);
   printf("%s%x\n",  "I am u_prog_b, malloc(123), addr is 0x", (uint32_t)addr);
   addr = malloc(90);
   printf("%s%x\n",  "I am u_prog_b, malloc(90), addr is 0x", (uint32_t)addr);
   while(1);
}

