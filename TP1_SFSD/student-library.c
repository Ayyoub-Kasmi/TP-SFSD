#include "student-library.h"

void searchStudent(Fichier* fichier, Student student, int* i, int* j, bool found){
//    typedef struct {
//        int id;
//        int class;
//        char firstName[MAX_FIRST_NAME_SIZE];
//        char lastName[MAX_LAST_NAME_SIZE];
//        char gender;
//        char isDeleted;
//        float marks[MAX_NUMBER_OF_SUBJECTS];
//    } Student;

    //setting up some string buffers for reading from the file
    char firstNameSize[FIRSTNAME_LENGTH+1];
    char lastNameSize[LASTNAME_LENGTH+1];
    char classID[CLASS_ID_SIZE+1];

    int level = student.class % (10 * CLASS_NUMBER_SIZE); // student.class % 100 for our context
    found = false;

    //Getting the starting positions of the level
    *i = classesIndex[level].i;
    *j = classesIndex[level].j;

    if(*i == INT_MAX){
        //student level is higher than the current highest level of the school ==> insert in the end of file
        *i = getEntete(fichier, 1); //number of last block
        *j = getEntete(fichier, 2); //last available position in the last block
        return;
        //well in fact the only exception is if 
    }

    //read the lengths of first name and last name so to skip directly if it's not the right student
    lirechaine(fichier, &buffer, firstNameSize, FIRSTNAME_LENGTH, i, j);
    lirechaine(fichier, &buffer, lastNameSize, LASTNAME_LENGTH, i, j);
    lirechaine(fichier, &buffer, classID, CLASS_ID_SIZE, i, j);
    if(student.class !=)

    //stop conditions: find student or passing the its "potential?" position
}