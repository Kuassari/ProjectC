



/* the first loop that opens the given filename, reads through it, adding the relevant information to symbols linked-list, code table, and data table */
startLoop(char * fileName)
{

	FILE *fp;			
	int j,i;			/* index variable */
	char[MAX_BUF] buf;		/* a buffer to hold the current line read */
	bool label;			/* holds info on whether a label exists in line or not */
	char[MAX_LABEL_LENGTH] word;	/* a buffer for the curent word read */
	char letter;			
	int labelpos;			/* label position in line */ 
	int cmdNUM;			/* command type */

	fp = fopen(fileName, "r");

	if(!fp)
	{
	   printf("cannot open file\n");
	   exit(0);
	}

	while(fgets(buf,MAX_BUF,fp) != NULL) /* reads a line from the text file */
	{
	   strncpy(letter,buf,1);
	   if(letter == ';')
	   {
		break;
	   }
	   
	   i = 0;
	   while(isspace(buf+i) /* checks if the line is empty */
	   {
	   	i++;
		if((buf+i) == EOF)
		{
		    break;
		{
	   }

	   if((labelpos = strchr(buf,':')) != NULL)  /* checks if the line contains a label */
	   {
	     	label = true;
		sscanf(buf, " %s", word);
		
		if(strchr(word,':') == NULL)
		{

		    /*error, ':' is not part of label*/
		    /* ADD ERROR HANDLING */
		}
		
		if(isalpha(letter)==0)
		{
		    /*error, first letter is not a real letter */
		    /* ADD ERROR HANDLING */
		}
		
		
	   }

	   else
	   {
	     	label = false;
	   }

	   if(strstr(buf,".data") != NULL || strstr(buf,".string") != NULL)
		{
		 /* step 6+7 in algorithm */  
		}
		
		if(strstr(buf,".entry") != NULL || strstr(buf,".extern") != NULL)
		{
		 /* step 9+10 in algorithm */
		}
		
		/* step 11 */
	   if(label)
	   {
		j = skipSpaces(buf+labelpos,word);
		j += labelpos;
	   }
	   else
	   {
		j = skipSpaces(buf+j,word);
	   }
	   

	   cmdNUM = checkCMD(word);
	   switch(cmdNUM)
	   {
		case -1: /* error: no command */
		case 0:  /* mov */ 
			j = skipSpaces(buf+j,word);
			
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
			
		default: /* if not a command, or error */
	   }
	}

	/* merge code table with data table */
}

int skipSpaces(char * str, char * toWord)	/* a function for "skipping" spaces in a given string */
{
	int i = 0;
	while(isspace(str+i)) 	 	/* as long as current letter pointed to in the string is space */
	{
	   i++;			 	/* skip a letter */
	   if((str+i) == EOF) 	 	/* check for making sure we didn't reach end of string */
		break;
	}
	toWord = strcpy(toWord,buf+i);  /* copy the next "word" to the desired string */
	
	return i;
}

int checkTwoOperands(char * str)			/* a function to check the operands of a command that needs 2 operands. assume these 2 operands exist in the string and the given string begins with the first operand and not a space */
{
	int i = 0;
	bool op1reg;
	bool op2reg;
	bool squareBrackets;
	bool directNum;
	char * temp;
	
	if(str[i] == '#')
	{
	   directNum == true;
	   
	}
	if(str[i] == 'r' && isdigit(str[i+1]) && directNum == false) /* first operand found to be a register */
	{
	   if(str[i+1] == 8 || str[i+1] == 9)
	   {
		/* error, illegal number of register */
		/* ADD ERROR HANDLING */
	   }
	   op1reg = true;
	   i = skipSpaces(str, temp);
	}
	

}
