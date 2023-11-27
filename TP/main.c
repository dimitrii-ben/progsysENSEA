#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "constant_header.h"
#include "microshellcreat.h"
#include "prompt.h"

int main (){
	
	
	create_enseash();
	while(1){
		write(STDOUT_FILENO, PROMPT_MESSAGE, strlen(PROMPT_MESSAGE));
		pid_t pid=fork(); // fork to be able to execute a new command after the first one
		
		if (pid==-1){
			perror("fork impossible");
			exit(EXIT_FAILURE);
		}
		else if (pid==0){ // if it is the child
			prompt();
			perror("enseash %");
			exit(127);			
}
		else{
			int status;
			waitpid(pid,&status,0);	//waiting for the child process to be terminated
			}}
	return 0;
}
	
