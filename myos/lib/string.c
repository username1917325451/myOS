#include "string.h"
#include "debug.h"
#include "global.h"

// 将从地址dst_开始的size个字节的值设置为value
void memset(void* dst_, uint8_t value, uint32_t size){
    uint8_t* dst = (uint8_t*)dst_;
    ASSERT(dst != NULL);
    while(size--){
        *dst = value;
        dst ++;
    }
}
// 将从地址src_开始的size个字节复制到dst_开始的size长度的空间中去
void memcpy(void* dst_, const void* src_, uint32_t size){
    uint8_t* dst = (uint8_t*)dst_;
    const uint8_t* src = (const uint8_t*)src_;
    ASSERT(dst != NULL && src != NULL);
    while(size--){
        *dst = *src;
        dst ++,src ++;
    }
}
//
int memcmp(const void* a_, const void* b_, uint32_t size){
    const uint8_t* a = (const uint8_t*)a_;
    const uint8_t* b = (const uint8_t*)b_;
    ASSERT(a != NULL && b != NULL);
    while(size--){
        if(*a != *b)
            return (*a > *b ? 1 : -1);
        a ++,b ++;
    }
    return 0;
}
// 将字符串从src拷贝到dst,并返回目的字符串的起始地址
char* strcpy(char* dst_, const char* src_){
    char* dst = dst_;
    ASSERT(dst_ != NULL && src_ != NULL);
    while(*src_ != '\0'){
        *dst_ = *src_;
        dst_ ++,src_ ++;
    }
    *dst_ = '\0';
    return dst;
}

uint32_t strlen(const char* str){
    ASSERT(str != NULL);
    uint32_t len = 0;
    while(*str != '\0'){
        len ++;
        str ++;
    }
    return len;
}

int8_t strcmp (const char *a, const char *b){
    ASSERT(a != NULL && b != NULL);
    while(*a != '\0' && *a == *b)
        a ++,b ++;
    return (*a == *b ? 0 : (*a > *b ? 1 : -1));
}
// 从左到右查找字符串str中首次出现字符ch的地址(不是下标,是地址)
char* strchr(const char* str, const uint8_t ch){
    ASSERT(str != NULL);
    while(*str != '\0' && *str != ch)
        str ++;
    return (*str == ch ? (char*)str : NULL);
}
// 从后往前查找字符串str中首次出现字符ch的地址(不是下标,是地址)
char* strrchr(const char* str, const uint8_t ch){
    ASSERT(str != NULL);
    char* res = NULL;
    while(*str != '\0'){
        if(*str == ch)
            res = (char*)str;
        str ++;
    }
    return res;
}
// 将字符串src_拼接到dst_后,将回拼接的串地址
char* strcat(char* dst_, const char* src_){
    ASSERT(dst_ != NULL && src_ != NULL);
    char *dst = (dst_ + strlen(dst_));
    while(*dst ++ = *src_ ++);
    return dst_;
}
// 在str中查找ch出现的次数
uint32_t strchrs(const char* str, uint8_t ch){
    ASSERT(str != NULL);
    uint32_t cnt = 0;
    while(*str != '\0'){
        cnt += (*str == ch);
        str ++;
    }
    return cnt;
}