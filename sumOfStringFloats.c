/*
*
*
* Author: Ahmet KARACALI
* ID	  : 160101015
*
*	Problem:
*		Write a program that inputs four strings that represent
*    floating-point values, converts the strings to double values,
*    sums the values and prints the total of the four values.
*
*/


#include<stdio.h>
#include<string.h>
#include<stdlib.h>


int main()
{
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
	    double sum=0.0;

	    sum=strtod(a,NULL)+strtod(b,NULL)+strtod(c,NULL)+strtod(d,NULL);
		printf("\nSum is=%f",sum);

}

