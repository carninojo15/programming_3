#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZ 1024

int main()
{
  pid_t pid;
  int fd[2], n;
  char str[] = "hello world!\n";
  char buf[BUFSIZ];

  if(pipe(fd) < 0) {
    perror("pipe failed");
    return 1;
  }
		   
  pid = fork();
  if(pid < 0) { /* an error occurred */
    perror("fork failed");
    exit(-1);
  } else if(pid == 0) { /* child process */
    close(fd[0]);
    write(fd[1], str, sizeof(str));
  } else { /* parent process */
    close(fd[1]);
    n = read(fd[0], buf, BUFSIZ);
    printf("%s", buf); /* write to standard out */
  }

  return 0;
}
