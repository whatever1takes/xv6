#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main(int argc, char *argv[]) {
  int parent_to_child[2];
  int child_to_parent[2];
  if (pipe(parent_to_child) < 0 || pipe(child_to_parent) < 0) {
    printf("pipe() failed\n");
    exit(1);
  }

  int pid = fork(); // child pid==0 | par pid!=0

  if (!pid) { // child
    char buf;
    close(parent_to_child[1]);
    close(child_to_parent[0]); // release unused
    if (read(parent_to_child[0], &buf, 1) != 1) {
      printf("child read failed\n");
      exit(1);
    }
    printf("%d: received ping\n", pid);
    if (write(child_to_parent[1], &buf, 1) != 1) {
      printf("child write failed\n");
      exit(1);
    }
    close(parent_to_child[0]);
    close(child_to_parent[1]); // release all before exit
    exit(0);
  } else {
    char buf = 'Y';
    close(child_to_parent[1]);
    close(parent_to_child[0]);

    if (write(parent_to_child[1], &buf, 1) != 1) {
      printf("parent write failed\n");
      exit(1);
    }
    if (read(child_to_parent[0], &buf, 1) != 1) {
      printf("parent read failed\n");
      exit(1);
    }
    printf("%d: received pong\n", pid);

    close(parent_to_child[1]);
    close(child_to_parent[0]); // release all before exit
    exit(0);
  }
}
