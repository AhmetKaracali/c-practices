/*
*
*
* Author: Ahmet KARACALI
* ID	  : 160101015
*
*	Problem:
*		Write a program that inputs four strings that represent integers,
*		converts the strings to integers, sums the values and prints the
*		total of the four values.
*
*/

#include <stdio.h>
#include<string.h>
#include <stdlib.h>

int main(void){

	char a[10];
	char b[10];
	char c[10];
	char d[10];



	printf("Please enter 4 strings and i will be print sum of them mathematically:");
	scanf(" %s %s %s %s", a, b, c, d);

	printSum(a,b,c,d);

	return 0;

}


void printSum(char *a[10],char *b[10],char *c[10],char *d[10])
{
		float sum=0.0;

		printf("\nSum is=%d", atoi(a)+atoi(b)+atoi(c)+atoi(d));

}
