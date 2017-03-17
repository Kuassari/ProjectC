#include "common.h"

void startLoop(FILE *, char *) 

int main(int argc, char *argv[]) {

	int i;
	int IC = 100;
	int DC = 0;
	*char[] nameList;
	
	/* create array to hold given filenames */
	nameList = malloc((argc) * sizeof(char*));
	if(nameList == NULL)
	{
	   printf("error, out of memory");
	   exit(0);
	}
	/* in each array block, create a string to hold the filename, adding ".as" at the end, as needed */
	for(i=1;i<argc;i++){
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
	
	for(i=1;i<argc;i++){
	startLoop(nameList[i]);
	endLoop(nameList[i]);
	}
}



/* the first loop that opens the given filename, reads through it, adding the relevant information to symbols linked-list, code table, and data table */
startLoop(char * fileName){

	FILE *fp;
	int j;
	char[MAX_BUF] buf;
	fp = fopen(fileName, "r");
	if(!fp){
	   printf("cannot open file\n");
	   exit(0);
	}

	while(fgets(buf,MAX_BUF,fp) != NULL){
	   
	   
	   
	   
	   
	   
	}
}
