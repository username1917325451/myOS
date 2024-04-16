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
#include "debug.h"

void k_thread_a(void*);
void k_thread_b(void*);
void u_prog_a(void);
void u_prog_b(void);

int main(void) {
   put_str("I am kernel\n");
   init_all();

   void *p = get_a_page(PF_KERNEL, 0x8048000);
   int *a = p;
   *a = 3;

   process_execute(u_prog_a, "user_prog_a");
   process_execute(u_prog_b, "user_prog_b");

   intr_enable();
   console_put_str(" main_pid:0x");
   console_put_int(sys_getpid());
   console_put_char('\n');
   thread_start("k_thread_a", 31, k_thread_a, "argA ");
   thread_start("k_thread_b", 31, k_thread_b, "argB ");

   while(1){
      int i = 0;
      while(i < 10000000){
         if(i % 500000 == 0){
            console_put_str("the value for main is a : ");
            console_put_int(*a);
            console_put_str("\n");
         }
         i ++;
      }
   }
   return 0;
}

/* 在线程中运行的函数 */
void k_thread_a(void* arg) {     
   char* para = arg;
   console_put_str(" I am thread_a, my pid:0x");
   console_put_int(sys_getpid());
   console_put_char('\n');
   while(1);
}

/* 在线程中运行的函数 */
void k_thread_b(void* arg) {     
   char* para = arg;
   console_put_str(" I am thread_b, my pid:0x");
   console_put_int(sys_getpid());
   console_put_char('\n');
   while(1);
}

/* 测试用户进程 */
void u_prog_a(void) {
   char* name = "prog_a";
   printf(" I am %s, my pid:%d%c", name, getpid(),'\n');
   void *p = 0x8048000;
   // void *p = get_user_pages(1);
   int *a = p;
   *a = 1;
   // printf("the vaddr for a is : %x\n", p);
   // put_str("prog_a use putstr\n");
   // console_put_str("prog_a use putstr\n");
   while(1){
      int i = 0;
      while(i < 10000000){
         if(i % 500000 == 0){
            printf("the value for a is : %d\n", *a);
         }
         i ++;
      }
   }
   while(1);
}

/* 测试用户进程 */
void u_prog_b(void) {
   char* name = "prog_b";
   printf(" I am %s, my pid:%d%c", name, getpid(), '\n');
   // void *p = get_user_pages(1);
   void *p = 0x8048000;
   int *a = p;
   *a = 2;
   // printf("the vaddr for b is : %x\n", p);
   // put_str("prog_a use putstr\n");
   // console_put_str("prog_a use putstr\n");
   while(1){
      int i = 0;
      while(i < 10000000){
         if(i % 500000 == 0){
            printf("the value for b is : %d\n", *a);
         }
         i ++;
      }
   }
   while(1);
}