#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tovcFunctions.h"
#include "fileManipulationFunctions.h"

//global variables declaration:
    const int numberOfSubjectsPerLevel[6] =  {4, 5, 5, 7, 7, 7}; //just an example, not real data
                    //we can also declare the names of subjects as a matrix of Levels-Subjects, if we need the names
    //string buffers:
    //char *firstName = (char*)malloc(sizeof(char)*MaxFirstNameSize);
    //char *lastName = (char*)malloc(sizeof(char)*MaxLastNameSize);
    //char *gender = (char*)malloc(sizeof(char));

    //Marks buffer:
    //float tableOfMarks[MaxNumberOfSubjects]

int main() {

    //Generation of random IDs for 3 students
    int seed = 0;
    int id;
    for (int i = 0; i < 3; ++i) {
        id = generateStudentID(seed);
        printf("ID[%d]: %d\n", i, id);
        seed = id; //we will use the previous ID value as a seed
    }

    //Accessing names files

    /*These three variables will be declared as a global variable and be used as string buffers */
    char *firstName = (char*)malloc(sizeof(char)*MaxFirstNameSize);
    char *lastName = (char*)malloc(sizeof(char)*MaxLastNameSize);
    char *gender = (char*)malloc(sizeof(char));

    getFirstName(&firstName, 4);
    getlastNameAndGender(&lastName, &gender, 3);
    printf("\nhello world\n");

    float tableOfMarks[MaxNumberOfSubjects];
    getMarks(tableOfMarks, 3);
    return 0;
}
