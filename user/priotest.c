#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

// test program for task 4, that test on priority-based scheduler
void
work(int n)
{
  volatile int sum = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < 500000; j++) {
      sum += j;
    }
  }
}

int
main(int argc, char *argv[])
{
  int sync_pipe[2];
  pipe(sync_pipe);

  int pid1 = fork();
  if (pid1 == 0) {
    setpriority(10);
    close(sync_pipe[1]);
    char buf;
    read(sync_pipe[0], &buf, 1);
    close(sync_pipe[0]);

    printf("Child 1 (LOW 10) started\n");
    work(200);
    printf("Child 1 (LOW 10) done\n");
    exit(0);
  }

  int pid2 = fork();
  if (pid2 == 0) {
    setpriority(40);
    close(sync_pipe[1]);
    char buf;
    read(sync_pipe[0], &buf, 1);
    close(sync_pipe[0]);

    printf("Child 2 (HIGH 40) started\n");
    work(200);
    printf("Child 2 (HIGH 40) done\n");
    exit(0);
  }

  close(sync_pipe[0]);
  
  for (volatile int i = 0; i < 1000000; i++);

  close(sync_pipe[1]);

  wait(0);
  wait(0);
  exit(0);
}