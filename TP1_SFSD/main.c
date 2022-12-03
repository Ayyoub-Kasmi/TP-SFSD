#include <stdio.h>
#include <stdlib.h>
#include "DataManipulation.h"

//Global variables declaration:

StudentsIdArray studentsIdArray;
ClassIdArray roomIdArray;

const int numberOfSubjectsPerLevel[6] =  {4, 5, 5, 7, 7, 7}; //just an example, not real data
//we can also declare the names of subjects as a matrix of Levels-Subjects, if we need the names

//Strings buffers
char *firstName;
char *lastName;
char *gender;

//Marks buffer:
float tableOfMarks[MAX_NUMBER_OF_SUBJECTS];


int main() {
    //string buffers:
<<<<<<< Updated upstream
     firstName = (char*)malloc(sizeof(char)*MAX_FIRST_NAME_SIZE);
     lastName = (char*)malloc(sizeof(char)*MAX_LAST_NAME_SIZE);
     gender = (char*)malloc(sizeof(char)*2);

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
//    }

    return 0;
}

//    int i1 = 247593;
//    char str[10];
//    sprintf(str, "%d", i1);
//    printf("\n%s", str);
//
//
//    char str1[10] = "213";
//    sscanf(str1, "%d", &i1);
//    printf("\n%d", i1);

