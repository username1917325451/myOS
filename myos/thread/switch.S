[bits 32]
section .text
global switch_to
switch_to:
   ;栈中此处是返回地址
   push esi                      	;这4条就是对应压入线程栈中预留的ABI标准要求保存的，esp会保存在其他地方
   push edi
   push ebx
   push ebp

   mov eax, [esp + 20]		      	; 把cur地址保存到eax寄存器
   mov [eax], esp                	; 将self_kstack赋值成esp栈顶指针的值
				 					; self_kstack在task_struct中的偏移为0,
				 					; 所以直接往thread开头处存4字节便可。
									;------------------  以上是备份当前线程的环境，下面是恢复下一个线程的环境  ----------------
   mov eax, [esp + 24]		; 得到栈中的参数next, next = [esp+24]
   mov esp, [eax]		 		; esp赋值为next的self_kstack, pcb的第一个成员是self_kstack成员,用来记录0级栈顶指针
				 					; 用来上cpu时恢复0级栈,0级栈中保存了进程或线程所有信息,包括3级栈指针
   pop ebp
   pop ebx
   pop edi
   pop esi
                           ; 如果next时第一次执行, esp会指向eip
   ret				 			; 返回到上面的switch_to下面的那句注释的返回地址,
				 					; 未由中断进入,第一次执行时会返回到kernel_thread