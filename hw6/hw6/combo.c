#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//execlp("/usr/bin/sort", "sort", "<", argv[0], NULL); < arg1
//execlp("/bin/grep", "grep", "include", NULL);
//execlp("usr/bin/wc", "wc", NULL); > arg2

main(int argc, char* argv []){
    if(argc != 2){
        fprintf(stderr, "Expected format: ./combo input_file.c output_file");
        exit(-1);
    }
    
    int fd[2];
    pid_t pid;
    pipe(fd); // file descriptors set fd[1] for writing
    pid = fork(); 

    if(pid < 0) {
        fprintf(stderr, "Fork Failed");
        exit(-1);
    }

    if(pid > 0){ // parent process (sort)
        close(fd[0]);
        // direct output to file desrciptor for child
        dup(fd[1]);
        execlp("/usr/bin/sort", "sort", "<", argv[0], NULL);
    }
    else if(pid == 0){ //child process
        close(fd[1]);
        dup(fd[0]);
        execlp("/bin/grep", "grep", "include", NULL);
    }
    return 0;
}