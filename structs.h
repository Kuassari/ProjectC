#include "common.h"

/*------------------- Code Structure -------------------*/
typedef struct code * codp;
typedef struct code
{
	int address;
	int command;
	char * operand1;
	char * operand2;
	int op1addressMethod;
	int op2addressMethod;
	int lineNum;
	codp next;
}cod;


codp _codhead = NULL;


/* create new data link of code and return a pointer to it */
codp createCod(int address, int command, char * operand1, char * operand2, int op1addressMethod, int op2addressMethod, int lineNum)
{
	codp newCod = (codp)malloc(sizeof(cod));
	if(newCod == NULL)
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
void addCodeNode(codp newCod)
{
   if(_codhead == NULL)
   {
	_codhead = newCod;
	newCod->next = NULL;
   }

   else
   {
	codp temp = _codhead;
	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = newCod;
   }
   return;	
}

/* free memory allocation of codes */
void freeCodeList()
{
   codp temp;
   codp node = _codhead;
   while(node != NULL)
   {
	temp = node;
	node = node->next;
	free(temp);
   }	
   free(_codhead);
}

/* get the info of a specific code line by it's address, or NULL for error */
codp getCodeInfo(int address)	
{
   codp temp = _codhead;
   while (temp != NULL)
   {
	if(temp->address == address)
		return temp;
	else
		temp = temp->next;
   }

   return NULL;
}

/* get the info of a specific code line by it's line number, or NULL for error */
codp LineGetCodeInfo(int lineNum)	
{
   codp temp = _codhead;
   while (temp != NULL)
   {
	if(temp->lineNum == lineNum)
		return temp;
	else
		temp = temp->next;
   }

   return NULL;
}
/*------------------- Data Structure -------------------*/
typedef enum {string, data} str_dat;
typedef struct data * datp;
typedef struct data
{
	int address;
	int value;
	char * name;
	str_dat type;
	datp next;
}dat;

datp _dathead = NULL;


/* create new data link of data and return a pointer to it */
datp createDat(int address, int value, char * name, str_dat type)
{
	datp newDat = (datp)malloc(sizeof(dat));
	if(newDat == NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	newDat->address = address;
	newDat->value = value;
	newDat->name = name;
	newDat->type = type;
	newDat->next = NULL;

	return newDat; 
}

/* add new data line to the list */
void addData(datp newDat)
{
   if(_dathead == NULL)
   {
	_dathead = newDat;
	newDat->next = NULL;
   }

   else
   {
	datp temp = _dathead;
	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = newDat;
   }
   return;	
}

/* free memory allocation of data list */
void freeDataList()
{
   datp temp;
   datp node = _dathead;
   while(node != NULL)
   {
	temp = node;
	node = node->next;
	free(temp);
   }	
   free(_dathead);
}

/* get the info of the data in the data list */
datp getDataInfo(int address)
{
   datp temp = _dathead;
   while(temp != NULL)
   {
	if(temp->address == address)
	   return temp;

	else
	{
	   temp = temp->next;
	}
   }
   return NULL;
}


/*------------------- Symbols Structure -------------------*/
typedef enum{action,instruction}act_inst;
typedef struct symbols * symp;
typedef struct symbols
{
	char name[MAX_LABEL_LENGTH];	/* the name of the lable */
	int address;			/* the address of the label */
	bool isExtern;			/* extern = true, not extern = false */
	act_inst type;			/* action or instruction statement flag */
	symp next;			/* next symbol in the linkedlist */
}sym;

symp _symhead = NULL;


/* create new data link of symbol and return a pointer to it */
symp createSym(char name[MAX_LABEL_LENGTH], int add, bool isExt, act_inst type)
{
	symp newSym = (symp)malloc(sizeof(sym));
	if(newSym == NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	strcpy(newSym->name,name);
	newSym->address = add;
	newSym->isExtern = isExt;
	newSym->type = type;
	newSym->next = NULL;

	return newSym; 
}

/* add new symbol to the list */
void addSymbol(symp newSym)
{
   if(_symhead == NULL)
   {
	_symhead = newSym;
	newSym->next = NULL;
   }

   else
   {
	symp temp = _symhead;
	while(temp->next != NULL)
		temp = temp->next;
	
	temp->next = newSym;
   }
   return;	
}

/* free memory allocation of symbols */
void freeSymbolList()
{
   symp temp;
   symp node = _symhead;
   while(node != NULL)
   {
	temp = node;
	node = node->next;
	free(temp);
   }	
   free(_symhead);
}

/* get the position in the linked list of a label  */
symp getLabel(char* labelName)
{
   symp temp = _symhead;
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
   symp temp = _symhead;
   int count = 0;
   while(count < position)
	temp = temp->next;

   return temp->address;
}

/* update the address of the internal declared symbols at the end of the first read */
void updateSymbolAdress(int IC)
{
   symp temp = _symhead;
   while(temp != NULL)
   {
	if((temp->type == instruction) && (temp->isExtern == false))
	{
	   temp->address += IC;
	}
	temp = temp->next;
   }
}



/*------------------- Machine Code Structure -------------------*/
typedef struct machineCodeNode * mCNp;

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

typedef union machineCodeUnion{
	mach bits;
	short int code;
}mCU;

typedef struct machineCodeNode{
	int address;
	mCU current;
	mCNp next;
}mCN;

mCNp _machhead = NULL;


/* create new data link of symbol and return a pointer to it */
mCNp createMach(int address, unsigned int group, unsigned int opcode, unsigned int originOp, unsigned int destOp, unsigned int ERA)
{
	mCU * newMach = (mCU *)malloc(sizeof(mCU));
	mCNp newMCN = (mCNp)malloc(sizeof(mCN));
	if(newMach == NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	if(newMCN == NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	newMach->bits.ZERO = 0;			/* this bit is always 0 and is used to make converting to hexadecimal easier */
	newMach->bits.unused = 7;		/* these 3 bits are always 111 */
	newMach->bits.group = group;
	newMach->bits.opcode = opcode;
	newMach->bits.originOp = originOp;
	newMach->bits.destOp = destOp;
	newMach->bits.ERA = ERA;

	newMCN->address = address;
	newMCN->current = *newMach;
	newMCN->next = NULL;

	return newMCN; 
}

/* add new symbol to the list */
void addMachCode(mCNp newMach)
{
   if(_machhead == NULL)
   {
	_machhead = newMach;
	newMach->next = NULL;
   }

   else
   {
	mCNp temp = _machhead;
	while(temp->next != NULL)
		temp = temp->next;
	
	temp->next = newMach;
   }
   return;	
}

/* free memory allocation of machine code linked list */
void freeMachList()
{
   mCNp temp;
   mCNp node = _machhead;
   while(node != NULL)
   {
	temp = node;
	node = node->next;
	free(temp);
   }	
   free(_machhead);
}

/*------------------- Machine Word Structure -------------------*/
typedef struct machineWordNode * mWNp;
typedef struct machineWord
{
	unsigned int ZERO	: ZERO_SIZE;
	unsigned int WORD	: WORD_LENGTH;
}mword;

typedef union machineWordUnion{
	mword bits;
	short int word;
}mWU;

typedef struct machineWordNode{
	int address;
	mWU current;
	mWNp next;
}mWN;

mWNp _mwordhead = NULL;


/* create new data link of symbol and return a pointer to it */
mWNp createMword(int address, unsigned int word)
{
	mWU * newmWU = (mWU *)malloc(sizeof(mWU));
	mWNp newmWN = (mWNp)malloc(sizeof(mWN));
	if(newmWU == NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	if(newmWN == NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}
	newmWU->bits.ZERO = 0;		/* this bit is always 0 and is used to make converting to 16 bit easier */
	newmWU->bits.WORD = word;

	newmWN->address = address;
	newmWN->current = *newmWU;	
	newmWN->next = NULL;

	return newmWN;
}

/* add new symbol to the list */
void addMword(mWNp newMword)
{
   if(_mwordhead == NULL)
   {
	_mwordhead = newMword;
	newMword->next = NULL;
   }

   else
   {
	mWNp temp = _mwordhead;
	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = newMword;
   }
   return;	
}

/* free memory allocation of Machine words */
void freeMwordList()
{
   mWNp temp;
   mWNp node = _mwordhead;
   while(node != NULL)
   {
	temp = node;
	node = node->next;
	free(temp);
   }	
   free(_mwordhead);
}

/*------------------- Machine Data Structure -------------------*/
typedef struct machineDataNode * mDNp;
typedef struct machineData
{
	unsigned int ZERO	: ZERO_SIZE;
	unsigned int DATA	: WORD_LENGTH;
}mdata;

typedef union machineDataUnion
{
	mdata bits;
	short int data;
}mDU;

typedef struct machineDataNode
{
	int address;
	mDU current;
	mDNp next;
}mDN;

mDNp _mdatahead = NULL;


/* create new data link of symbol and return a pointer to it */
mDNp createMdata(int address, unsigned int data)
{
	mDNp newmDN = (mDNp)malloc(sizeof(mDN));
	mDU * newmDU = (mDU *)malloc(sizeof(mDU));
	if(newmDN == NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	   return;
	}
	if(newmDU == NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	   return;
	}
	newmDU->bits.ZERO = 0;		/* this bit is always 0 and is used to make converting to 16 bit easier */
	newmDU->bits.DATA = data;

	newmDN->address = address;
	newmDN->current = *newmDU;	
	newmDN->next = NULL;

	return newmDN; 
}

/* add new machine data node to the list */
void addMdata(mDNp newMdata)
{
   if(_mdatahead == NULL)
   {
	_mdatahead = newMdata;
	newMdata->next = NULL;
   }

   else
   {
	mDNp temp = _mdatahead;
	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = newMdata;
   }
   return;	
}

/* free memory allocation of Machine words */
void freeMdataList()
{
   mDNp temp;
   mDNp node = _mdatahead;
   while(node != NULL)
   {
	temp = node;
	node = node->next;
	free(temp);
   }	
   free(_mdatahead);
}

/*------------------- External Structure -------------------*/
typedef struct external * extp;
typedef struct external
{
	char name[MAX_LABEL_LENGTH];
	int address;
	extp next;
}ext;

extp _exthead = NULL;


/* create new external node and return a pointer to it */
extp createExt(char name[MAX_LABEL_LENGTH], int address)
{
	extp newExt = (extp)malloc(sizeof(ext));
	if(newExt == NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}

	strcpy(newExt->name,name);
	newExt->address = address;
	newExt->next = NULL;

	return newExt; 
}

/* add new data line to the list */
void addExt(extp newExt)
{
   if(_exthead == NULL)
   {
	_exthead = newExt;
	newExt->next = NULL;
   }

   else
   {
	extp temp = _exthead;
	while(temp->next != NULL)
		temp = temp->next;
	
	temp->next = newExt;
   }
   return;	
}

/* free memory allocation of data list */
void freeExtList()
{
   extp node = _exthead;
   extp temp;
   while(node != NULL)
   {
	temp = node;
	node = node->next;
	free(temp);
   }
   free(_exthead);
}

/*------------------- Entry Structure -------------------*/
typedef struct entry * entp;
typedef struct entry
{
	char name[MAX_LABEL_LENGTH];
	int address;
	entp next;
}ent;

entp _enthead = NULL;


/* create new external node and return a pointer to it */
entp createEnt(char * name, int address)
{
	entp newEnt = (entp)malloc(sizeof(ent));
	if(newEnt == NULL)
	{
	   /* error: not enough memory */
	   /* ADD ERROR HANDLING */
	}

	strcpy(newEnt->name,name);
	newEnt->address = address;
	newEnt->next = NULL;

	return newEnt; 
}

/* add new data line to the list */
void addEnt(entp newEnt)
{
   if(_enthead == NULL)
   {
	_enthead = newEnt;
	newEnt->next = NULL;
   }

   else
   {
	entp temp = _enthead;
	while(temp->next != NULL)
		temp = temp->next;
	
	temp->next = newEnt;
   }
   return;	
}

/* free memory allocation of data list */
void freeEntList()
{
   entp node = _enthead;
   entp temp;
   while(node != NULL)
   {
	temp = node;
	node = node->next;
	free(temp);
   }
   free(_enthead);
}
