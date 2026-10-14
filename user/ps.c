#include "kernel/param.h"
#include "kernel/types.h"
#include "kernel/pstat.h"
#include "user/user.h"

int
main(int argc, char **argv)
{
  struct pstat uproc[NPROC];
  int nprocs;
  int i;
  char *state;
  static char *states[] = {
    [SLEEPING]  "sleeping",
    [RUNNABLE]  "runnable",
    [RUNNING]   "running ",
    [ZOMBIE]    "zombie  "
  };

  nprocs = getprocs(uproc);
  if (nprocs < 0)
    exit(-1);

  int curtime = uptime();

  printf("pid\tstate\t\tsize\tppid\tpri\tage\tname\n");
  for (i=0; i<nprocs; i++) {
    state = states[uproc[i].state];

    // calculate age whne process is RUNNABLE (task 3)
    int age = 0;
    if (uproc[i].state == RUNNABLE) {
      age = curtime - uproc[i].readytime;
    }

    printf("%d\t%s\t%ld\t%d\t%d\t%d\t%s\n", uproc[i].pid, state,
                   uproc[i].size, uproc[i].ppid, uproc[i].priority, age, uproc[i].name);
  }

  exit(0);
}

