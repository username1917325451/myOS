#include "print.h"
#include "init.h"
#include "fs.h"
#include "stdio.h"
#include "dir.h"

int main(void)
{
   put_str("I am kernel\n");
   init_all();
   /********  测试代码  ********/
   printf("the file in /dir1/ is:\n");
   struct dir *dir = sys_opendir("/dir1/");
   char *type = NULL;
   struct dir_entry *dir_e = NULL;
   while ((dir_e = sys_readdir(dir)))
   {
      if (dir_e->f_type == FT_REGULAR)
      {
         type = "regular";
      }
      else
      {
         type = "directory";
      }
      printf("      %s   %s\n", type, dir_e->filename);
   }

   struct stat obj_stat;
   sys_stat("/", &obj_stat);
   printf("/`s info\n   i_no:%d\n   size:%d\n   filetype:%s\n",
         obj_stat.st_ino, obj_stat.st_size,
         obj_stat.st_filetype == 2 ? "directory" : "regular");
   sys_stat("/dir1", &obj_stat);
   printf("/dir1`s info\n   i_no:%d\n   size:%d\n   filetype:%s\n",
         obj_stat.st_ino, obj_stat.st_size,
         obj_stat.st_filetype == 2 ? "directory" : "regular");
   
   sys_stat("/dir1/file1", &obj_stat);
   printf("/dir1/file1`s info\n   i_no:%d\n   size:%d\n   filetype:%s\n",
         obj_stat.st_ino, obj_stat.st_size,
         obj_stat.st_filetype == 2 ? "directory" : "regular");
    /********  测试代码  ********/
    while (1)
        ;
    return 0;
}
