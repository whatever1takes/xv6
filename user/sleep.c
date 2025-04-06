//
// Created by 周文浩 on 25-4-6.
//
#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
//  if (argc != 2) {
//    printf("Error. Enter for example: sleep 2\n");
//    exit(-1);
//  }
  int sleep_time = atoi(argv[1]);
  if (sleep_time < 0) {
    printf("Invalid sleep time\n");
    exit(-1);
  }
  sleep(sleep_time);
  exit(0);
}