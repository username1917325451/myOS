#ifndef __KERNEL_INTERRUPT_H
#define __KERNEL_INTERRUPT_H
#include "stdint.h"
typedef void* intr_handler;		//将intr_handler定义为void*同类型
void idt_init(void);            //完成有关中断的所有初始化工作

/* 定义中断的两种状态 */
enum intr_status {		 // 中断状态
    INTR_OFF,			 // 0: 中断关闭
    INTR_ON		         // 1: 中断打开
};

enum intr_status intr_get_status(void);
enum intr_status intr_set_status (enum intr_status);
enum intr_status intr_enable (void);
enum intr_status intr_disable (void);

#endif