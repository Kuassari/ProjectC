#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_BUF 80
#define MAX_FILENAME 32

typedef enum{relocatable,external}rel_ex;

typedef struct symbols{
	char * name;
	rel_ex type;
	int value;
	*symbol next;
}
