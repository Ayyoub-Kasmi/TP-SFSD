#include <stdio.h>
#include <stdlib.h>
#include "DataManipulation.h"
#include <string.h>

#define SIZE 10

//Global variables declaration:

StudentsIdArray studentsIdArray;
ClassIdArray roomIdArray;
StudentsNamesArray studentsNamesArray;

const int numberOfSubjectsPerLevel[6] =  {4, 5, 5, 7, 7, 7}; //just an example, not real data
//we can also declare the names of subjects as a matrix of Levels-Subjects, if we need the names

//Strings buffers
char *firstName;
char *lastName;
char *gender;

//Marks buffer:
float tableOfMarks[MAX_NUMBER_OF_SUBJECTS];

//File buffer:
Buffer buffer;

int main() {

//    buffer.positionLibre = 0;
//    int i = 0;
//    int j = 0;
//    char testString[BUFFER_SIZE];
//    Fichier* fichier = ouvrirFichier("2022_STUDENTS", 'N');
//
//    //Custom student for test
//    Student student;
//    student.id = 3333;
//    student.class = 222;
//    strcpy(student.firstName ,"Houari");
//    printf("firstname: %s\n", student.firstName);
//    strcpy(student.lastName, "Mohammed");
//    student.gender = 'M';
//    student.isDeleted = '0';
//    student.marks[0] = 10.00;
//    student.marks[1] = 7.5;
//    student.marks[2] = 9.25;
//    student.marks[3] = 5.5;
//    student.marks[4] = 8.0;
//    writeStudent(fichier, &student,  &buffer, &i,&j);
//
//    student.id = 9999;
//    student.class = 444; //level is 4, number of subjects is 7
//    strcpy(student.firstName ,"Sediki");
//    printf("firstname: %s\n", student.firstName);
//    strcpy(student.lastName, "Raouf");
//    student.gender = 'M';
//    student.isDeleted = '0';
//    student.marks[0] = 11.11;
//    student.marks[1] = 22.22;
//    student.marks[2] = 33.33;
//    student.marks[3] = 44.44;
//    student.marks[4] = 55.55;
//    student.marks[5] = 66.66;
//    student.marks[6] = 77.77;
//    writeStudent(fichier, &student,  &buffer, &i,&j);
//
////    createSchoolYear(fichier, &buffer, &i, &j);
//    j = 0;
//    i = 0;
////    lirechaine(fichier, &buffer, testString,  buffer.positionLibre, &i, &j); //
//    lireBloc(fichier, i, &buffer);
//    buffer.positionLibre = 99;
//    lirechaine2(fichier, &buffer, testString,  buffer.positionLibre, &i, &j);
//    //after the end of each string there is '\0' so we have to eliminate it
//    printf("%s", testString);
//    fermerFichier(fichier);


    int  result;
    char buffer1[SIZE] = "a";
    char buffer2[SIZE] = "bau6ri6eri6ri7rir7s";
    int index = 1;
    void print_result( int, char *, char *, int );

    result = strcmp( buffer1, buffer2 );
    printf( "  strcmp: compares each character\n");
    print_result( result, buffer1, buffer2, index );

    result = strncmp( buffer2, buffer1, index);
    printf( "\nstrncmp: compares only the first %i characters\n", index);
    print_result( result, buffer2, buffer1, index );

    studentsNamesArray.nb = 0;
    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {
        generateStudentName(&studentsNamesArray);
    }
    for (int k = 0; k < 30; ++k) {
        printf("%s %c %d %d\n", studentsNamesArray.tab[k].fullName, studentsNamesArray.tab[k].gender, studentsNamesArray.tab[k].lastNameSize, studentsNamesArray.tab[k].firstNameSize);
    }

    return 0;
}

void print_result( int res, char * p_buffer1, char * p_buffer2, int index )
{
    if ( res == 0 )
        printf( "first %i characters of \"%s\" is identical to \"%s\"\n",
                index,  p_buffer1, p_buffer2);
    else if ( res < 0 )
        printf( "\"%s\" is less than \"%s\"\n", p_buffer1, p_buffer2 );
    else
        printf( "\"%s\" is greater than \"%s\"\n", p_buffer1, p_buffer2 );
}
//    ClassIdArray classIdArray;
//    classIdArray.nb = 0;
//    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {
//        generateClassId(&classIdArray);
//    }
//    printf("array.nb: %d\n", classIdArray.nb);
//
//    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {
//        printf("class: %d, array.nb: %d\n", classIdArray.tab[k] ,classIdArray.nb);
//    }

//    int id = 0;
//    bool found;
//    ClassIdArray classIdArray;
//    classIdArray.nb = 6;
//    classIdArray.tab[0]=223  ;
//    classIdArray.tab[1]= 400 ;
//    classIdArray.tab[2]= 305 ;
//    classIdArray.tab[3]= 416 ;
//    classIdArray.tab[4]=  520;
//    classIdArray.tab[5]=  310;
//    checkRoomNumber(&classIdArray, 0, &found);
//    printf("found: %d\n", found);

//Custom student for test
//    Student student;
//    student.id = 1;
//    student.class = 115;
//    strcpy(student.firstName ,"Houari");
//    printf("firstname: %s\n", student.firstName);
//    strcpy(student.lastName, "Mohammed");
//    student.gender = 'M';
//    student.isDeleted = '0';
//    student.marks[0] = 10.00;
//    student.marks[1] = 7.5;
//    student.marks[2] = 9.25;
//    student.marks[3] = 5.5;
//    student.marks[4] = 8.0;

//    writeStudent(fichier, &student,  &buffer, &i,&j);
//    printf("i after writing: %d\nj after writing: %d\n", i, j);
//string buffers:
//     firstName = (char*)malloc(sizeof(char)*MAX_FIRST_NAME_SIZE);
//     lastName = (char*)malloc(sizeof(char)*MAX_LAST_NAME_SIZE);
//     gender = (char*)malloc(sizeof(char)*2);


//    //Generation of random IDs for 3 students
//    int seed = 0;
//    int id;
//    for (int i = 0; i < 3; ++i) {
//        id = generateStudentID(seed);
//        printf("ID[%d]: %d\n", i, id);
//        seed = id; //we will use the previous ID value as a seed
//    }

//
//    getFirstName(&firstName, 4);
//    getlastNameAndGender(&lastName, &gender, 3);
//    printf("\nhello world\n");
//
//    getMarks(tableOfMarks, 3);
//
//    studentsIdArray.nb = 0;
//    studentsIdArray.nb = 0;

//    for (int i = 0; i < 30; ++i) {
//        generateClassId(&roomIdArray);
//    }
//
//    for (int i = 0; i < 30; ++i) {
//        printf("%d\n", roomIdArray.tab[i]);
//    }//
//createSchoolYear();
//char buffer[30] = "Hello";
//    printf("%lu", strlen(buffer));
//
//    int i1 = 247;
//    char str[4];
//    sprintf(str, "%d", i1);
//    printf("\n%s %d", str, strlen(str));


//    int i1 = 247593;
//    char str[10];
//    sprintf(str, "%d", i1);
//    printf("\n%s", str);
//
//
//    char str1[10] = "213";
//    sscanf(str1, "%d", &i1);
//    printf("\n%d", i1);

