#include "common.h"

void startLoop(FILE *, char *) 

int main(int argc, char *argv[]) 
{
	int i;
	char ** nameList;
	
	/* create array to hold given filenames */
	nameList = (char**) malloc((argc) * sizeof(char*));
	if(nameList == NULL)
	{
		printf("error, out of memory");
		exit(0);
	}
	
	for(i=1;i<argc;i++)	  	/* copy the given filenames to the name array */
	{
	   nameList[i] = malloc((MAX_FILENAME) * sizeof(char));
	   if(nameList[i] == NULL)
	   {
	   	printf("error, out of memory");
	   	exit(0);
	   }
	   strcpy(nameList[i],argv[i]);

	}

	for(i=1;i<argc;i++)
	{
		startLoop(nameList[i]);
		endLoop(nameList2[i]);
	}
}

