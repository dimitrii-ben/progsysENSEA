#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <time.h>

#define WELCOME_MSG "Welcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'.\n"
#define SHELL_NAME "enseash %%"
#define SHELL_NAME2 "enseash [exit:%d|%dms] %%"
#define EXIT "exit\n"
#define INPUT_SIZE 128
#define CLOCK_MONOTONIC 1
#define ROOT_PATH "/usr/bin/"
int displayNewLine(int exit_status){
    return write(STDOUT_FILENO, SHELL_NAME, strlen(SHELL_NAME));  
}

int getExecutionTime(struct timespec spec_before,struct timespec spec_after){
    return (int)((spec_after.tv_sec) * 1000 + (spec_after.tv_nsec)/1000000)-((spec_before.tv_sec) * 1000 + (spec_before.tv_nsec)/10000000);
}
void resetBuffer(char*buffer){
    for(int i = 0;i<INPUT_SIZE;i++){
            buffer[i]=0;
        }
}
int initENSEASH() {
    /*
    Init the display of the tiny shell
    Args: 
     - welcome_msg (char*): Message to display at the start of the shell 
     - shell_name (char*): Define the shell name before command line
    Example:
    welcome_msg
    shell_name % command line
    */
    if (write(STDOUT_FILENO, WELCOME_MSG, strlen(WELCOME_MSG)) == -1 || 
        write(STDOUT_FILENO, SHELL_NAME, strlen(SHELL_NAME)) == -1) {
        perror("Error writing to file");
        return -1;
    } 
    
    return 0;
}
char** getArguments(char* raw_command,char* delimiter){
    char* copy = malloc(strlen(raw_command));
    strcpy(copy,raw_command);
    char* token = strtok(copy,delimiter);
    int token_count = 0;
    //Counting the number of token
    while(token !=NULL){
        token_count++;
        token=strtok(NULL,delimiter);
    }
    //Allocate memory for the array of strings and then adding each token to the array
    char ** arr = (char**) malloc((token_count+1)*sizeof(char*));
    int i = 0;
    strcpy(copy,raw_command);
    token = strtok(copy,delimiter);

    while(token != NULL){
        arr[i] = strdup(token);
        token = strtok(NULL,delimiter);
        i++;
    }
    arr[i-1][strlen(arr[i-1])-1] = '\0',
    arr[i]=NULL;
    return arr;

}
int getPath(char* command,char* path){
    pid_t pid;
    int fd[2];
    char buf[4096];
    if (pipe(fd)==-1){
        perror("enseash %%");
        exit(EXIT_FAILURE);
    }
    if ((pid= fork()) == -1){
        perror("enseash %%");
        exit(EXIT_FAILURE);
    }
    if (pid ==0){//Child process
        
        dup2 (fd[1], STDOUT_FILENO);
        close(fd[0]);
        close(fd[1]);
        execlp("which","which",command,NULL);
        // If execlp fails
        perror("enseash %%");
        exit(127);
    }else{
        close(fd[1]);
        int nbytes = read(fd[0], buf, sizeof(buf));
        buf[strlen(buf)-1]='\0';
        strcpy(path,buf);
        wait(NULL);   
    }
    return 0;  
}
int main() {
    char input[INPUT_SIZE],new_line_buffer[INPUT_SIZE],path[INPUT_SIZE],root_path[INPUT_SIZE];
    char**arguments;
    int status,bytes_read;
    struct timespec time_result_before,time_result_after;
    if (initENSEASH() == -1) {
        exit(1);
    }
    
    // Current shell while loop
    while (1) {
        resetBuffer(input);
        bytes_read = read(STDIN_FILENO,input,sizeof(input));
        clock_gettime(CLOCK_MONOTONIC,&time_result_before);
        if (!strcmp(input,EXIT) || bytes_read ==0){
            exit(EXIT_SUCCESS);
        }
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("Fork failed");
        }
        if (pid == 0) {
            arguments = getArguments(input," ");
            getPath(arguments[0],path);
            execv(path,arguments);
            
            // If execlp fails
            perror("enseash %%");
            exit(127);

        } else {
            int status;
            //waiting for the child
            waitpid(pid, &status, 0);
            if(WIFEXITED(status)){
                int exit_code = WEXITSTATUS(status);
                clock_gettime(CLOCK_MONOTONIC,&time_result_after);
                sprintf(new_line_buffer,SHELL_NAME2,exit_code,getExecutionTime(time_result_before,time_result_after));
                
            }
            
        }
        
        
        write(STDOUT_FILENO, new_line_buffer, strlen(new_line_buffer));
        
    }
    return 0;
}
