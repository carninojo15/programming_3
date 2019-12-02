#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

//execlp("/usr/bin/sort", "sort", "<", argv[0], NULL); 
//execlp("/bin/grep", "grep", "include", NULL);
//execlp("usr/bin/wc", "wc", ">", argv[1], NULL); 

int fd1[2], fd2[2];
pid_t pid;

void cmd0(char* input_file){
    printf("doing cmd0\n");
    close(fd1[0]); // close unused pipe
    dup2(fd1[1], 1);
    close(fd1[1]);
    execlp("/usr/bin/sort", "sort <", input_file, NULL);
    fprintf(stderr, "Sort not executed properly\n");
    exit(-1);
}

void cmd1(){
    printf("doing cmd1\n");
    close(fd1[1]);
    close(fd2[0]);
    dup2(fd1[0], 0);
    dup2(fd2[1], 1);
    close(fd1[0]);
    close(fd2[1]);
    execlp("/bin/grep", "grep", "include", NULL);
    fprintf(stderr, "grep not executed properly\n");
    exit(-1);
}

void cmd2(char* output_file){
    printf("doing cmd2\n");
    close(fd2[1]);
    dup2(fd2[0], 0);
    close(fd2[0]);
    execlp("usr/bin/wc", "wc >", output_file, NULL); 
    fprintf(stderr, "wc not executed properly\n");
    exit(-1);
}

int main(int argc, char** argv []){
    if(argc != 3){
        fprintf(stderr, "Expected format: ./combo input_file.c output_file");
        exit(-1);
    }

    pipe(fd1); // file descriptors set fd[1] for writing
    pipe(fd2);
    pid = fork(); 
    char *ch0 = argv[0];
    char *ch1 = argv[1];

    if ((pid = fork()) == -1) {
        perror("bad fork1");
        exit(1);
    } 
    else if (pid == 0)
        cmd0(ch0); // stdin -> sort ->  fd1

    if ((pid = fork()) == -1) {
        perror("bad fork2");
        exit(1);
    } 
    else if (pid == 0) 
        cmd1(); // fd1 -> grep -> fd2

    close(fd1[0]);
    close(fd1[1]);

    if ((pid = fork()) == -1) {
        perror("bad fork3");
        exit(1);
    }  
    else if (pid == 0) 
        cmd2(ch1); // fd2 -> wc -> stdout (the output file)
    return 0;
}

