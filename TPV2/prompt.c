#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>

#include "constant_header.h"
#include "prompt.h"

void prompt(char* inp){
			
			if(strcmp(inp,"exit")!=0){
				execlp(inp,inp,NULL);	//execute the command given in input
			}
			
}

		
		
	
	
