/*
*
* Author: Ahmet KARACALI
* ID	  : 160101015
*
*       Problem: MY OWN CHARACTER HANDLING FUNCTIONS.
*
*
*/

#include <stdio.h>
#include <stdlib.h>


int isNumericChar(char x)
{
    if (x >= '0' && x <= '9') return 1;
    else return -1;

}
int isLowerChar(char x)
{
    if (x >= 'a' && x <= 'z') return 1;
    else return -1;

}
int isUpperChar(char x)
{
    if (x >= 'A' && x <= 'Z') return 1;
    else return -1;

}

int isSpace(char x)
{
    if (x ==' ') return 1;
    else return -1;

}

char toUpper ( char c ) {

    if ( c >= 'a' && c <= 'z')
    {
     c-=32;
     return c;
    }
    else return c;

}

char toLower ( char c ) {

    if ( c >= 'A' && c <= 'Z' )
    {
        c+=32;
    return c;
    }
    else return c;

}

int main()
{
    char character;

    printf("Please enter a character\n");
    scanf("%c",&character);

    printf("isLowerChar(%c) = %d\n",character,isLowerChar(character));
    printf("isUpperChar(%c) = %d\n",character,isUpperChar(character));
    printf("isNumericChar(%c) = %d\n",character,isNumericChar(character));
    printf("isSpace(%c) = %d\n",character,isSpace(character));
    printf("toLower(%c) = %c\n",character,toLower(character));
    printf("toUpper(%c) = %c\n",character,toUpper(character));

    return 0;
}
