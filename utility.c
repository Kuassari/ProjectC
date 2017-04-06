#include "common.h"

const char commands[16][4] = {"mov","cmp","add","sub","not","clr","lea","inc","dec","jmp","bne","red","prn","jsr","rts","stop"};

/*-------------------From Base 10 to Base 16-------------------*/

char HexChar [16] = { '0', '1', '2', '3', '4', '5', '6', '7',
                      '8', '9', 'A', 'B', 'C', 'D', 'E', 'F' };

static int * initHexArray (char * pDecStr, int * pnElements);
static void addDecValue (int * pMyArray, int nElements, int value);


/* start at the bottom of the array and work towards the top
 *
 * multiply the existing array value by 10, then add new value.
 * carry over remainder as you work back towards the top of the array
 */
static void addDecValue (int * pHexArray, int nElements, int value)
{
    int carryover = value;
    int tmp = 0;
    int i;

    for (i = (nElements-1); (i >= 0); i--)
    {
        tmp = (pHexArray[i] * 10) + carryover;
        pHexArray[i] = tmp % 16;
        carryover = tmp / 16;
    }
}

/* allocate an array of integer values to store intermediate results
 * only need as many as the input string as going from base 10 to
 * base 16 will never result in a larger number of digits, but for values
 * less than "16" will use the same number
 */
static int * initHexArray (char * pDecStr, int * pnElements)
{
    int * pArray = NULL;
    int lenDecStr = strlen (pDecStr);
    int i;

    pArray = (int *) calloc (lenDecStr,  sizeof (int));

    for (i = 0; i < lenDecStr; i++)
    {
        addDecValue (pArray, lenDecStr, pDecStr[i] - '0');
    }

    *pnElements = lenDecStr;

    return (pArray);
}



/*-------------------Error Table-------------------*/

/*
 * 100 - ':' is not part of lable
 * 101 - first letter invalid
 * 102 - lable length is too long
 * 103 - no more letters in the line
 * 104 - lable name already exists
 * 105 - missing expression after ':'
 * 106 - missing arguments
 * 107 - next word is not a string
 * 108 - line isn't empty after the string
 * 109 - missing '"' for the string
 * 110 - first word unknown
 * 111 - line isn't empty after external symbol name
 * 112 - error in operand information
 * 113 - destination operand is using illegal address method for the command
 * 114 - origin operand is using illegal address method for the command
 * 115 - no operand information recieved
 * 116 - unknown command
 * 117 - missing comma
 * 118 - first operand invalid
 * 119 - missing space between first operand and comma
 * 120 - illegal register number
 * 121 - missing bracket
 * 122 - first register must be an odd number
 * 123 - invalid char
 * 124 - invalid second operand
 * 125 - invalid firs operand
 * 126 - misplaced expression
 */


/* the function gets file name, line number and code error,
 * and print to stderr details that are rellavent to this specific error */
void errorFunction(char * sourceFile, int lineNum, int errorCode)
{
    switch(errorCode)
    {
        case 100:
                printf("error in line %d - ':' is not part of lable\n", lineNum);
                break;

        case 101:
                printf("error in line %d - first letter invalid\n", lineNum);
                break;

        case 102:
                printf("error in line %d - lable length is too long\n", lineNum);
                break;

        case 103:
                printf("error in line %d - no more letters in the line\n", lineNum);
                break;

        case 104:
                printf("error in line %d - lable name already exists\n", lineNum);
                break;

        case 105:
                printf("error in line %d - missing expression after ':'\n", lineNum);
                break;

        case 106:
                printf("error in line %d - missing arguments\n", lineNum);
                break;

        case 107:
                printf("error in line %d - next word is not a string\n", lineNum);
                break;

        case 108:
                printf("error in line %d - line isn't empty after the string\n", lineNum);
                break;

        case 109:
                printf("error in line %d - missing \" for the string\n", lineNum);
                break;

        case 110:
                printf("error in line %d - first word unknown\n", lineNum);
                break;

        case 111:
                printf("error in line %d - line isn't empty after external symbol name\n", lineNum);
                break;

        case 112:
                printf("error in line %d - error in operand information\n", lineNum);
                break;

        case 113:
                printf("error in line %d - destination operand is using illegal address method for the command\n", lineNum);
                break;

        case 114:
                printf("error in line %d - origin operand is using illegal address method for the command\n", lineNum);
                break;

        case 115:
                printf("error in line %d - no operand information recieved\n", lineNum);
                break;

        case 116:
                printf("error in line %d - unknown command\n", lineNum);
                break;

        case 117:
                printf("error in line %d - missing comma\n", lineNum);
                break;

        case 118:
                printf("error in line %d - first operand invalid\n", lineNum);
                break;

        case 119:
                printf("error in line %d - missing space between first operand and comma\n", lineNum);
                break;

        case 120:
                printf("error in line %d - illegal register number\n", lineNum);
                break;

        case 121:
                printf("error in line %d - missing bracket\n", lineNum);
                break;

        case 122:
                printf("error in line %d - first register must be an odd number\n", lineNum);
                break;

        case 123:
                printf("error in line %d - invalid char\n", lineNum);
                break;

        case 124:
                printf("error in line %d - invalid second operand\n", lineNum);
                break;

        case 125:
                printf("error in line %d - invalid firs operand\n", lineNum);
                break;

        case 126:
                printf("error in line %d - misplaced expression\n", lineNum);
                break;

        default:
                printf("error not found\n");
                break;
    }
}


/*------------------- -------------------*/


/* check if a given string is a command */
/* return its number if it is, or -1 if it's not */
int checkCMD(char * toCheck)
{
   int i;
   for(i = 0; i<COMMANDS_NUMBER; i++)
   {
	if(i == 15) 	/* for command "stop" we need to check 4 letters instead of 3 */
	{
		if(strncmp(commands[i],toCheck,4) == 0)
			return i;
	}
	else
	{
		if(strncmp(commands[i],toCheck,3) == 0)
			return i;
	}
   }

   return -1;
}
