#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "constant_header.h"
#include "prompt.h"

void prompt(void){
			read(STDIN_FILENO,input_buffer,BUFF_SIZE);	// reading of the command enters by the user
		
			input_buffer[strlen(input_buffer)-1]='\0'; // The buffer takes into account when we tap entry so we have a buffer that looks like that "fortune\n\0" so we have to remove the \n to execute the good command//

			if(input_buffer!='exit'){
				execlp(input_buffer,input_buffer,NULL);	//execute the command given in input
			}
			else{
				write(STDOUT_FILENO, BYE_MESSAGE, strlen(PROMPT_MESSAGE));
				exit(EXIT_SUCCESS);}
			printf("1");
}

		
		
	
	
