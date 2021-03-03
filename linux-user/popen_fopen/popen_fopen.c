#include "stdio.h"
#include "string.h"

int main(int args, char *argv[]) {
  if (args > 1) {
    printf("Usage: %s command\n", argv[0]);
  }
  printf("%s\n", argv[1]);

  FILE *fifo;    // shell管道
  char buf[10240]; //获取的shell输出存储buf

  memset(buf, '\0', sizeof(buf));

  fifo = popen(argv[1], "r"); // ‘ r ’ 读取管道内容
  if (fifo == NULL) {
    printf("Can't connect to shell\n");
    return -1;
  }

  fread(buf, sizeof(char), sizeof(buf), fifo);

  if (strstr(buf, "popen_fopen.c")) {
    printf("file is exist!\n");
  }

  printf("%s", buf);

  pclose(fifo);               //关闭管道通讯

  return 0;
}
