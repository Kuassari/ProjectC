/*------------------- Libraries-------------------*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

/*------------------- Constant Variables -------------------*/

#define IC_FIRST_ADDRESS       	100
#define DC_FIRST_ADDRESS       	0
#define MAX_DATA_SIZE          	1000
#define MAX_BUF                	80
#define MAX_FILENAME           	32
#define MAX_LABEL_LENGTH       	30
#define WORD_LENGTH           	15
#define MAX_REGISTER_DIGIT     	7
#define BYTE_SIZE	       	8
#define ZERO_SIZE		1
#define UNUSED_SIZE		3
#define GROUP_SIZE		2
#define OPCODE_SIZE		4
#define OPERAND_SIZE		2
#define ERA_SIZE		2



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
	int address;
	int command;
	char * operand1;
	char * operand2;
	int op1addressMethod;
	int op2addressMethod;
	int lineNum;
	cod * next;
}cod;


cod _codhead = NULL;


/* create new data link of code and return a pointer to it */
cod * createCod(int address, int command, char * operand1, char * operand2, int op1addressMethod, int op2addressMethod, int lineNum)
{
	cod * newCod = (cod *)malloc(sizeof(cod));
	if(newCod = NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	newCod->address = address;
	newCod->command = command;
	newCod->operand1 = operand1;
	newCod->operand2 = operand2;
	newCod->op1addressMethod = op1addressMethod;
	newCod->op2addressMethod = op2addressMethod;
	newCod->lineNum = lineNum;
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

/* get the info of a specific code line by it's address, or NULL for error */
cod * getCodeInfo(int address)	
{
   cod temp = _codhead;
   while (temp!= NULL)
   {
	if(temp->address == address)
		return temp;
	else
		temp = temp->next;
   }

   return NULL;
}

/* get the info of a specific code line by it's line number, or NULL for error */
cod * LineGetCodeInfo(int lineNum)	
{
   cod temp = _codhead;
   while (temp!= NULL)
   {
	if(temp->lineNum == lineNum)
		return temp;
	else
		temp = temp->next;
   }

   return -1;
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
	newDat->type = type;
	newDat->next = NULL;

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

/* get the position in the linked list of a label  */
sym getLabel(char* labelName)
{
   int count = 0;
   sym temp = _symhead;
   while(temp != NULL)
   {
	if(strcmp(labelName, temp->name) == 0)
	   return temp;

	else
	{
	   temp = temp->next;
	}
   }
   return NULL;	/* return NULL to signal "labelName" isn't in symbol list */
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
typedef struct machineCodeNode{
	int address;
	mCU current;
	mCN * next;
}mCN;

typedef union {
	typedef struct machineCode
	{
		unsigned int ERA 	: ERA_SIZE;
		unsigned int destOp 	: OPERAND_SIZE;
		unsigned int originOp 	: OPERAND_SIZE;
		unsigned int opcode	: OPCODE_SIZE;
		unsigned int group	: GROUP_SIZE;
		unsigned int unused 	: UNUSED_SIZE;
		unsigned int ZERO	: ZERO_SIZE;		
	}mach;
	short int code;
}mCU;

mCN _machhead = NULL;


/* create new data link of symbol and return a pointer to it */
machineCodeUnion * createMach(int address, unsigned int group, unsigned int opcode, unsigned int originOp, unsigned int destOp, unsigned int ERA)
{
	int i;
	mCU * newMach = (mCU *)malloc(sizeof(mCU));
	if(newMach = NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	mCN * newMCN = (mCN *)malloc(sizeof*mcN));
	if(newMCN = NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	newMach->mach->ZERO = 0;		/* this bit is always 0 and is used to make converting to 16 bit easier */
	newMach->mach->unsued = 7;		/* these 3 bits are always 111 */
	newMach->mach->group = group;
	newMach->mach->opcode = opcode;
	newMach->mach->originOp = originOp;
	newMach->mach->destOp = destOp;
	newMach->mach->ERA = ERA;

	newMCN->address = address;
	newMCN->current = newMach;
	newMCN->next = NULL;

	return newMach; 
}

/* add new symbol to the list */
void addMachCode(mCN newMach)
{
   if(_machhead == NULL)
   {
	_machhead = newMach;
	newMach->next = NULL;
   }

   else
   {
	mCN temp = _machhead;
	while(temp->next != NULL)
		temp = temp->next;
	
	temp->next = newMach;
   }
   return;	
}

/* free memory allocation of machine code linked list */
void freeMachList()
{
   mCN temp = _machhead;
   while(temp != NULL)
   {
	_machhead = _machhead->next;
	free(temp);
	temp=_machhead;
   }	
}

/*------------------- Machine Word Structure -------------------*/
typedef struct machineWordNode{
	int address;
	mWU current;
	mWN * next;
}mWN;

typedef union {
	typedef struct machineWord
	{
		unsigned int ZERO	: ZERO_SIZE;
		unsigned int WORD	: WORD_LENGTH;
	}mword;
	short int word;
}mWU;


mWN _mwordhead = NULL;


/* create new data link of symbol and return a pointer to it */
mWN * createMword(int address, unsigned int word)
{
	mWU * newmWU = (mWU *)malloc(sizeof(mWU));
	if(newMU = NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	mWN * newMWN = (mWN *)malloc(sizeof(mWN));
	if(newMword = NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	newmWU->mword->ZERO = 0;		/* this bit is always 0 and is used to make converting to 16 bit easier */
	newmWU->mword->WORD = word;

	newmWU->address = address;	
	newMWN->next = NULL;

	return newMword; 
}

/* add new symbol to the list */
void addMword(mWN newMword)
{
   if(_mwordhead == NULL)
   {
	_mwordhead = newMword;
	newMword->next = NULL;
   }

   else
   {
	mWN temp = _mwordhead;
	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = newMword;
   }
   return;	
}

/* free memory allocation of Machine words */
void freeMwordList()
{
   mWN temp = _mwordhead;
   while(temp != NULL)
   {
	_mwordhead = _mwordhead->next;
	free(temp);
	temp=_mwordhead;
   }	
}

/*------------------- External Structure -------------------*/
typedef struct external
{
	char[MAX_LABEL_LENGTH] name;
	int address;
	ext * next;
}ext;

ext _exthead = NULL;


/* create new external node and return a pointer to it */
ext * createExt(char * name, int address)
{
	ext * newExt = (ext *)malloc(sizeof(ext));
	if(newExt = NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}

	newExt->name = name;
	newExt->address = address;
	newExt->next = NULL;

	return newExt; 
}

/* add new data line to the list */
void addExt(ext newExt)
{
   if(_exthead == NULL)
   {
	_dexthead = newExt;
	newExt->next = NULL;
   }

   else
   {
	ext temp = _exthead;
	while(temp->next != NULL)
		temp = temp->next;
	
	temp->next = newExt;
   }
   return;	
}

/* free memory allocation of data list */
void freeExtList()
{
   ext temp = _exthead;
   while(temp != NULL)
   {
	_exthead = _exthead->next;
	free(temp);
	temp = _exthead;
   }	
}

/*------------------- Entry Structure -------------------*/
typedef struct entry
{
	char[MAX_LABEL_LENGTH] name;
	int address;
	ext * next;
}ent;

ent _enthead = NULL;


/* create new external node and return a pointer to it */
ent * createEnt(char * name, int address)
{
	ent * newEnt = (ent *)malloc(sizeof(ent));
	if(newEnt = NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}

	newEnt->name = name;
	newEnt->address = address;
	newEnt->next = NULL;

	return newEnt; 
}

/* add new data line to the list */
void addEnt(ent newEnt)
{
   if(_exthead == NULL)
   {
	_dexthead = newExt;
	newExt->next = NULL;
   }

   else
   {
	ent temp = _enthead;
	while(temp->next != NULL)
		temp = temp->next;
	
	temp->next = newEnt;
   }
   return;	
}

/* free memory allocation of data list */
void freeEntList()
{
   ent temp = _enthead;
   while(temp != NULL)
   {
	_enthead = _enthead->nent;
	free(temp);
	temp = _enthead;
   }	
}
