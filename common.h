/*------------------- Libraries-------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*------------------- Constant Variables -------------------*/

#define IC_FIRST_ADDRESS       100
#define DC_FIRST_ADDRESS       0
#define MAX_DATA_SIZE          1000
#define MAX_BUF                80
#define MAX_FILENAME           32
#define MAX_LABEL_LENGTH       30
#define WORD_LENGTH            15
#define MAX_REGISTER_DIGIT     7
#define BYTE_SIZE	       8

/*------------------- String constants -------------------*/

#define COMMENT_SIGN ';'
#define NEWLINE '\n'
#define LABEL_FLAG ':'
#define STR_FLAG '"'
#define IMD_FLAG '#'
#define REG_FLAG 'r'
#define COMMA ','
#define SPACE ' '
#define PLUS '+'
#define MINUS '-'
#define LEFT_BRACKET '['
#define RIGHT_BRACKET ']'

/*------------------- Global Variables -------------------*/

int IC = IC_FIRST_ADDRESS;
int DC = DC_FIRST_ADDRESS;

typedef enum{"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"}command;
char ** commands = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};

/*----------------- Functions Declaration -----------------*/

int checkCMD(char *)




/*------------------- Code Structure -------------------*/
typedef struct code
{
	char * command;
	char * operand1;
	char * operand2;
	int position;
	act_inst type;
	*cod next;
}cod;



/*------------------- Data Structure -------------------*/
typedef enum{string,data}str_dat;
typedef struct data
{
	char * name;
	int position;
	str_data type;
	*dat next;
}dat;



/*------------------- Symbols Structure -------------------*/
typedef enum{action,instruction}act_inst;
typedef struct symbols
{
	char name[MAX_LABLE_LENGTH];	/* the name of the lable */
	int address;			/* the address of the lable */
	bool isExtern;			/* extern = true, not extern = false */
	act_inst type;			/* action or instruction statment flag */
}sym;

sym _head = NULL;


/* create new data link of symbol and return a pointer to it */
sym * createSym(char * name, char * add, bool isExt, act_inst type)
{
	sym * newSym = (sym *)malloc(sizeof(sym));
	newSym->name = name;
	newSym->address = add;
	newSym->isExtern = isExt;
	newSym->type = type;
	newSym->next = NULL;

	return newSym; 
}

/* add new symbol to the list */
void addSymbol(sym newSym)
{
   if(_head == NULL)
   {
	_head = newSym;
	newSym->next = NULL;
   }

   else
   {
	sym temp = _head;
	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = newSym;
   }
   return;	
}

/* free memory allocation of symbols */
void freeSymbolList()
{
   sym temp = _head;
   while(_head != NULL)
   {
	_head = head->next;
	free(temp);
	temp=_head;
   }	
}

/* get the Label at the list symbol table */
int getLabel(char* labelName)
{
   int count = 0;
   sym temp = _head;
   while(_head != NULL)
   {
	if(strcmp(labelName, temp->name) == 0)
	   return count;

	else
	{
	   count++;
	   temp = temp->next;
	}
   }
   return -1;
}

/* get the address of a specific symbol by it's position in the list */
char* getAddress(int position)	
{
   sym temp = _head;
   int count = 0;
   while(count < position)
	temp = temp->next;

   return temp->address;
}



