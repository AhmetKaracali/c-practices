/*
*   Author:Ahmet KARACALI
*   Due Date: 14.05.2017
*   CEN108 Homework 3 - Student Database System
*
*/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct
{
    char firstname[20];
    char lastname[20];
    char Gender[1];
    int math[1];
    int comp[1];
    int secret;
}student;

void AddStd()
{
    FILE *fp;
       printf("\nPlease enter student details:\n\n");

       printf("\nFirst Name:");
       scanf("%s",student.firstname);
       printf("\nLast Name:");
       scanf("%s",student.lastname);
       printf("\nGender ( M or F ): ");
       scanf("%s",student.Gender);
       printf("\nMath Score: ");
       scanf("%s",student.math);
        printf("\nComputer Score: ");
       scanf("%s",student.comp);

       fp=fopen("studentDatabase.txt","a+");
       fprintf(fp,"\n%s\t%s\t%s\t%s\t%s\t",student.firstname,student.lastname,student.Gender,student.math,student.comp);
       fclose(fp);
}

void FindStd()
{
    FILE *fp;
    int compare=0,found;

    char firstName[20],lastName[20];
       printf("\nEnter student's first name: ");
       scanf("%s",&firstName);
       printf("\nEnter student's last name: ");
       scanf("%s",&lastName);

       printf("Searching record for %s %s...\n",firstName,lastName);
           found=0;
           if((fp=fopen("studentDatabase.txt","r"))==NULL)
        {
            printf(" Sorry! The File is empty.\n\n");
        }
        else
        {
            while(!feof(fp)&& found==0)
                {
                fscanf(fp,"\n%s\t%s\t%c\t%s\t%s\t",student.firstname,student.lastname,student.Gender,student.math,student.comp);
                compare = strcmp(student.firstname,firstName);
                if(strlen(student.firstname)==strlen(firstName))
                {
                    if(strlen(student.lastname)==strlen(lastName))
                {
                        found=1;
                }
                }

            }
            }
       if(found)
       {
         printf("\nThe student found...");
         printf("\nFirst Name:%s\nLast Name:%s\nGender:%s\nMath Score:%s\nComputer Score:%s\n",student.firstname,student.lastname,student.Gender,student.math,student.comp);
        getch();
       }
       else
       {
         printf("Can not found anything about %s %s.\n",student.firstname,student.lastname);
         getch();
       }
}

void deleteStd()
{
    FILE *fp;
    FILE *tempfp;
    int compare=0,found;

    char firstName[20],lastName[20];
       printf("\nEnter student's first name: ");
       scanf("%s",&firstName);
       printf("\nEnter student's last name: ");
       scanf("%s",&lastName);

       printf("Searching record for %s %s...\n",firstName,lastName);
           found=0;
           tempfp=fopen("Temporary.txt","a");
           if((fp=fopen("studentDatabase.txt","r"))==NULL)
        {
            printf(" Sorry! File is empty.\n\n");
        }
        else
        {
            while(!feof(fp))
                {
                fscanf(fp,"\n%s\t%s\t%c\t%s\t%s\t",student.firstname,student.lastname,student.Gender,student.math,student.comp);
                compare = strcmp(student.firstname,firstName);
                if(strlen(student.firstname)==strlen(firstName))
                {
                    if(strlen(student.lastname)==strlen(lastName))
                {
                found=1;
                }
                }
                else
                {
                    fprintf(tempfp,"\n%s\t%s\t%s\t%s\t%s\t",student.firstname,student.lastname,student.Gender,student.math,student.comp);
                }

            }
            }
       if(found)
       {
         printf("\nThe record is found.");
        fclose(fp);
        fclose(tempfp);
        remove("studentDatabase.txt");
        rename("Temporary.txt","studentDatabase.txt");
        printf("\nThe Student is deleted.");

        getch();
       }
       else
       {
         printf("The Student does not exists.\n");
         getch();
       }
}

void updateStd()
{
   FILE *fp;
    FILE *tempfp;
    int compare=0,found;

    char firstName[20],lastName[20];
       printf("\nEnter student's first name: ");
       scanf("%s",&firstName);
       printf("\nEnter student's last name: ");
       scanf("%s",&lastName);

       printf("Searching record for %s %s...\n",firstName,lastName);
           found=0;
           tempfp=fopen("Temporary.txt","a");
           if((fp=fopen("studentDatabase.txt","r"))==NULL)
        {
            printf(" Sorry! File is Empty...\n\n");
        }
        else
        {
            while(!feof(fp))
                {
                fscanf(fp,"\n%s\t%s\t%c\t%s\t%s\t",student.firstname,student.lastname,student.Gender,student.math,student.comp);
                compare = strcmp(student.firstname,firstName);
                if(strlen(student.firstname)==strlen(firstName))
                {
                    if(strlen(student.lastname)==strlen(lastName))
                {
                found=1;
                }
                }
                else
                {
                    fprintf(tempfp,"\n%s\t%s\t%s\t%s\t%s\t",student.firstname,student.lastname,student.Gender,student.math,student.comp);
                }

            }
            }
       if(found)
       {
        printf("Please enter new details for student '%s %s'\n",student.firstname,student.lastname);
       printf("\nGender ( M or F ): ");
       scanf("%s",student.Gender);
       printf("\nMath Score: ");
       scanf("%s",student.math);
        printf("\nComputer Score: ");
       scanf("%s",student.comp);

       fprintf(tempfp,"\n%s\t%s\t%s\t%s\t%s\t",firstName,lastName,student.Gender,student.math,student.comp);
        fclose(fp);
        fclose(tempfp);
        remove("studentDatabase.txt");
        rename("Temporary.txt","studentDatabase.txt");
        printf("\nThe student is UPDATED.\n");

        getch();
       }
       else
       {
        printf("Can not found anything about %s %s.\n",student.firstname,student.lastname);
        remove("Temporary.txt");
        fclose(fp);
        fclose(tempfp);
         getch();
       }
}

void fileSize(){
    FILE *fp;
    int size;
   fp=fopen("studentDatabase.txt","r");

   if(fp==NULL) {
      printf("File not found!\n");
   }
   else {
      fseek(fp,0,SEEK_END);
      size=ftell(fp);
      printf("The file's size is %1d Byte\n",size);
      fclose(fp);
      getch();
   }
}

int main()
{
   int choice;
   FILE *fp;
   int quit=0;
   do{
        system("CLS");
    printf("-------------------------------------------------------------\n");
    printf("|               STUDENT DATABASE SYSTEM                     |\n");
    printf("-------------------------------------------------------------\n");
    printf("| CEN108 - Homework 3                        Ahmet Karacali |\n");
    printf("-------------------------------------------------------------\n");
      printf("\n1 -> Add a Student\n");
      printf("2 -> Find a Student\n");
      printf("3 -> Delete a Student\n");
      printf("4 -> Update a Student\n");
      printf("5 -> Get File Size\n");
      printf("6 -> Quit ");
      printf("\n\n");
      printf("Enter your choice : ");
      scanf("%d",&choice);
      switch(choice)
      {
       case 1: { AddStd(); break; }
       case 2: {FindStd(); break;   }
       case 3: { deleteStd(); break;}
       case 4: {updateStd(); break;}
       case 5: { fileSize(); break;}
       case 6: quit=1; break;
        }
}while(quit==0);
      getch();
      return 0;
}