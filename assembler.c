#include "common.h"

int main(int argc, char *argv[]) 
{
	int i;
	/*char **nameList;*/
	
	/* create array to hold given filenames 
	nameList = (char**) malloc((argc) * sizeof(char*);
	if(nameList == NULL)
	{
		printf("error, out of memory");
		exit(0);
	}
	*/
	/*for(i=1;i<argc;i++)	  	/* copy the given filenames to the name array 
	{
	   nameList[i] = malloc((MAX_FILENAME) * sizeof(char));
	   if(strncmp(nameList[i],STRING_END) == 0)
	   {
	   	printf("error, out of memory");
	   	exit(0);
	   }
	   strcpy(nameList[i],argv[i]);
	   strcat(nameList[i],STRING_END);

	}
	*/
	for(i=1;i<argc;i++)
	{
		startLoop(argv[i]);
		endLoop(argv[i]);
	}

	return 0;
}

