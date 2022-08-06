/* Написание, компиляция и запуск программы с системными вызовами getpid() и getppid() */
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main()
{
   pid_t pid, ppid;
   
   pid = getpid();
   ppid = getppid();

   printf("PID: %d\n", pid);
   printf("PPID: %d\n", ppid);

   fprintf(stderr, "Press <Enter> to exit...");

   getchar();
   return 0;
}