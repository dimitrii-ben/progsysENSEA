#include <unistd.h>
#include <string.h>
#include <stdio.h>

#define WELCOME_MSG "Welcome to ENSEA Tiny Shell.\nPour quitter, tapez 'exit'.\n"
#define SHELL_NAME "enseash %"

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
    if (initENSEASH() == -1) {
        return 1;  // initialization error
    }

    // Rest of your code goes here

    return 0;
}
