#include "kernel/stat.h"
#include "kernel/types.h"
#include "user/user.h"

int main(int argc, char *argv[]) {
  int fds[2];
  if (pipe(fds) != 0) {
    printf(" pipe() failed\n");
    exit(1);
  }

  int pid = fork(); // child pid==0 | par pid!=0
  char buf[1] = "Y";
  if (!pid) {
    // close(fds[0]);
    // printf("child: %d\n", pid);
    int readok = read(fds[0], buf, 1);
    if (!readok) {
      exit(1);
    }
    printf("%d: received ping\n", pid);
    int isok = write(fds[1], buf, 1);
    if (!isok) {
      printf("child write failed\n");
      exit(1);
    }

    exit(0);
  } else {
    // printf("parent: %d\n", pid);
    int writeok = write(fds[1], buf, 1);
    if (!writeok) {
      exit(1);
    }
    // close(fds[1]);
    int isok = read(fds[0], buf, 1);
    if (!isok) {
      printf("parent read failed\n");
      exit(1);
    }
    printf("%d: received pong\n", pid);
    exit(0);
  }

  exit(0);
}
