//
// Created by hp on 12/2/2022.
//

#include "fileManipulationFunctions.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/*************************************** Auxiliary functions ***********************************************/

// Générer aléatoirement le numéro d’identification de l’élève
int generateStudentID(int seed){
    int randomID;
    srand( (unsigned) time(0) + seed);
    for (int counter = 0; counter < 2; ++counter) {
        //this loop is to ensure the randomness of the generated value
        randomID = rand() % 10000;
    }
    return randomID;
}

void getFirstName(char **firstName, int number) {
    //open the first names file
    FILE *firstNameFile;
    firstNameFile = fopen(firstNamesFilePath, "r");

    //read the first name from the file
    for (int counter = 0; counter < number; ++counter) {
        //the current solution to read the nth name is to use a for loop until we reach the desired string
        fscanf(firstNameFile, "%[^,],", *firstName);
    }

}

void getlastNameAndGender(char **lastName, char **gender, int number) {
    FILE *lastNameAndGenderFile;
    lastNameAndGenderFile = fopen(lastNamesAndGenderFilePath, "r");

    //Max number of names is currently 614
    if(number > 614) number = number % 614;

    //read the first name from the file
    for (int counter = 0; counter < number; ++counter) {
        fscanf(lastNameAndGenderFile, "%[^,],%[^;];", *lastName, *gender);
    }
}

void getMarks(float *tableOfMarks, int level) {
    //The level will determine the number and type of subjects to generate marks for
    //I will suppose that all necessary information is saved in a global table (array)
    int numberOfSubjects = numberOfSubjectsPerLevel[level];

    for (int i = 0; i < numberOfSubjects; ++i) {;
        tableOfMarks[i] = rand() % 41 * 0.25; //0.25 * 40 = 10
        srand( (unsigned) time(NULL)+i);
    }
}

