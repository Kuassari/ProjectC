#include "common.h"

int skipSpaces(char *, char *)

/* the second loop that: opens the given filename to read and 3 other output files to write to, translates the relevant code from the given file in assembly to machine code in the output files */
endLoop(char * fileName)
{

	FILE * fp, fob, fent, fext;	
	int lineNum = 0;			/* holds the current line number */
	int j,i;				/* index variable */
	bool label_flag;			/* holds info on whether a label exists in line or not */
	char[MAX_BUF] buf;			/* a buffer to hold the current line read */
	char[MAX_BUF] tempBuf;			/* a temp buffer to hold a part of buf temporarily */
	char[MAX_BUF] tempBuf2;			/* another temp buffer to hold a part of buf temporarily */
	char[MAX_BUF] tempLabel;		/* a buffer for holding potential label name */
	char[MAX_LABEL_LENGTH] label;   	/* holds current label if it exists */
	char[MAX_LABEL_LENGTH] tempWord;	/* a temp buffer to hold a temporary word from buf */
	char[MAX_LABEL_LENGTH] sourceFile;
	char[MAX_LABEL_LENGTH] objFile;
	char[MAX_LABEL_LENGTH] entFile;
	char[MAX_LABEL_LENGTH] extFile;
	cod tempCod;				/* holds info on current line of code that we collected on first loop */
	sym tempSym;				/* holds info on a temporary symbol */
	int groupCode;
	int opCode;
	int 1op;
	int 2op;
	int ARE;				/* holds current ERA value */
	int 1opARE;		

	int tempNum;				/* a temp int to hold numbers */
	char letter;			
	int labelpos;				/* label position in line */ 
	int cmdNUM;				/* command type */
	int 1opresult;
	char * op1name;
	int 2opresult;
	char * op2name;
	int check;
	int L; 					/* the number of words required by the line */
	int address;				/* hold address of current symbol\entry\extern word */

	strcpy(sourceFile,fileName);	
	strcpy(objFile,fileName);	
	strcpy(entFile,fileName);	
	strcpy(extFile,fileName);	


	strcat(sourceFile,SOURCE_FILE);		/* add ".as" to the end of the filename, to address to the proper file */
	strcat(objFile,OBF_FILE);		/* add ".ob" to the end of the filename, to address to the proper file */
	strcat(entFile,ENT_FILE);		/* add ".ent" to the end of the filename, to address to the proper file */
	strcat(extFile,EXT_FILE);		/* add ".ext" to the end of the filename, to address to the proper file */
	
	fp = fopen(sourceFile, "r");
	fob = fopen(objFileFile, "a");
	fent = fopen(entFileFile, "a");
	fext = fopen(extFileFile, "a");

	if(!fp)
	{
	   printf("cannot open file\n");
	   exit(0);
	}

	while(fgets(buf,MAX_BUF,fp) != NULL) 	/* reads a line from the text file */
	{
	   lineNum++;
	   /* check for empty or comment line */
	   j = 0; /* reset index j before check */
	   if((j = skipSpaces(buf,tempWord)) == -1)
	   {
		/* empty line */
		break;
	   }

	   /*--- MAKE SURE TO CHECK IF J IS NEEDED IN NEXT LINE ---*/
	   /*--- MAKE SURE TO CHECK IF J IS NEEDED IN NEXT LINE ---*/ 
	   /*--- MAKE SURE TO CHECK IF J IS NEEDED IN NEXT LINE ---*/

	   strncpy(letter,buf+j,1); 		/* check first non-space letter of the line to see if it's a comment line */
	   if(letter == COMMENT_SIGN)
	   {
		break;
	   }
	   j = 0; /* reset index j after check */
	   
	   if((labelpos = strchr(buf,LABEL_SIGN)) != NULL) 	 /* checks if the line contains a label */
	   {
		sscanf(buf, " %s", &tempLabel);
		
		/* checks for valid label */
		if(strchr(tempLabel,STRING_SIGN) != NULL)				/* find if there is a '"' in the word */
		{
		   check = strcspn(tempLabel,LABEL_SIGN);				/* find the location of ':' */
		   strncpy(tempWord,tempLabel,length);					/* copy the part of the word before ':' into tempWord, to check */
		   if(strchr(tempWord,STRING_SIGN) == strrchr(tempWord,STRING_SIGN))	/* check that only one '"' exists before ':' */
		   {
			if(strchr(tempLabel+check,LABEL_SIGN) != NULL)
			{
			   break;		/* we have found that ':' is between two '"'s so it's not part of a label, but part of a string */
			}

		   }
		}
		else if(strchr(tempLabel,LABEL_SIGN) == NULL)
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
		
		label_flag = true;
		strncpy(label,tempLabel,(strlen(tempLabel)-1));		/* copy label name to label string, without the ":" at the end */

	   }

	   else
	   {
	     	label_flag = false;
	   }
	
	   if(strstr(buf,DATA_WORD) != NULL || strstr(buf,STRING_WORD) != NULL)
	   {
		/* skip this line */
	   }
		
	   if(strstr(buf,ENTRY_WORD) != NULL || strstr(buf,EXTERN_WORD) != NULL)
	   {
		tempBuf = strchr(buf,SPACE);			/* find the end of instruction name */
		/* step 9+10 in algorithm */
		if(strstr(buf,EXTERN_WORD) != NULL)		/* if it's external instruction */
		{
		   j = skipSpaces(tempBuf,tempBuf);		/* check that line isn't empty after ".extern" */
		   if(j == -1)
		   {
			/* error: no more letters in line */
			/* ADD ERROR HANDLING */
		   }	
		   check = strcspn(tempBuf,SPACE);		/* find the end of external symbol name */
		   strncpy(tempBuf2,tempBuf,check-1);		/* copy the symbol name to tempbuf2, without spaces and ":" */			
		   j = skipSpaces(tempBuf,tempWord);
		   if(j != -1)
		   {
			/* error: line isn't empty after external symbol name */
			/* ADD ERROR HANDLING */
		   }
		   if(getLabel(tempBuf2) != NULL)		/* make sure external word is in symbol list */
		   {
			address = getSymbolAddress(check);	/* get the address of label name*/

			/* convert address to hexadecimal */

			fprintf(fext, address, tempBuf2);	/* write the label name and its address (in hexa) to external labels file */
		   }
		   else
		   {
			/* error: label name doesn't exist in label list */
			/* ADD ERROR HANDLING */
		   }
		}
		else if(strstr(buf,ENTY_WORD) != NULL)		/* if it's entry instruction */	
		{
		   j = skipSpaces(tempBuf,tempBuf);		/* check that line isn't empty after ".entry" */
		   if(j == -1)
		   {
			/* error: no more letters in line */
			/* ADD ERROR HANDLING */
		   }	
		   check = strcspn(tempBuf,SPACE);		/* find the end of entry symbol name */
		   strncpy(tempBuf2,tempBuf,check-1);		/* copy the symbol name to tempbuf2, without spaces and ":" */			
		   j = skipSpaces(tempBuf,tempWord);
		   if(j != -1)
		   {
			/* error: line isn't empty after entry symbol name */
			/* ADD ERROR HANDLING */
		   }
		   if(getLabel(tempBuf2) != NULL)			/* make sure entry word is in symbol list */
		   {
			address = getSymbolAddress(check);	/* get the address of label name*/

			/* convert address to hexadecimal */

			fprintf(fent, address, tempBuf2);	/* write the label name and its address (in hexa) to entry labels file */
		   }
		   else
		   {
			/* error: label name doesn't exist in label list */
			/* ADD ERROR HANDLING */
		   }
		}	 	
	   }
	
	i = 0;
	while(i<code_length)
	{
	
	}
		
	   /* step 11 in algorithm */

	   /* skip spaces in line until next word is reached */
	   if(label_flag)
	   {
		j = skipSpaces(buf+labelpos,word);
	   	if(j == -1)
		{
			/* error: no more letters in line */
			/* ADD ERROR HANDLING */
		}
		j += labelpos;
	   }
	   else
	   {
		j = skipSpaces(buf+j,word);
		if(j == -1)
		{
			/* error: no more letters in line */
			/* ADD ERROR HANDLING */
		}
	   }
	   

	   cmdNUM = checkCMD(word);
	   if(cmdNum >=0 && <= 15) 	/* command in line is a proper command, which should be in code linked list */
	   {
		opCode = tempCod->command;
		tempCod = LineGetCodeInfo(lineNum);
		if(tempCod->command >= 14) /* command is either: rts, stop */
		{
		   group = 0;		/* the command is in the first group, with no operands */
		   1op = 0;		/* set both operands to 0 */
		   2op = 0;
		   addMachCode(createMach(tempCod->address, group, opCode, 1op, 2op, 0));	/* add the command line to the machine code list */
		}

		else if((tempCod->command >= 0 && <= 3) || tempCod->command == 6) /* command is either: mov, cmp, add, sub, lea */
		{
		   group = 2;		/* the command is in the second group, with two operands */
		   switch(tempCod->op1addressMethod)	/* check origin operand addressing method */	
		   {
			case 1:	/* immediate number */
				1op = 0;		/* fix the operand addressing method to be the correct number required by the assembler */

				1opresult = atoi(tempCod->operand1) << 2;
				/* copy the immediate number with atoi, then shift it 2 times to get it to the right location */
				ARE = 0;		/* absolute */

			case 2: /* register */
				1op = 3;		/* fix the operand addressing method to be the correct number required by the assembler */

				1opresult = atoi(tempCod->operand1[1]) << 8;
				/* get the register number from the operand by looking at the 2nd letter, then shift it 8 times to get it to the right location*/
				ARE = 0;		/* absolute */

			case 3: /* register index */
				1op = 2;		/* fix the operand addressing method to be the correct number required by the assembler */

				1opresult = (atoi(tempCod->operand1[4]) << 2) + (atoi(tempCod->operand1[1]) << 8);
				/* shift the bits in the first and second register given by 2 (second register) and 8 (first register) to get them to the right location */
				ARE = 0;		/* absolute */

			case 4: /* variable */
				1op = 1;		/* fix the operand addressing method to be the correct number required by the assembler */

				if((tempSym = getLabel(tempCod->operand1)) != NULL)	/* if 1st operand is in symbol list */
				{
					if(tempSym->isExtern == false)
					{
						1opresult = (tempSym->address) << 2;	/* get the address of the symbol, shift it 2 times to get it to the right location */
						ARE = 2;	/* relocatable */
					}
					else
					{
						1opresult = 0 << 2;			/* if symbol is external, address should be 0 */
						addExt(createExt(tempSym->name, (tempCod->address)+1));	/* add the external symbol to the external list, to be written later to the external file, use "address+1" because we need the address following the original command */
						ARE = 1;	/* external */
					}
				}
				else
				{
					/* error: symbol is not in symbol list */
					/* ADD ERROR HANDLING */
				}

		   } /* end of first operand switch check */

		   1opARE = ARE; /* save 1st operand ERA status before checking 2nd operand and its ERA */

		   switch(tempCod->op2addressMethod)	/* check destination operand addressing method */	
		   {
			case 1:	/* immediate number */
				2op = 0;		/* fix the operand addressing method to be the correct number required by the assembler */

				2opresult = atoi(tempCod->operand2) << 2;
				/* copy the immediate number with atoi, then shift it 2 times to get it to the right location */
				ARE = 0;		/* absolute */

			case 2: /* register */
				2op = 3;		/* fix the operand addressing method to be the correct number required by the assembler */
				if(1op = 3) /* if both operands are registers, so only 1 word is required */
				{
					1opresult += atoi(tempCod->operand2[1]) << 2;
				}
				else
				{
					2opresult = atoi(tempCod->operand2[1]) << 2;
				/* get the register number from the operand by looking at the 2nd letter, then shift it 2 times to get it to the right location*/
				}
				ARE = 0;		/* absolute */

			case 3: /* register index */
				2op = 2;		/* fix the operand addressing method to be the correct number required by the assembler */

				2opresult = (atoi(tempCod->operand2[4]) << 2) + (atoi(tempCod->operand2[1]) << 8);
				/* shift the bits in the first and second register given by 2 (second register) and 8 (first register) to get them to the right location */
				ARE = 0;		/* absolute */

			case 4: /* variable */
				2op = 1;		/* fix the operand addressing method to be the correct number required by the assembler */

				if((tempSym = getLabel(tempCod->operand2)) != NULL)	/* if 2nd operand is in symbol list */
				{
					if(tempSym->isExtern == false)
					{
						2opresult = (tempSym->address) << 2;	/* get the address of the symbol, shift it 2 times to get it to the right location */
						ARE = 2;	/* relocatable */
					}
					else
					{
						2opresult = 0 << 2;			/* if symbol is external, address should be 0 */
						addExt(createExt(tempSym->name, (tempCod->address)+2));	/* add the external symbol to the external list, to be written later to the external file, use "address+2" because we need the address following the first operand */
						ARE = 1;	/* external */
					}
				}
				else
				{
					/* error: symbol is not in symbol list */
					/* ADD ERROR HANDLING */
				}
		   } /* end of second operand switch check */
		   addMachCode(createMach(tempCod->address, group, opCode, 1op, 2op, 0));	/* add the command line to the machine code list */
		   addMword(createMword((tempCod->address)+1, 1opresult+1opARE));		/* add the first operand information to the machine word list */
		   if((1op != 3) || 2op != 3)	/* if one of the operands isn't a register */
		   {
			addMword(createMword((tempCod->address)+2, 2opresult+2opARE));		/* add the second operand information to the machine word list */
		   }

		}
		else	/* command is either: not, clr, inc, dec, jmp, bne, red, prn, jsr */
		{
		   group = 1;			/* the command is in the third group, with only 1 operand */
		   1op = 0;			/* since only 1 operand is needed, set the origin operand to 0 */
		   switch(tempCod->op2addressMethod)		
		   {
			case 1:	/* immediate number */
				2op = 0;		/* fix the operand addressing method to be the correct number required by the assembler */

				2opresult = atoi(tempCod->operand2) << 2;
				/* copy the immediate number with atoi, then shift it 2 times to get it to the right location */
				ARE = 0;		/* absolute */

			case 2: /* register */
				2op = 3;		/* fix the operand addressing method to be the correct number required by the assembler */

				2opresult = atoi(tempCod->operand2[1]) << 8;
				/* get the register number from the operand by looking at the 2nd letter, then shift it 8 times to get it to the right location*/
				ARE = 0;		/* absolute */

			case 3: /* register index */
				2op = 2;		/* fix the operand addressing method to be the correct number required by the assembler */

				2opresult = (atoi(tempCod->operand2[4]) << 2) + (atoi(tempCod->operand2[1]) << 8);
				/* shift the bits in the first and second register given by 2 (second register) and 8 (first register) to get them to the right location */
				ARE = 0;		/* absolute */

			case 4: /* variable */
				2op = 1;		/* fix the operand addressing method to be the correct number required by the assembler */

				if((tempSym = getLabel(tempCod->operand2)) != NULL)	/* if 2nd operand is in symbol list */
				{
					if(tempSym->isExtern == false)
					{
						2opresult = (tempSym->address) << 2;	/* get the address of the symbol, shift it 2 times to get it to the right location */
						ARE = 2;	/* relocatable */
					}
					else
					{
						2opresult = 0 << 2;				/* if symbol is external, address should be 0 */
						addExt(createExt(label, (tempCod->address)+1));	/* add the external symbol to the external list, to be written later to the external file */
						ARE = 1;	/* external */
					}
				}
				else
				{
					/* error: symbol is not in symbol list */
					/* ADD ERROR HANDLING */					
				}
		   } /* end of operand switch check */
		addMachCode(createMach(tempCod->address, group, opCode, 1op, 2op, 0));	/* add the command line to the machine code list */
		addMword(createMword((tempCod->address)+1, 2opresult+ARE));		/* add the operand information to the machine word list */
		}


		
	   } 

	   else
	   {
		/* error: illegal command */
		/* ADD ERROR HANDLING */
	   }
	
	 
	}
	temp mCN = _machhead;
	while(temp != NULL)
	{
	    fprintf(fobs,"%s /n",temp->current->code);
	    temp = temp->next;
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
