/*
*
* Author: Ahmet KARACALI
* ID	  : 160101015
*
*   Problem:
*    Write a program that uses random number generation to create sentences.
*   The program should use four arrays of pointers to char called article, noun, verb and preposition.
*   The program should create a sentence by selecting a word at random from each array in
*   the following order: article, noun, verb, preposition, article and noun. As each word is picked,
*   it should be concatenated to the previous words in an array large enough to hold the entire sentence.
*   The words should be separated by spaces. When the final sentence is output, it should start with a
*   capital letter and end with a period.
*
*
*/


#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include <string.h>
#include <ctype.h>

int main(void){

	char poem[200];
	char *ptrArticle[]={"the","a","one","some","any","this"};
	char *ptrNoun[]={"student","woman","man","kid","driver","teacher","lawyer"};
	char *ptrVerb[]={"jumped","ran","walked","studied","read","played","saw","spoken"};
	char *ptrPreposition[]={"to","from","over","under","on","near","between","with"};



    poemGenerator(poem,ptrPreposition,ptrVerb,ptrNoun,ptrArticle);

	getch();

}

void poemGenerator(char poem[200],char *ptrPreposition[],char *ptrVerb[],char *ptrNoun[],char *ptrArticle[])
{
    int i,j;
	srand(time(NULL));
    for(j=0;j<3;j++)
    {
    for (i = 0; i < 4; i++)
	{

		strcpy(poem,ptrArticle[rand()%4]);
		strcat(poem," ");
		strcat(poem,ptrNoun[rand()%5]);
		strcat(poem," ");
		strcat(poem,ptrVerb[rand()%5]);
		strcat(poem," ");
		strcat(poem,ptrPreposition[rand()%5]);
		strcat(poem," ");
		strcat(poem,ptrArticle[rand()%4]);
		strcat(poem," ");
		strcat(poem,ptrNoun[rand()%5]);
		strcat(poem,".");
		poem[0]=toupper(poem[0]);

		puts(poem);
	}
	printf("\n");
    }
}
