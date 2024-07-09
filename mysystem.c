/*
 *  mysystem.c : system 関数のクローン
 */

#include <stdio.h>
#include <stdlib.h>    // exit, system のため
#include <unistd.h>    // fork, execXX のため
#include <sys/wait.h>  // wait のため
#include "mysystem.h"  // インタフェース

// system関数のクローン
int mysystem(char *command) {
  int status = 0;
  int p;

  if(command == NULL){
    return 1;
  }

  if((p = fork()) < 0){
    return -1;
  }

  if(p != 0){
    while(wait(&status) != p){
      ;
    }
  }else{
    execl("/bin/sh","sh","-c",command,NULL);
    perror("/bin/sh");
    exit(127);
  }
  return status;
}

/* 実行例
% make
cc -Wall -std=c99 -o mysysmain mysysmain.c  mysystem.c
% ls -l
total 584
-rw-r--r--  1 yanairyosuke  staff     143  7  4 09:46 Makefile
-rw-r--r--  1 yanairyosuke  staff    2795  7  4 09:46 README.md
-rw-r--r--  1 yanairyosuke  staff  238232  7  4 09:46 README.pdf
-rwxr-xr-x  1 yanairyosuke  staff   33814  7  9 13:00 mysysmain
-rw-r--r--  1 yanairyosuke  staff     925  7  4 09:46 mysysmain.c
-rw-r--r--  1 yanairyosuke  staff     657  7  9 13:00 mysystem.c
-rw-r--r--  1 yanairyosuke  staff      90  7  4 09:46 mysystem.h
% ./mysysmain "ls -l"
mysystem:
total 584
-rw-r--r--  1 yanairyosuke  staff     143  7  4 09:46 Makefile
-rw-r--r--  1 yanairyosuke  staff    2795  7  4 09:46 README.md
-rw-r--r--  1 yanairyosuke  staff  238232  7  4 09:46 README.pdf
-rwxr-xr-x  1 yanairyosuke  staff   33814  7  9 13:00 mysysmain
-rw-r--r--  1 yanairyosuke  staff     925  7  4 09:46 mysysmain.c
-rw-r--r--  1 yanairyosuke  staff     657  7  9 13:00 mysystem.c
-rw-r--r--  1 yanairyosuke  staff      90  7  4 09:46 mysystem.h
retval = 00000000
system:
total 584
-rw-r--r--  1 yanairyosuke  staff     143  7  4 09:46 Makefile
-rw-r--r--  1 yanairyosuke  staff    2795  7  4 09:46 README.md
-rw-r--r--  1 yanairyosuke  staff  238232  7  4 09:46 README.pdf
-rwxr-xr-x  1 yanairyosuke  staff   33814  7  9 13:00 mysysmain
-rw-r--r--  1 yanairyosuke  staff     925  7  4 09:46 mysysmain.c
-rw-r--r--  1 yanairyosuke  staff     657  7  9 13:00 mysystem.c
-rw-r--r--  1 yanairyosuke  staff      90  7  4 09:46 mysystem.h
retval = 00000000
% ./mysysmain    
使い方 : ./mysysmain コマンド文字列
% ./mysysmain "ABCD README.md"
mysystem:
sh: ABCD: command not found
retval = 00007f00
system:
sh: ABCD: command not found
retval = 00007f00

*/
