#include "bitmap.h"     //不仅是为了通过一致性检查，位图的数据结构struct bitmap也在这里面
#include "stdint.h"     
#include "string.h"     //里面包含了内存初始化函数，memset
#include "print.h"
#include "interrupt.h"
#include "debug.h"      //ASSERT

/* 将位图btmp初始化 */
void bitmap_init(struct bitmap* btmp) {
    memset(btmp->bits, 0, btmp->btmp_bytes_len);   
}

//用来确定位图的某一位是1，还是0。若是1，返回真（返回的值不一定是1）。否则，返回0。传入两个参数，指向位图的指针，与要判断的位的偏移
bool bitmap_scan_test(struct bitmap* btmp, uint32_t bit_idx) {
    ASSERT(btmp != NULL);
    uint32_t byte_idx = bit_idx / 8;    //确定要判断的位所在字节的偏移
    uint32_t bit_odd  = bit_idx % 8;    //确定要判断的位在某个字节中的偏移
    return ((btmp->bits[byte_idx] & (BITMAP_MASK << bit_odd)) ? 1 : 0);
}

//用来在位图中找到cnt个连续的0，以此来分配一块连续未被占用的内存，参数有指向位图的指针与要分配的内存块的个数cnt
//成功就返回起始位的偏移，不成功就返回-1
int bitmap_scan(struct bitmap* bitmap, uint32_t cnt){
    ASSERT(bitmap != NULL);
    int the_cnt = 0;
    int i = 0;

    while(i / 8 < bitmap->btmp_bytes_len){
        if(!bitmap_scan_test(bitmap, i)){
            // 找到未进行分配的位置
            the_cnt = 0;
            while(i / 8 < bitmap->btmp_bytes_len && the_cnt < cnt && !bitmap_scan_test(bitmap, i)){
                the_cnt ++;
                i++;
            }
            if(the_cnt >= cnt)
                return i - cnt;
        }
        i ++;
    }
    return (cnt ? -1 : 0);
}

//将位图某一位设定为1或0，传入参数是指向位图的指针与这一位的偏移，与想要的值
void bitmap_set(struct bitmap* btmp, uint32_t bit_idx, int8_t value) {
    ASSERT(value == 1 || value == 0);
    int byte_idx = bit_idx / 8;
    int bit_odd = bit_idx % 8;
    // 将这一位置为0
    btmp->bits[byte_idx] &= (~(BITMAP_MASK << bit_odd));
    btmp->bits[byte_idx] |= (value << bit_odd);
}
