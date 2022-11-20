/*
*
* Author: Ahmet KARACALI
* ID	  : 160101015
*
*   Problem:Write a program that encodes English-language phrases into pig Latin. Pig Latin
*   is a form of coded language often used for amusement. Many variations exist in the methods used
*   to form pig-Latin phrases.
*
*
*/

#include <stdio.h>
#include <string.h>

void printLatinWord(char *);

int main()
{
	char myString[100];
	char *ptr;
	char *pigPtr;

	puts("Please enter a string and I will make it Latino :D : ");
	scanf("%s",myString);

	ptr=strtok(myString," ");

	while (ptr!=NULL)
	{
		printf("\nThe sentence BEFORE i make it latino:\n");
		printf("%s\n\n", myString);

		printf("The sentence AFTER i make it latino:\n");
		printLatinWord(ptr);
		ptr=strtok(NULL, " ");

		if (ptr!=NULL)
		{
			printf(" ");
		}

	}

	getch();

}

void printLatinWord(char *ptr){

	int i;
	for (i = 1; i < strlen(ptr); i++)
	{
		printf("%c", ptr[i]);
	}
	printf("%c%s", ptr[0],"ay");

}
