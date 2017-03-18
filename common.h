/*------------------- Libraries-------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*------------------- Constant Variables -------------------*/

#define MAX_BUF 81
#define MAX_FILENAME 32
#define MAX_LABEL 31
#define COMMANDS_NUMBER 15


/*------------------- Global Variables -------------------*/

typedef enum{"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"}command;
char ** commands = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};


/*------------------- symbols structure -------------------*/
typedef enum{action,instruction}act_inst;
typedef struct symbols{
	char * name;
	char * address;
	bool isExtern;
	act_inst type;
	*symbol next;
}sym;

sym _head = NULL;

/*------------------- method structure -------------------*/
int checkCMD(char *)

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



/*------------------- code structure -------------------*/
typedef enum{action,instruction}act_inst;
typedef struct code
{
	char * command;
	char * operand1;
	char * operand2;
	int position;
	act_inst type;
	*cod next;
}cod;

/* initiallize the start position in the memory to 100 */
int IC = 100;





/*------------------- data structure -------------------*/
typedef enum{string,data}str_dat;
typedef struct data
{
	char * name;
	int position;
	str_data type;
	*dat next;
}dat;

/* initiallize the start position in the memory to 0 */
int DC = 0;
