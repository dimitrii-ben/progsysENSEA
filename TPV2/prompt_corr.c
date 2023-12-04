#include <unistd.h>
#include <stdio.h>
#include <string.h>

#include "constant_header.h"
#include "prompt.h"

char prompt(char buff){
	buff[strlen(buff)-1]='0';
	return buff
}
