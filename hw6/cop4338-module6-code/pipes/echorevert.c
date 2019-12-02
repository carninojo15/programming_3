#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/wait.h>

#define BUFSIZ 1024

void revert(char* buf)
{
  int i = 0, j = strlen(buf)-1;
  

  while(i < j) { 
    char c = buf[j];
    buf[j--] = buf[i];
    buf[i++] = c;
  }
}

int main()
{
  pid_t pid;
  int p2c[2], c2p[2], n;
  char buf[BUFSIZ];

  if(pipe(p2c) < 0 || pipe(c2p) < 0) {
    perror("pipe failed");
    return 1;
  }
		   
  pid = fork();
  if(pid < 0) { /* an error occurred */
    perror("fork failed");
    exit(-1);
  } else if(pid == 0) { /* child process */
    close(p2c[1]); 
    close(c2p[0]);
    for(;;) {
      n = read(p2c[0], buf, BUFSIZ);
      if(n < 0) exit(-1);
      else if(n == 0) continue;
      revert(buf);
      n = write(c2p[1], buf, strlen(buf)+1);
      if(n < 0) exit(-1);
    }
  } else { /* parent process */
    close(p2c[0]);
    close(c2p[1]);
    while(fgets(buf, BUFSIZ, stdin)) {
      int len = strlen(buf);
      if(len > 0 && buf[len-1] == '\n') buf[--len] = 0; /* remove the newline */
      if(len <= 0) break; /* terminates when empty line is encountered */
      /*printf("%s", buf);*/
      n = write(p2c[1], buf, len+1);
      if(n < 0) exit(-1);
      n = read(c2p[0], buf, BUFSIZ);
      if(n < 0) exit(-1);
      printf("%s\n", buf);
    }
    kill(pid, SIGKILL);
  }
  return 0;
}
