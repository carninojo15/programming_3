#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char** argv []){
    if(argc != 3){
        fprintf(stderr, "Expected format: ./combo input_file.c output_file");
        exit(-1);
    }

    int fd0[2], fd1[2];
    pid_t pid0;
    int in, out; // to set pipes and file
    // fd0[0] = read by grep
    // fd0[1] = written by sort
    // fd1[0] = read by wc
    // fd1[1] = written by grep

    char* arg0 = (char*)argv[1];
    char* arg1 = (char*)argv[2];

    if (pipe(fd0)<0 || pipe(fd1)<0) { 
        perror("Pipe Failed" ); 
        exit(-1); 
    } 

    pid0 = fork();
    if (pid0 == -1){
        perror("fork failure\n");
        exit(-1);
    }
    else if (pid0 > 0){
        pid_t pid1;
        pid1 = fork();
        if (pid1 == -1){
            perror("fork failure\n");
            exit(-1);
        }
        else if (pid1 > 0){ // parent, wc
            out = open(arg1, O_RDWR|O_CREAT|O_APPEND, 0777);
            dup2(fd1[0], STDIN_FILENO);
            dup2(out, STDOUT_FILENO);
            close(fd0[0]);
            close(fd0[1]);
            close(fd1[0]);
            close(fd1[1]);
            close(out);
            execlp("wc", "wc", NULL);
            
        }
        else{ // child 1, grep
            dup2(fd0[0], STDIN_FILENO);
            dup2(fd1[1], STDOUT_FILENO);
            close(fd0[0]);
            close(fd0[1]);
            close(fd1[0]);
            close(fd1[1]);
            execlp("grep", "grep", "include", NULL);
        }
    }
    else{ // child0, sort
        in = open(arg0, O_RDONLY);
        dup2(in, STDIN_FILENO);
        dup2(fd0[1], STDOUT_FILENO);
        close(fd0[0]);
        close(fd0[1]);
        close(fd1[0]);
        close(fd1[1]);
        close(in);
        execlp("sort", "sort", NULL);
    }
}

