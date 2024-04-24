#!/bin/bash

# 清除二进制文件
make clean

# 进入本地代码目录
cd /home/shenhaomin/work

# 添加所有修改的文件到暂存区
git add .

# 提交修改，并输入提交信息
echo "请输入提交信息："
read commit_message
git commit -m "$commit_message"

# 推送到远程仓库
git push origin master

echo "代码已成功推送到远程仓库！"