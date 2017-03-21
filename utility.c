
/* check if a given string is a command. 
 * return its number if it is, or -1 if it's not */
int checkCMD(char * toCheck)
{
   int i;
   for(i = 0; i<COMMANDS_NUMBER; i++)
	if(strncmp(commands[i],toCheck,3) == 0)
		return i;

   return -1;
}

