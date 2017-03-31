#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sys/types.h"

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

void errorFunction(String sourceFile int lineNum, int errorCode)
{
    switch case(errorCode)
    {
        case 100:
                printf("':' is not part of lable\n")
                break;

        case 101:
                printf("first letter invalid\n");
                break;

        case 102:
                printf("lable length is too long\n");
                break;

        case 103:
                printf("no more letters in the line\n");
                break;

        case 104:
                printf("lable name already exists\n");
                break;

        case 105:
                printf("missing expression after ':'\n");
                break;

        case 106:
                printf("missing arguments\n");
                break;

        case 107:
                printf("next word is not a string\n");
                break;

        case 108:
                printf("line isn't empty after the string\n");
                break;

        case 109:
                printf("missing \" for the string\n");
                break;

        case 110:
                printf("first word unknown\n");
                break;

        case 111:
                printf("line isn't empty after external symbol name\n");
                break;

        case 112:
                printf("error in operand information\n");
                break;

        case 113:
                printf("destination operand is using illegal address method for the command\n");
                break;

        case 114:
                printf("origin operand is using illegal address method for the command\n");
                break;

        case 115:
                printf("no operand information recieved\n");
                break;

        case 116:
                printf("unknown command\n");
                break;

        case 117:
                printf("missing comma\n");
                break;

        case 118:
                printf("first operand invalid\n");
                break;

        case 119:
                printf("missing space between first operand and comma\n");
                break;

        case 120:
                printf("illegal register number\n");
                break;

        case 121:
                printf("missing bracket\n");
                break;

        case 122:
                printf("first register must be an odd number\n");
                break;

        case 123:
                printf("invalid char\n");
                break;

        case 124:
                printf("invalid second operand\n");
                break;

        case 125:
                printf("invalid firs operand\n");
                break;

        case 126:
                printf("misplaced expression\n");
                break;

        default:
                printf("error not found\n");
                break;
    }
}


/*------------------- -------------------*/


/* check if a given string is a command. 
 * return its number if it is, or -1 if it's not */
int checkCMD(char * toCheck)
{
   int i;
   for(i = 0; i<COMMANDS_NUMBER; i++)
	if(strncmp(commands[i],toCheck,3) == 0)
		return i;

   return -1;
}
