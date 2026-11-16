#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// Test program that checks priority for getprocs() system call
// Runs ps command
int
main(void)
{
  printf("Default priority: %d\n", getpriority());

  if (setpriority(15) < 0) {
    printf("setpriority failed\n");
    exit(1);
  }

  printf("Updated priority: %d\n", getpriority());

  // Running ps here
  int pid = fork();
  if (pid == 0) {
    char *argv[] = { "ps", 0 };
    exec("ps", argv);
    exit(0);
  }
  wait(0);

  exit(0);
}