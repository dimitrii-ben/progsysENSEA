#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "constant_header.h"
#include "microshellcreat.h"

void create_enseash( void){
	 write(STDOUT_FILENO, WELCOME_MESSAGE, strlen(WELCOME_MESSAGE));
	 //write(STDOUT_FILENO, PROMPT_MESSAGE, strlen(PROMPT_MESSAGE));
 }
 
