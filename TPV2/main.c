#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>

#include "constant_header.h"
#include "microshellcreat.h"
#include "prompt.h"

int main (){
	int ctrld;
	double ex_time=4;
	struct timespec time1={0},time2={0};
	pid_t pid;
	int code;
	char exit_code[BUFF_SIZE]="";
	create_enseash();
	while(1){
		write(STDOUT_FILENO,PROMPT_MESSAGEp1, strlen(PROMPT_MESSAGEp1));
		write(STDOUT_FILENO,exit_code, strlen(exit_code));
		write(STDOUT_FILENO,PROMPT_MESSAGEp2, strlen(PROMPT_MESSAGEp2));
		ctrld=read(STDIN_FILENO,input_buffer,BUFF_SIZE);	// reading of the command enters by the user
		clock_gettime(CLOCK_REALTIME,&time1);
		input_buffer[strlen(input_buffer)-1]='\0'; // to delete the tap of enter at the end
		if((strcmp(input_buffer,"exit")==0)||(ctrld==0)){ //EOF is zero in the read
			write(STDOUT_FILENO, BYE_MESSAGE, strlen(BYE_MESSAGE));
			exit(EXIT_SUCCESS);}
		else{			
			pid=fork();} // fork to be able to execute a new command after the first one
		
		if (pid==-1){
			perror("fork impossible");
			exit(EXIT_FAILURE);
		}
		else if (pid==0){ // if it is the child
			prompt(input_buffer,ex_time);
			perror("enseash %");
			exit(127);			
}
		else{
			int status;
			waitpid(pid,&status,0);	//waiting for the child process to be terminated
					clock_gettime(CLOCK_REALTIME,&time2);
			ex_time= (double) (time2.tv_nsec-time1.tv_nsec)/1000000; //computation of the execution time
			if (WIFEXITED(status)){
				code=WEXITSTATUS(status);
				sprintf(exit_code, "[exit: %d| %f ms]",code,ex_time);
			} else if (WIFSIGNALED(status)){
				code=WTERMSIG(status);
				sprintf(exit_code, "[signal: %d| %f ms]",code,ex_time);}
			}}
	return 0;
}
	
