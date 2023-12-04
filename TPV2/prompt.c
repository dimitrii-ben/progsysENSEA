#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <time.h>

#include "constant_header.h"
#include "prompt.h"

double prompt(char* inp,double dt){
	
	if(strcmp(inp,"exit")!=0){
		execlp(inp,inp,NULL);	//execute the command given in input
		
		
	}
		
}

		
		
	
	
