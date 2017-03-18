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

	/* in each array block, create a string to hold the filename, 
         * adding ".as" at the end, as needed */
	for(i=1;i<argc;i++)
	{
	   nameList[i] = malloc((MAX_FILENAME) * sizeof(char));
	   if(nameList[i] == NULL)
	   {
	   printf("error, out of memory");
	   exit(0);
	   }
	   strcpy(nameList[i],argv[i]);
	   strcar(nameList[i],".as");
	   /* copy the given filename to the name array, and add ".as" to it's end */
	}
	
	for(i=1;i<argc;i++)
	{
		startLoop(nameList[i]);
		endLoop(nameList[i]);
	}
}

