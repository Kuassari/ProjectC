#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_BUF 80
#define MAX_FILENAME 32

typedef enum{action,instruction}act_inst;

typedef struct symbols{
	char * name;
	char * address;
	bool isExtern;
	act_inst type;
	*symbol next;
}sym;

sym _head = NULL;

void addSymbol(){
   if(_head == NULL){
	_head = newsym;
	newsym->next = NULL;
   }
   else{
	sym temp = _head;
	while(temp->next!=NULL)
		temp = temp->next;
	
	temp->next = newsym;
   }
   return;	
}

void freeList(){
   sym temp = _head;
   while(_head != NULL)
   {
	_head = head->next;
	free(temp);
	temp=_head;
   }	
}

int getLabel(char* labelName){
   int count = 0;
   sym temp = _head;
   while(_head != NULL){
	if(strcmp(labelName, temp->name) == 0){
	   return count;
	}
	else{
	   count++;
	   temp = temp->next;
	}
   }
   return -1;
}

char* getAddress(int position){
   sym temp = _head;
   int count = 0;
   while(count < position){
	temp = temp->next;
   }
   return temp->address;
}
