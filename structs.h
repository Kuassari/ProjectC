#ifndef STRUCTS_H
#define STRUCTS_H

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


/*------------------- External Structure -------------------*/
typedef struct external * extp;
typedef struct external
{
	char name[MAX_LABEL_LENGTH];
	int address;
	extp next;
}ext;


/*------------------- Entry Structure -------------------*/
typedef struct entry * entp;
typedef struct entry
{
	char name[MAX_LABEL_LENGTH];
	int address;
	entp next;
}ent;


/*------------------- Code Structure Functions Declarations -------------------*/

/* create new data link of code and return a pointer to it */
codp createCod(int, int, char *, char *, int, int, int);

/* add new code to the list */
void addCodeNode(codp);

/* free memory allocation of codes */
void freeCodeList();

/* get the info of a specific code line by it's address, or NULL for error */
codp getCodeInfo(int);	


/* get the info of a specific code line by it's line number, or NULL for error */
codp LineGetCodeInfo(int);	

/*------------------- Data Structure Functions Declarations -------------------*/

/* create new data link of data and return a pointer to it */
datp createDat(int, int, char *, str_dat);

/* add new data line to the list */
void addData(datp);

/* free memory allocation of data list */
void freeDataList();

/* get the info of the data in the data list */
datp getDataInfo(int);

/*------------------- Symbols Structure Functions Declarations -------------------*/

/* create new data link of symbol and return a pointer to it */
symp createSym(char[MAX_LABEL_LENGTH], int, bool, act_inst);

/* add new symbol to the list */
void addSymbol(symp);

/* free memory allocation of symbols */
void freeSymbolList();

/* get the position in the linked list of a label  */
symp getLabel(char*);

/* get the address of a specific symbol by it's position in the list */
int getSymbolAddress(int);

/* update the address of the internal declared symbols at the end of the first read */
void updateSymbolAdress(int);

/*------------------- Machine Code Structure Functions Declarations -------------------*/

/* create new data link of symbol and return a pointer to it */
mCNp createMach(int, unsigned int, unsigned int, unsigned int, unsigned int, unsigned int);

/* add new symbol to the list */
void addMachCode(mCNp);

/* free memory allocation of machine code linked list */
void freeMachList();

/*------------------- Machine Word Structure Functions Declarations -------------------*/

/* create new data link of symbol and return a pointer to it */
mWNp createMword(int, unsigned int);

/* add new symbol to the list */
void addMword(mWNp);

/* free memory allocation of Machine words */
void freeMwordList();

/*------------------- Machine Data Structure Functions Declarations -------------------*/

/* create new data link of symbol and return a pointer to it */
mDNp createMdata(int, unsigned int);

/* add new machine data node to the list */
void addMdata(mDNp);

/* free memory allocation of Machine words */
void freeMdataList();

/*------------------- External Structure Functions Declarations -------------------*/

/* create new external node and return a pointer to it */
extp createExt(char[MAX_LABEL_LENGTH], int);

/* add new data line to the list */
void addExt(extp);

/* free memory allocation of data list */
void freeExtList();

/*------------------- Entry Structure Functions Declarations -------------------*/

/* create new external node and return a pointer to it */
entp createEnt(char *, int);

/* add new data line to the list */
void addEnt(entp);

/* free memory allocation of data list */
void freeEntList();

#endif
