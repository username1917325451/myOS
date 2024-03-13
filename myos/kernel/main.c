#include "print.h"
#include "init.h"
#include "debug.h"
#include "string.h"
int main(void) {
   put_str("I am kernel\n");
   // init_all();
   char* a = "aaaaaaa";
   char* b = "bbbbbbb";
   char* ab = "aaab";
   put_str("length of a: ");
   put_int(strlen(a));
   put_char('\n');
   put_str("cmp a and b: ");
   put_int(strcmp(a, b));
   put_char('\n');
   put_str("strcat a and b :");
   put_str(strcat(a, b));
   put_char('\n');
   put_str("length of a: ");
   put_int(strlen(a));
   put_char('\n');
   put_str("the count of 'a' in ab: ");
   put_int(strchrs(ab, 'a'));
   put_char('\n');
   put_str("strcpy ab to a, then print a: ");
   put_str(strcpy(a, ab));
   put_char('\n');
   put_str("init a: ");
   memset(a, 0, strlen(a));
   put_str(a);
   put_char('\n');
   return 0;
}