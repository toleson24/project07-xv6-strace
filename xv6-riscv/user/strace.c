#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
  int pid;

  if(argc < 0) {
    printf("Usage: strace command [args] ...\n");
    exit(1);
  }

  pid = fork();
  if (pid < 0) {
    printf("strace fork failed\n");
    exit(1);
  }

  if(pid == 0) {
    // Child process
    strace(1);
    exec(argv[1], &argv[1]);
    printf("strace exec %s failed\n", argv[1]);
    exit(1);
  }

  // Parent process
  wait(0);
  
  exit(0);
}
