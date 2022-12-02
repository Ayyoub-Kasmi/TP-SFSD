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

    float tableOfMarks[MaxNumberOfSubjects];
    getMarks(tableOfMarks, 3);

    srand(time(NULL));
    Fichier fichier;
    Buffer buffer;
    char chaine[5];
    int j = 0;
    int i = 0;
    int i1 = 247593;
    char str[10];

    sprintf(str, "%d", i1);
    buffer.tab[0] = 'f' ;
    buffer.tab[1] = 'a';
    buffer.tab[2] = 'r';
    buffer.tab[3] = 'e';
    buffer.tab[4] = 's';
    buffer.positionLibre = 5;
    printf("%d", sizeof(chaine));
    lirechaine(&fichier, &buffer, chaine, sizeof(chaine), &i, &j);

    for (int k = 0; k < 10; ++k) {
        printf("%s %d", chaine, rand());
    }


    printf("\n%s", str);

    char str1[10] = "213";
    sscanf(str1, "%d", &i1);
    printf("\n%d", i1);

    return 0;
}


//char text[20];
//int digit;
//for (digit = 0; digit < 10; ++digit)
//{
//text[digit] = digit + '0';
//puts(text);
//}