#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*TypeDef and Global Variables*/
typedef struct Student{
    int id;
    char name[50];
    float grade;
    struct Student *next;
}Student;

typedef struct StudentFile{
    int id;
    char name[50];
    float grade;
}StudentFile;

Student *head = NULL;
Student *tail = NULL;
Student *newStudent;
int S_numbers=0;

/*Functios Prototype*/

void Add(int);
void Delete(int);
void Search(int);
void Save(int);
void PrintAll(int);

void (*Op[5])(int) = 
{
    Add,
    Delete,
    Search,
    Save,
    PrintAll
};


void Start();

int Menu(int op_index, void(*Op[])()){

    Op[op_index]();

}





/*Main*/


int main(){

    int choice=0;
    Start();
    do{
    printf("-----------------------Menu----------------------\n Please Enter an option:\n 1=Add a Student\n 2=Delete a Student\n 3=Search by name\n 4=Save to Database\n 5=Print All Students Data\n 6=Exit\n");
    scanf("%d", &choice);

    if(choice < 1 || choice >6)
    {
        printf("invalid number!\n");
        free(newStudent);
        return -1;
    }
    
    Menu(choice-1, Op);    
    }while(choice != 6);

    free(newStudent);

    return 0;
}







/*Functions Definitions*/

void Start(int null){

    StudentFile temp;

    FILE *fp = fopen("Database.hex","rb");
    if(fp == NULL){
        printf("Data has not been loaded!\n");
    }
    fread(&S_numbers, sizeof(S_numbers), 1, fp);
    for(int i=0; i < S_numbers; i++)
    {
        newStudent = (Student*)malloc(sizeof(Student));
        
        if(newStudent == NULL)
        {
        printf("Memory allocation failed!\n");
        break;
        }

        fread(&temp, sizeof(StudentFile), 1, fp);
        newStudent->id = temp.id;
        strcpy(newStudent->name, temp.name);
        newStudent->grade = temp.grade;

        if(head == NULL)
        {
            head = newStudent;
            tail = newStudent;
        }
        else
        {
            tail->next = newStudent;
            tail = newStudent;
        }

        tail->next = NULL;
        


    }
    fclose(fp);

    
}

void Add(int null){
    char name[50];
    int id;
    float grade;

    newStudent = (Student*)malloc(sizeof(Student));
    printf("Enter student id:\n");
    scanf("%d", &id);
    printf("Enter student name:\n");
    scanf("%s", name);
    printf("Enter student grade:\n");
    scanf("%f", &grade);

    newStudent->id = id;
    strcpy(newStudent->name, name);
    newStudent->grade = grade;
    newStudent->next=NULL;


    if(head == NULL)
    {
        head = newStudent;
        tail = newStudent;
    }
    else
    {
        tail->next = newStudent;
        tail = newStudent;
    }

    
    S_numbers++;
   

    }


    void Save(int null){
        Student *current = head;
        StudentFile temp;
        FILE *fp = fopen("Database.hex","wb");
        fwrite(&S_numbers, sizeof(S_numbers), 1, fp);

        for(int i=0; i<S_numbers; i++)
        {
        temp.id = current->id;
        strcpy(temp.name, current->name);
        temp.grade = current->grade;    
        fwrite(&temp, sizeof(StudentFile), 1, fp);
        current = current->next;
        } 
        fclose(fp);   
    }

    void PrintAll(int null){
        Student *current = head;

        if(head == NULL){
            printf("No Data to Print!\n");
        }

        for(int i=0; i< S_numbers; i++)
        {
            printf("Name:%s\t\t Id:%d\t Grade:%f\n",current->name, current->id, current->grade);
            current = current->next;

        }

    }

    void Search(int null){

        char name[50];
        Student *current = head;
        int found=0;

        printf("Enter Student name:\n");
        scanf("%s", name);

        while(current != NULL)
        {
            if(strcmp(current->name, name) == 1)
            {
                found = 1;
                break;
            }    
        current = current->next;
        }

        if(found == 1)
        {
            printf(" ""%s"" Exist in your Database\n", name);
        }
        else if(found ==0)
        {
            printf(" ""%s"" Does not Exist in your Database\n", name);
        }

    }

    void Delete(int null){
        Student *current = head;
        Student *prev = head;
        char name[50];
        

        printf("Enter Student name to delete:\n");
        scanf("%s", name);

        while(strcmp(current->name, name)!=1)
        {
        prev = current;
        current = current->next;
        }
        
        if(current->next==NULL)
        {
        
            tail = prev;
            tail->next = NULL;
        }
        else
        {
            prev->next = current->next;
        }

        free(current);


    }
