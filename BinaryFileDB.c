#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>

void Add();
void Find();
void Update();
void Delete();
void ShowSize();
void MyMenu();

typedef struct
{
       char Name[20];
       char LastName[20];
       char Gender[1];
       int math;
       int comp;
       int secret;
} Student;

int main()
{
   int choice;
   int quit=0;
   do{
        system("CLS");
    printf("-------------------------------------------------------------\n");
    printf("|               STUDENT DATABASE SYSTEM  (BINARY)            |\n");
    printf("-------------------------------------------------------------\n");
    printf("| CEN108 - Homework 3                         Ahmet Karacali |\n");
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
       case 1: { Add(); break; }
       case 2: {Find(); break;   }
       case 3: {Delete(); break;}
       case 4: {update(); break;}
       case 5: { fileSize(); break;}
       case 6: quit=1; break;
        }
}while(quit==0);
      getch();
      return 0;
}


void update()
{
    Student *students;
    students = (Student*) malloc(sizeof(Student));

    FILE *studentInfo;

    Delete();

    printf("Please Enter NEW Gender:");
    scanf("%s",&students->Gender);
    printf("Please Enter NEW Math Score:");
    scanf("%d",&students->math);
    printf("Please Enter NEW Computer Score:");
    scanf("%d",&students->comp);

    studentInfo=fopen("myStudents.txt","rb+");
    fwrite(students, sizeof(Student) - 2*sizeof(students), 1, studentInfo);
    fclose(studentInfo);
    printf("Student updated..\n");
    getch();
}
void Add()
{
    Student *students;
    students = (Student*) malloc(sizeof(Student));

    FILE *studentInfo;

    printf("Please Enter First Name:");
    scanf("%s",&students->Name);
    printf("Please Enter Last Name:");
    scanf("%s",&students->LastName);
    printf("Please Enter Gender:");
    scanf("%s",&students->Gender);
    printf("Please Enter Math Score:");
    scanf("%d",&students->math);
    printf("Please Enter Computer Score:");
    scanf("%d",&students->comp);

    studentInfo=fopen("myStudents.txt","ab");
    fwrite(students, sizeof(Student) - 2*sizeof(students), 1, studentInfo);
    fclose(studentInfo);
    printf("Student added..\n");
    getch();
}

void Delete()
{
    Student *students;
    char TempName[20];
    char TempLastName[20];

    FILE *StudentInfo;
    FILE *TempStudentInfo;

    printf("Please enter the name of the student:");
    scanf("%s",&TempName);
    printf("Please enter the Last Name of the student:");
    scanf("%s",&TempLastName);

    StudentInfo = fopen("myStudents.txt","rb");
    TempStudentInfo = fopen("Temporary.txt","wb");

    while(!feof(StudentInfo))
     {
            students = (Student*) malloc(sizeof(Student));
            fread(students, sizeof(Student) - 2*sizeof(students), 1, StudentInfo);
            if(students != NULL)
            {
                if(strcmp(students->Name, TempName))
                {
                    fwrite(students, sizeof(Student) - 2*sizeof(students), 1, TempStudentInfo);
                }
                if(strcmp(students->LastName, TempLastName))
                {
                    fwrite(students, sizeof(Student) - 2*sizeof(students), 1, TempStudentInfo);
                }
                else if(strcmp(students->Name, TempName))
                {
                    if(strcmp(students->LastName, TempLastName))
                    {
                        printf("Student DELETED!\n");
                    }

                }
            }
     }
     fclose(StudentInfo);
     fclose(TempStudentInfo);

     remove("myStudents.txt");
     rename("Temporary.txt","myStudents.txt");
     getch();
}

void Find()
{
    Student *students;
    char TempName[20];
    char TempLastName[20];

    int found=0;
    FILE *StudentInfo;

    printf("Please enter the name of the student:");
    scanf("%s",&TempName);
    printf("Please enter the Last Name of the student:");
    scanf("%s",&TempLastName);

    StudentInfo = fopen("myStudents.txt","r");

     while(!feof(StudentInfo))
     {
            students = (Student*) malloc(sizeof(Student));
            fread(students, sizeof(Student) - 2*sizeof(students), 1, StudentInfo);

            //printf(students->Name);
            if(students != NULL)
            {
                if(!strcmp(students->Name, TempName))
                {
                if(!strcmp(students->LastName, TempLastName))
                {
                 printf("First Name : %s\n", students->Name);
                 printf("Last Name : %s\n", students->LastName);
                 printf("Gender : %s\n", students->Gender);
                 printf("Math Score : %d\n", students->math);
                 printf("Computer Score : %d\n", students->comp);
                 found=1;

                }
                }
            }
     }
     fclose(StudentInfo);
     if(found!=1)
            {
                    printf("There is no student with that name.\n");
            }
            getch();
}

void fileSize(){
    FILE *fp;
    int size;
   fp=fopen("myStudents.txt","r");

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