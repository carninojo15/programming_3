#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void usage(char* name) {
  fprintf(stderr, "Usage: %s filename\n", name);
}

int main(int argc, char* argv[])
{
  pid_t pid;
  int fd, pp[2];
  char buf[BUFSIZ];
  int n;
 
  if(argc != 2) { usage(argv[0]); exit(0); }

  fd = open(argv[1], O_RDONLY);
  if(fd < 0) { perror("open failed"); exit(-1); }

  if(pipe(pp) < 0) { perror("pipe failed"); exit(-1); }

  pid = fork();
  if(pid < 0) { perror("fork failed"); exit(-1); }
  else if(pid > 0) {
    close(fd);
    close(pp[1]);
    while((n = read(pp[0], buf, BUFSIZ)) > 0) {
      buf[n] = 0;
      printf("%s", buf);
    }
    close(pp[0]);
  } else {
    dup2(fd, STDIN_FILENO);
    dup2(pp[1], STDOUT_FILENO);
    close(fd);
    close(pp[0]);
    close(pp[1]);
    execlp("sort", "sort", NULL);
    perror("exec failed");
    exit(-1);
  }

  return 0;
}
