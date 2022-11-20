/*******************************************************************
*
* Author: Ahmet KARACALI
* ID	  : 160101015
*
*   Problem:
*   Write a program that uses function strncmp
*   to compare two strings input by the user.
*   The program should input the number of characters
*   to be compared,then display whether the first string
*   is less than, equal to or greater than the second string.
*
*
********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main()
{

	char s1[100];
	char s2[100];
	int charComp=3;

    printf("Please enter two strings to compare:\n");
	scanf("%s %s", s1,s2);


	puts("Please enter how many characters to count: ");
	scanf("%d", &charComp);

    compareChar(s1,s2,charComp);

    return 0;
}

void compareChar(char s1[100],char s2[100],int charComp)
{

    if (!strncmp(s1,s2,charComp))
	{
		puts("Two strings are equal");
	}
	else if(strncmp(s1,s2,charComp)>0)
	{
		printf("%s > %s", s1,s2);
	}
	else
	{
		printf("%s < %s", s1,s2);

	}

}
