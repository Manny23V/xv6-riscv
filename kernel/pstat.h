#ifndef _PSTAT_H_
#define _PSTAT_H_

#include "types.h"

// from proc.h; for the getprocs() system call to get all valid values
#ifndef _PROCSTATE_
#define _PROCSTATE_
enum procstate { UNUSED, USED, SLEEPING, RUNNABLE, RUNNING, ZOMBIE };
#endif

struct rusage {
  uint cputime;
};

struct pstat {
  int pid; // Process ID
  enum procstate state; // Process state
  uint64 size; // Size of process memory (bytes)
  int ppid; // Parent process ID
  char name[16]; // Parent command name
  int priority; // Process scheduling priority (Task 2)
  int readytime; // time for when process becomes RUNNABLE (Task 3)
};

#endif

