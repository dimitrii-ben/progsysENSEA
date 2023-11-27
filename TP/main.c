#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>

#define WELCOME_MSG "Welcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'.\n"
#define SHELL_NAME "enseash %"
#define EXIT "exit\n"
#define INPUT_SIZE 128

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

int main() {
    char input[INPUT_SIZE];
    if (initENSEASH() == -1) {
        return 1;
    }
    
    // Current shell while loop
    while (1) {
        read(STDIN_FILENO,input,sizeof(input));
        
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("Fork failed");
        }
        if (pid == 0) {
            input[strlen(input)-1] = '\0';
            execlp(input, input, NULL);
            // If execlp fails
            perror("execlp");

        } else {
            int status;
            waitpid(pid, &status, 0);
            if (WIFEXITED(status)) {
                int exit_status = WEXITSTATUS(status);
            } else {
                // Handle error if the child process didn't exit normally
            }
        }
        write(STDOUT_FILENO, SHELL_NAME, strlen(SHELL_NAME));
        for(int i = 0;i<INPUT_SIZE;i++){
            input[i]=0;
        }
    }
    return 0;
}
