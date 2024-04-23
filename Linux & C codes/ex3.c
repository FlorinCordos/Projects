
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>

#define BUFFER_SIZE 10

int main() {
  //creez pipe-ul
  int pipefd[3];
  if (pipe(pipefd) < 0) {
    perror("Pipe-ul nu a putut fi creat");
    exit(EXIT_FAILURE);
  }

  pid_t pid1, pid2,pid3;
  //copil 1
  pid1 = fork();
  if (pid1 == 0) {
    printf("PID copil 1: %d nu face nimic\n", getpid());
    exit(EXIT_FAILURE);
  }

  pid2=fork();
  //copil 2
  if(pid2==0)
  {
    printf("PID copil 2: %d\n",getpid());
    //scriu in canalul 1
    write(pipefd[1], "ping", 4);
    exit(EXIT_FAILURE);
  }
  //Copil 3
  pid3 = fork();
  if (pid3 == 0) {
    printf("PID copil 3: %d\n", getpid());

    char buf[4];
    //citesc din canalul 1
    read(pipefd[1], buf, 4);
    printf("Primit mesajul ping: %s\n", buf);
    //scriu in canalul 2 ce am citit din canalul 1
    write(pipefd[2], "pong", 4);
    char mesaj= read(pipefd[2], buf, 4);
    printf("%s",mesaj);
    exit(EXIT_FAILURE);
  }

  int status;
  waitpid(pid2, &status, 0);
  waitpid(pid3, &status, 0);

  close(pipefd[2]);
  close(pipefd[3]);

  return 0;
}

