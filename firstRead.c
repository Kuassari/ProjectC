/* check if a given string is a command. 
 * return its number if it is, or -1 if it's not */
int checkCMD(char * toCheck)
{
   int i;
   for(i = 0; i<COMMANDS_NUMBER; i++){
	if(strcmp(commands[i],toCheck) == 0)
		return i;
   }


   return -1;
}


/* the first loop that opens the given filename, reads through it, adding the relevant information to symbols linked-list, code table, and data table */
startLoop(char * fileName)
{

	FILE *fp;
	int j;
	char[MAX_BUF] buf;
	bool label;
	char[MAX_LABEL] word;
	char letter;
	int cmdNUM;		/* what comand it is */
	fp = fopen(fileName, "r");

	if(!fp)
	{
	   printf("cannot open file\n");
	   exit(0);
	}

	while(fgets(buf,MAX_BUF,fp) != NULL){ /* reads a line from the text file */
	   if(strchr(buf,':') != NULL){ /* check if the line contains a label */
	     	label = true;
		sscanf(buf, " %s", word);
		
		if(strchr(word,':') == NULL){

		    /*error, ':' is not part of label*/
		    /* ADD ERROR HANDLING */
		}
		strncpy(letter,word,1);
		if(isalpha(letter)==0){
		    /*error, first letter is not a real letter */
		    /* ADD ERROR HANDLING */
		}
		
		
	   }

	   else{
	     	label = false;
	   }

	   if(strstr(buf,".data") != NULL || strstr(buf,".string") != NULL){
		 /* step 6+7 in algorithm */  
		}
		
		if(strstr(buf,".entry") != NULL || strstr(buf,".extern") != NULL){
		 /* step 9+10 in algorithm */
		}
		
		/* step 11 */

	   cmdNUM = checkCMD(buf);
	   switch(cmdNUM){
		case -1: /* error: no command */
		case 0:  /* mov */
		case 1:  /* cmp */
		case 2:  /* add */
		case 3:  /* sub */
		case 4:  /* not */
		case 5:  /* clr */
		case 6:  /* lea */
		case 7:  /* inc */
		case 8:  /* dec */
		case 9:  /* jmp */ 
		case 10: /* bne */
		case 11: /* red */
		case 12: /* prn */
		case 13: /* jsr */
		case 14: /* rts */
	   	case 15: /* stop */
	   }
	}

	/* merge code table with data table */
}
