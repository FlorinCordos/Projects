#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void handler(int signum) {
  printf("Am primit semnalul SIGUSR1!\n");
}

int main() {

  pid_t pid = fork();
  if (pid == 0) {
    signal(SIGUSR1, handler);

    while (1) {
      pause();
    }
  }

  kill(pid, SIGUSR1);

  waitpid(pid, NULL, 0);

  return 0;
}

