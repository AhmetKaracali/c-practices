/*
*
* Author: Ahmet KARACALI
* ID	  : 160101015
*
*   Problem:
*    Write a program that uses function strcmp to compare two strings input
*   by the user. The program should state whether the first string is less than, equal to or greater
*   than the second string.
*
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void){

	char s1[100];
	char s2[100];


    printf("Please enter two strings to compare:\n");
	scanf("%s %s", s1,s2);


    CompareStr(s1,s2);

    return 0;
}

void CompareStr(char s1[100],char s2[100])
{

    if (!strcmp(s1,s2))
	{
		puts("Two strings are equal");
	}
	else if(strcmp(s1,s2)>0)
	{
		printf("%s > %s", s1,s2);
	}
	else
	{
		printf("%s < %s", s1,s2);

	}

}
