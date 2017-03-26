
int checkOneOperand(char *) 
int checkTwoOperands(char *)
int skipSpaces(char *, char *)
int frstOpChk(char *)


/* the first loop that opens the given filename, reads through it, adding the relevant information to symbols linked-list, code table, and data table */
startLoop(char * fileName)
{

	FILE *fp;	
	int lineNum = 0;		/* holds the current line number */
	int j,i;			/* index variable */
	char[MAX_BUF] buf;		/* a buffer to hold the current line read */
	bool label;			/* holds info on whether a label exists in line or not */
	char[MAX_LABEL_LENGTH] word;	/* a buffer for the curent word read */
	char letter;			
	int labelpos;			/* label position in line */ 
	int cmdNUM;			/* command type */
	int 1opresult;
	int 2opresult;

	fp = fopen(fileName, "r");

	if(!fp)
	{
	   printf("cannot open file\n");
	   exit(0);
	}

	while(fgets(buf,MAX_BUF,fp) != NULL) /* reads a line from the text file */
	{
	   lineNum++;
	   /* check for empty or comment line */
	   j = 0; /* reset index j before check */
	   if((j = skipSpaces(buf,word)) == -1)
	   {
		/* empty line */
		break;
	   }
	   strncpy(letter,buf+j,1); /* check first non-space letter of the line to see if it's a comment line */
	   if(letter == COMMENT_SIGN)
	   {
		break;
	   }
	   j = 0; /* reset index j after check */
	   
	   if((labelpos = strchr(buf,LABEL_FLAG)) != NULL)  /* checks if the line contains a label */
	   {
	     	label = true;
		sscanf(buf, " %s", &word);
		
		/* checks for valid label */
		if(strchr(word,LABEL_FLAG) == NULL)
		{

		    /* error, ':' is not part of label */
		    /* ADD ERROR HANDLING */
		}
		
		if(isalpha(letter)==0)
		{
		    /* error, first letter is not a real letter */
		    /* ADD ERROR HANDLING */
		}
		
		if(strlen(word)>MAX_LABEL_LENGTH)
		{
		   /* error, label length is too big*/
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
		
		/* step 11 in algorithm */

	   /* skip spaces in line until next word is reached */
	   if(label)
	   {
		j = skipSpaces(buf+labelpos,word);
	   	if(j == -1)
		{
			/* error: no more letters in line */
		}
		j += labelpos;
	   }
	   else
	   {
		j = skipSpaces(buf+j,word);
		if(j == -1)
		{
			/* error: no more letters in line */
		}
	   }
	   

	   cmdNUM = checkCMD(word);
	   switch(cmdNUM)
	   {
		case -1: /* error: no command */
		case 0:  /* mov */ 
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			2opresult = checkTwoOperands(buf+j);
			if(2opresult % 10 == 1)
			{
				/* error: destination operand is using illegal assignment method for 'mov' (immediate) */
				/* ADD ERROR HANDLING */
			}
	
		case 1:  /* cmp */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			2opresult = checkTwoOperands(buf+j);


		case 2:  /* add */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			2opresult = checkTwoOperands(buf+j);
			if(2opresult % 10 == 1)
			{
				/* error: destination operand is using illegal assignment method for 'add' (immediate) */
				/* ADD ERROR HANDLING */
			}

		case 3:  /* sub */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			2opresult = checkTwoOperands(buf+j);
			if(2opresult % 10 == 1)
			{
				/* error: destination operand is using illegal assignment method for 'sub' (immediate) */
				/* ADD ERROR HANDLING */
			}

		case 4:  /* not */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			1opresult = checkOneOperand(buf+j)
			if(1opresult == 1)
			{
				/* error: destination operand is using illegal assignment for 'not' (immediate) */
				/* ADD ERROR HANDLING */
			}

		case 5:  /* clr */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			1opresult = checkOneOperand(buf+j)
			if(1opresult == 1)
			{
				/* error: destination operand is using illegal assignment for 'not' (immediate) */
				/* ADD ERROR HANDLING */
			}

		case 6:  /* lea */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			2opresult = checkTwoOperands(buf+j);
			if(2opresult < 30 ) 
			{
				/* error: origin operand is using illegal assignment methods for command 'lea' (immediate or register) */
				/* ADD ERROR HANDLING */
			}

		case 7:  /* inc */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			1opresult = checkOneOperand(buf+j)
			if(1opresult == 1)
			{
				/* error: destination operand is using illegal assignment for 'not' (immediate) */
				/* ADD ERROR HANDLING */
			}
			
		case 8:  /* dec */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			1opresult = checkOneOperand(buf+j)

			
		case 9:  /* jmp */ 
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			1opresult = checkOneOperand(buf+j)
			if(1opresult == 1)
			{
				/* error: destination operand is using illegal assignment for 'not' (immediate) */
				/* ADD ERROR HANDLING */
			}
			
		case 10: /* bne */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			1opresult = checkOneOperand(buf+j)
			if(1opresult == 1)
			{
				/* error: destination operand is using illegal assignment for 'not' (immediate) */
				/* ADD ERROR HANDLING */
			}
			
		case 11: /* red */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			1opresult = checkOneOperand(buf+j)
			if(1opresult == 1)
			{
				/* error: destination operand is using illegal assignment for 'not' (immediate) */
				/* ADD ERROR HANDLING */
			}
			
		case 12: /* prn */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			1opresult = checkOneOperand(buf+j)

			
		case 13: /* jsr */
			j = skipSpaces(buf+j,word);
			if(j == -1)
			{
				/* error: no more letters in line */
				/* ADD ERROR HANDLING */
			}

			1opresult = checkOneOperand(buf+j)
			if(1opresult == 1)
			{
				/* error: destination operand is using illegal assignment for 'not' (immediate) */
				/* ADD ERROR HANDLING */
			}
			
		case 14: /* rts */
			
	   	case 15: /* stop */
			
		default: /* if not a command, or error */

			/* ADD ERROR HANDLING */
	   }
	}

	/* merge code table with data table */
}

int skipSpaces(char * str, char * toWord)	/* a function for "skipping" spaces in a given string */
{
	int i = 0;
	while(isspace(str+i)) 	 		/* as long as current letter pointed to in the string is space */
	{
	   i++;			 		/* skip a letter */
	   if((str+i) == NEWLINE) 	 	/* check for making sure we didn't reach end of string */
		return -1;			/* if we did, return -1 to signal */
	}
	toWord = strcpy(toWord,buf+i);  	/* copy the next "word" to the desired string */
	
	return i;				/* return the index for the next non-space character in str */
}



int checkTwoOperands(char * str)			/* a function to check the operands of a command that needs 2 operands. assume these 2 operands exist in the string and the given string begins with the first operand and not a space */
{
	int i = 0;
	int j = 0;
	int length = 0;
	
	/* bool variables used as flags by the function */
	
	bool op1directNum = false;
	bool op1variable = false;
	bool op1regIndx = false;
	bool op1reg = false;
	

	int op1type = 0;	/* variables for holding operand types. 0 is not found or error, 1 is immediate number */
	int op2type = 0;	/* 2 is register, 3 is register-index assignment, and 4 is variable */

	char * op1;	/* a string to hold first operand information */
	char * op2;	/* a string to hold second operand information */
	char * garbage; /* a char array to hold garbage  */
	

	if(str[i] == IMD_FLAG)
	{

	   if((garbage = strstr(str,COMMA)) == NULL)	/* check line for comma */
	   {
			/* error: no comma separating operands */
			/* ADD ERROR HANDLING */
	   }
	   length = strcspn(str,COMMA); 		/* check for the end of first operand by finding comma */
	   strncpy(op1,str,length);			/* copy where first operand should be to op1 (with the comma, for the check) */
	   strcpy(op2,str+length); 			/* copy where next operand should be to op2 (without the comma) */
	   

	   i = 0;
	   while(i<length-1)
	   {	   
		if(isdigit(op1+1+i)) /* check to make sure that the first operand is really a number, we add +1 to skip the "#" sign*/
		{
		   i++;
		}
		else if(i == 0 && (op1+1 == PLUS || op1+1 == MINUS))
		{
		   i++; 	/* plus or minus signs are allowed before the number */
		}
		else
		{
		   /* error: first operand contains non-digit*/
		   /* ADD ERROR HANDLING */
		}
	   }

	   if(frstOpChk(op1) == -1)
	   {
		/* error: non-space exists between first operand and comma */
		/* ADD ERROR HANDLING */
	   }
	   op1type = 1;		/* signal that first operand is an immediate number */
	}


	if(str[i] == REG_FLAG && isdigit(str[i+1]) && op1type == 0) 	/* first operand found to be a register */
	{
	   if(str[i+1] == 8 || str[i+1] == 9) /* check for illegal register numbers */
	   {
		/* error: illegal number of register */
		/* ADD ERROR HANDLING */
	   }
	   else if(str[i+2] != SPACE && str[i+2] != COMMA) 	/* check if next letter in str is not a valid char */
	   {
		if(str[i+2] == LEFT_BRACKET && str[i+3] == REG_FLAG && isdigit(str[i+4])) 	/* check if using index assignment by checking for expression like "r1[r2]" */
		{
		   if(str[i+1] % 2 == 1)	/* check to make sure first reg is odd number */
		   {
			if(str[i+5] == RIGHT_BRACKET)
			{
			   if(str[i+6] == SPACE || str[i+6] == COMMA)
			   {
			   	op1type = 3; 		/* signal that first operand is a register-index assignment */

			  	if((garbage = strstr(str,COMMA)) == NULL)
			   	{
					/* error: no comma separating operands */
					/* ADD ERROR HANDLING */
			   	}

			   	length = strcspn(str,COMMA);		/* find the beginning of the next operand info */
			   	strcpy(op2,str+length+1); 		/* copy it to op2, skipping the comma */
			   	strncpy(op1,str,length);		/* copy the first part to op1 (with the comma, for the check) */	
	 
			   }
			   else
			   {
			      /* error: non-space non-comma character after first operand */
			      /* ADD ERROR HANDLING */
			   }

			}
			else
			{
			    /* error: no closing right bracket */
			    /* ADD ERROR HANDLING */
			}

		   }
		   else
		   {
			/* error: first register must be odd number */
			/* ADD ERROR HANDLING */
	   	   }
		   
		}
		else
		{
		   /* error: not a valid char */
		   /* ADD ERROR HANDLING */
		}
	   }
	   else
	   {
	   	op1type = 2; 		/* signal that first operand is a register */
		if((garbage = strstr(str,COMMA)) == NULL)
		{
			/* error: no comma separating operands */
			/* ADD ERROR HANDLING */
		}

		length = strcspn(str,COMMA);		/* find the beginning of the next operand info */
		strcpy(op2,str+length+1); 		/* copy it to op2, skipping the comma */
		strncpy(op1,str,length);		/* copy the first part to op1 (with the comma, for the check) */
		
	   }

	   if(frstOpChk(op1) == -1)
	   {
		/* error: non-space exists between first operand and comma */
		/* ADD ERROR HANDLING */
	   }
	}
	
	if(op1type == 0)	/* check that we didn't find first operand type yet, so should be a variable */ 
	{
	   op1type = 4; 		/* signal that first operand is a variable */
	   if((garbage = strstr(str,COMMA)) == NULL)
	   {
		/* error: no comma separating operands */
		/* ADD ERROR HANDLING */
	   }
	   length = strcspn(str,COMMA);		/* find the beginning of the next operand info */
	   strcpy(op2,str+length+1); 		/* copy it to op2, skipping the comma */
	   strncpy(op1,str,length);		/* copy the first part to op1 (with the comma, for the check) */
	   
	   

	   /* ADD HANDLING THE FIRST OPERAND AS A VARIABLE */
	   /* ADD HANDLING THE FIRST OPERAND AS A VARIABLE */
	   /* ADD HANDLING THE FIRST OPERAND AS A VARIABLE */

	   
	   if(frstOpChk(op1) == -1)
	   {
		/* error: non-space exists between first operand and comma */
		/* ADD ERROR HANDLING */
	   }
	}



	/* ------- first operand check is finished ------- */

	
	/* reset index numbers before op2 check */
	i=0;
	
	i = skipSpaces(op2, op2)
	if(i == -1)
	{
		/* error: line is empty after comma */
		/* ADD ERROR HANDLING */
	}

	op2type = checkOneOperand(op2);		/* send the second operand to be checked by the single operand check function */
	if(op2type == 0)	/* operand type not found for second operand */
	{
	   /* error: error with 2nd operand */
	   /* ADD ERROR HANDLING */
	}
	
	if(op1type == 0)	/* operand type not found for first operand */
	{
		/* error: no valid first operand found */		
		/* ADD ERROR HANDLING */
	}
	else
	{
	   op1type *= 10; 		/* turn the result of op1type to "tens" */
	   op1type += op2type;  	/* then add op2type, and we get both types in one integer to work with*/
	   return op1type;		/* return the result. the origin operand is in the "tens" digit, and the destination operand is in the "ones" digit */
	}

}

int frstOpChk(char * op1) /* a function that recieves the first operand of a two-operand command, and checks that there are no values between it and the comma separating it from the second operand (should be the last letter of op1 */
{

	int j = 0;
	int i = 0;
	char * garbage;
	
	while(isalnum(op1+j) && op1[j] != COMMA) 	/* check the part between first operand and comma, until reaching space or comma */
	{
	   j++;
	}
	if(op1[j] != COMMA)				/* if space is reached */
	{
	   i = skipSpaces(op1+j, garbage); 	/* skip to next non-space letter */
	   if(i == -1)
	   {
		/* error: line is empty after first operand */
		/* ADD ERROR HANDLING */
	   }
	   if(op1[i] != COMMA)			/* check that it's a comma, if it's not, then there is an error in the line */
	   {
		/* error: non-space after first operand and before comma */
		return -1; 	/* return -1 to signal an error */
	   }
	}
	
	return 1; /* return 1 to signal everything is fine */
	
	
}


int checkOneOperand(char * str) /* a function to check the validity and type of a single operand, which can be a second operand of a two-operand command, or the single operand if a one-operand command. assumes the string given starts with the first letter of the operand. return 1 for immediate number, 2 for register, 3 for register-index, and 4 for variable. 0 is given if no type is detected */
{

	int i = 0;
	int j = 0;
	int length = 0;
	bool typeFound = false;
	
	char * garbage; /* a char array to hold garbage  */

	if(str[i] == IMD_FLAG)
	{
	   typeFound = true;
	   if((garbage = strstr(str,COMMA)) != NULL)	/* check line for comma */
	   {
			/* error: there is a comma but shouldn't be */
			/* ADD ERROR HANDLING */
	   }
	   while(i<length-1)
	   {	   
		if(isdigit(op1+1+i)) /* check to make sure that the operand is really a number, we add +1 to skip the "#" sign*/
		{
		   i++;
		}
		else if(i == 0 && (op1+1 == PLUS || op1+1 == MINUS))
		{
		   i++; 	/* plus or minus signs are allowed before the number */
		}
		else
		{
		   /* error: first operand contains non-digit*/
		   /* ADD ERROR HANDLING */
		}
	   }
	   j = skipSpaces(str+i, garbage);
	   if(j != -1)
	   {
		/* error: non-space letter between operand and newline */
		/* ADD ERROR HANDLING */
	   }
	   
	   return 1;	/* immediate number found with no errors */
	}

	if(str[0] == REG_FLAG && isdigit(str[1]) && typeFound == false) /* operand found to be a register */
	{
	   typeFound = true;
	   if(str[1] == 8 || str[1] == 9) /* check for illegal register numbers */
	   {
		/* error: illegal number of register */
		/* ADD ERROR HANDLING */
	   }
	   if(str[2] != SPACE) 	/* check if next letter in str is not a valid char */
	   {
		if(str[2] == LEFT_BRACKET && str[3] == REG_FLAG && isdigit(str[4])) 	/* check if using index assignment by checking for expression like "r1[r2]" */
		{
		   if(str[1] % 2 == 1)	/* check to make sure first reg is odd number */
		   {
			if(str[5] == RIGHT_BRACKET)
			{
			   if(str[6] == SPACE)
			   {
			  	if((garbage = strstr(str,COMMA)) != NULL)
			   	{
					/* error: there is a comma but shouldn't be */
					/* ADD ERROR HANDLING */
			   	}
				
				return 3; /* register index assignment found with no errors */
			   }
			   else
			   {
			      /* error: non-space non-comma character after first operand */
			      /* ADD ERROR HANDLING */
			   }
			}
			else
			{
			    /* error: no closing right bracket */
			    /* ADD ERROR HANDLING */
			}
		   }
		   else
		   {
			/* error: first register must be odd number */
			/* ADD ERROR HANDLING */
	   	   }
		   
		}
		else
		{
		   /* error: not a valid char */
		   /* ADD ERROR HANDLING */
		}
	   }
	   else 	/* there was a space after register number */
	   {
		j = skipSpaces(str2, garbage);
	   	if(j != -1)
	   	{
			/* error: non-space letter between operand and newline */
			/* ADD ERROR HANDLING */
	  	}

		return 2; 	/* register found with no errors */
	   }


	if(typeFound == false)	/* check that we didn't find operand type yet, so should be a variable */ 
	{
	   typeFound = true;
	   if((garbage = strstr(str,COMMA)) != NULL)
	   {
		/* error: there is a comma but shouldn't be */
		/* ADD ERROR HANDLING */
	   }
	      

	   /* ADD HANDLING THE FIRST OPERAND AS A VARIABLE */
	   /* ADD HANDLING THE FIRST OPERAND AS A VARIABLE */
	   /* ADD HANDLING THE FIRST OPERAND AS A VARIABLE */


	   i = skipSpaces(str, garbage);
	   if(i != -1)
	   {
			/* error: line isn't empty after first operand */
			/* ADD ERROR HANDLING */
	   }

	   return 4; 	/* variable found with no errors */
	}



	return 0;	/* no valid operand found */
}
