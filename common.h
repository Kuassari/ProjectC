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

#define SOURCE_FILE .as
#define OBJ_FILE .ob
#define EXT_FILE .ext
#define ENTRY_FILE .ent
#define COMMENT_SIGN ';'
#define STRING_SIGN '"'
#define DATA_WORD ".data"
#define STRING_WORD ".string"
#define ENTRY_WORD ".entry"
#define EXTERN_WORD ".extern"
#define NEWLINE '\n'
#define LABEL_SIGN ':'
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

char ** commands = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};

/*----------------- Functions Declaration -----------------*/

int checkCMD(char *)




/*------------------- Code Structure -------------------*/
typedef struct code
{
	int position;
	int command;
	char * operand1;
	char * operand2;
	int op1addressMethod;
	int op2addressMethod;
	cod * next;
}cod;


cod _codhead = NULL;


/* create new data link of code and return a pointer to it */
cod * createCod(int position, int command, char * operand1, char * operand2, int op1addressMethod, int op2addressMethod)
{
	cod * newCod = (cod *)malloc(sizeof(cod));
	if(newCod = NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	newCod->position = position;
	newCod->command = command;
	newCod->operand1 = operand1;
	newCod->operand2 = operand2;
	newCod->op1addressMethod = op1addressMethod;
	newCod->op2addressMethod = op2addressMethod;
	newCod->next = NULL;

	return newCod; 
}

/* add new code to the list */
void addCodeNode(cod newCod)
{
   if(_codhead == NULL)
   {
	_codhead = newCod;
	newCod->next = NULL;
   }

   else
   {
	cod temp = _codhead;
	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = newCod;
   }
   return;	
}

/* free memory allocation of codes */
void freeCodeList()
{
   cod temp = _codhead;
   while(_codhead != NULL)
   {
	_codhead = _codhead->next;
	free(temp);
	temp=_codhead;
   }	
}

/* get the Label at the list code table */
int getLabel(char* labelName)
{
   int count = 0;
   cod temp = _codhead;
   while(_codhead != NULL)
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

/* get the address of a specific code line by it's position in the list */
cod * getCodeInfo(int position)	
{
   cod temp = _codhead;
   while (temp!= NULL)
   {
	if(temp->
   }
}

/*------------------- Data Structure -------------------*/
typedef enum{string,data}str_dat;
typedef struct data
{
	int position;
	int value;
	char * name;
	str_data type;
	*dat next;
}dat;

dat _dathead = NULL;


/* create new data link of data and return a pointer to it */
dat * createDat(int position, int value, char * name, str_data type)
{
	dat * newDat = (dat *)malloc(sizeof(dat));
	if(newDat = NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	newDat->position = position;
	newDat->value = value;
	newDat->name = name;
	newSym->type = type;
	newSym->next = NULL;

	return newDat; 
}

/* add new data line to the list */
void addData(dat newDat)
{
   if(_dathead == NULL)
   {
	_dathead = newDat;
	newDat->next = NULL;
   }

   else
   {
	dat temp = _dathead;
	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = newDat;
   }
   return;	
}

/* free memory allocation of data list */
void freeDataList()
{
   dat temp = _dathead;
   while(_dathead != NULL)
   {
	_dathead = _dathead->next;
	free(temp);
	temp=_dathead;
   }	
}

/* get the position of the data in the data list */
int getData(char* dataName)
{
   int count = 0;
   dat temp = _dathead;
   while(_dathead != NULL)
   {
	if(strcmp(dataName, temp->name) == 0)
	   return count;

	else
	{
	   count++;
	   temp = temp->next;
	}
   }
   return -1;
}


/*------------------- Symbols Structure -------------------*/
typedef enum{action,instruction}act_inst;
typedef struct symbols
{
	char name[MAX_LABLE_LENGTH];	/* the name of the lable */
	int address;			/* the address of the label */
	bool isExtern;			/* extern = true, not extern = false */
	act_inst type;			/* action or instruction statement flag */
	sym * next;			/* next symbol in the linkedlist */
}sym;

sym _symhead = NULL;


/* create new data link of symbol and return a pointer to it */
sym * createSym(char * name, int add, bool isExt, act_inst type)
{
	sym * newSym = (sym *)malloc(sizeof(sym));
	if(newSym = NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
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
   if(_symhead == NULL)
   {
	_symhead = newSym;
	newSym->next = NULL;
   }

   else
   {
	sym temp = _symhead;
	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = newSym;
   }
   return;	
}

/* free memory allocation of symbols */
void freeSymbolList()
{
   sym temp = _symhead;
   while(_symhead != NULL)
   {
	_symhead = _symhead->next;
	free(temp);
	temp=_symhead;
   }	
}

/* get the Label at the list symbol table */
int getLabel(char* labelName)
{
   int count = 0;
   sym temp = _symhead;
   while(_symhead != NULL)
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
int getSymbolAddress(int position)	
{
   sym temp = _symhead;
   int count = 0;
   while(count < position)
	temp = temp->next;

   return temp->address;
}

/* update the address of the internal declared symbols at the end of the first read */
void updateSymbolAdress(int IC)
{
   sym temp = _symhead;
   while(temp != NULL)
   {
	if((temp->act_inst == instruction) && (temp->isExtern == false))
	{
	   temp->address += IC;
	}
	temp = temp->next;
   }
}



/*------------------- Machine Code Structure -------------------*/
typedef struct machineCode
{
	int address;
	int[WORD_LENGTH] code_array;
	mach * next;
}mach;

mach _machhead = NULL;


/* create new data link of symbol and return a pointer to it */
mach * createMach(int address, )
{
	int i;
	mach * newMach = (mach *)malloc(sizeof(mach));
	if(newMach = NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}

	for(i=0;i<WORD_LENGTH;i++)	/* reset each initial code word to 0*/
	{
	   newMach->code_array[i] = 0;	
	}

	newMach->address = address;
	newMach->next = NULL;

	return newMach; 
}

/* add new symbol to the list */
void addMachCode(mach newMach)
{
   if(_machhead == NULL)
   {
	_machhead = newMach;
	newMach->next = NULL;
   }

   else
   {
	mach temp = _machhead;
	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = newMach;
   }
   return;	
}

/* free memory allocation of symbols */
void freeMachList()
{
   mach temp = _machhead;
   while(_machhead != NULL)
   {
	_machhead = _machhead->next;
	free(temp);
	temp=_machhead;
   }	
}

/* get the address of a specific symbol by it's position in the list */
char* getAddress(int position)	
{
   mach temp = _machhead;
   int count = 0;
   while(count < position)
	temp = temp->next;

   return temp->address;
}
