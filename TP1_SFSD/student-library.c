#include <limits.h>
#include <string.h>
#include "student-library.h"

/*************************************** Auxiliary functions ***********************************************/
void skip(FichierTovc *fichier, int steps, int *i, int *j) {
    (*j) += steps;
    if (*j >= TOVC_BUFFER_SIZE) {
        (*i)++;
        lireBloc(fichier, *i, &bufferTovc);
        (*j) -= TOVC_BUFFER_SIZE;
    }
}

/*************************************** Main functions ***********************************************/

void searchStudent(FichierTovc *fichier, Student student, int *i, int *j, bool *found) {
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
    char firstNameSize[FIRSTNAME_LENGTH + 1];
    char lastNameSize[LASTNAME_LENGTH + 1];
    char classID[CLASS_ID_SIZE + 1];
    char ID[STUDENT_ID_SIZE + 1];
    char firstName[MAX_FIRST_NAME_SIZE];
    char lastName[MAX_LAST_NAME_SIZE];

    //declaration of necessary variables
    int studentLevel =
            student.class / (int) (pow(10, CLASS_NUMBER_SIZE) + 1e-9); // student.class % 100 for our context;
    int class, offset;
    *found = false;

    //Getting the starting positions of the studentLevel
    *i = classesIndex[studentLevel].i;
    *j = classesIndex[studentLevel].j;
    lireBloc(fichier, *i, &bufferTovc);

    if (*i == INT_MAX) {
        //student studentLevel is higher than the current highest studentLevel of the school ==> insert in the end of file
        *i = getEntete(fichier, 1); //number of last block
        *j = getEntete(fichier, 2); //last available position in the last block
        return;
        //well in fact the only exception is if the school doesn't have a studentLevel in the middle (e.g like 1-3-5),
        //so the insertion won't necessarily be in the end
    }

    //variables to save positions i and j
    int tempI;
    int tempJ;

    while (!(*found)) {      //return statements are used to quit the loop if "stop" conditions are met

        //saving the starting positions of the read student before reading advancing and reading its information
        tempI = *i;
        tempJ = *j;

        //read the lengths of first name and last name so to skip directly if it's not the right student
        lirechaine(fichier, &bufferTovc, firstNameSize, FIRSTNAME_LENGTH, i, j);
        lirechaine(fichier, &bufferTovc, lastNameSize, LASTNAME_LENGTH, i, j);
        lirechaine(fichier, &bufferTovc, classID, CLASS_ID_SIZE, i, j);

        class = stringToInt(classID, CLASS_ID_SIZE);

        if (student.class == class) {
            //class found ===> compare IDs until finding the student or stopping
            printf("class found!\n");
            //read the ID
            lirechaine(fichier, &bufferTovc, ID, STUDENT_ID_SIZE, i, j);
            printf("\n\nstudent id read: %s", ID);

            if (student.id == stringToInt(ID, STUDENT_ID_SIZE)) {
                //student found ===> stop
                *i = tempI; //i will receive the number of the starting position (and not the IsDeleted field) since
                //we will need to modify other fields as well
                *j = tempJ;
                *found = true;
                return;
            } else {
                //student not found, decide whether to advance or stop ==> compare names
                offset = IS_DELETED_SIZE +
                         MARK_LENGTH * numberOfSubjectsPerLevel[studentLevel]; //skip to the field of "firstName"
                skip(fichier, offset, i, j);

                lirechaine(fichier, &bufferTovc, firstName, stringToInt(firstNameSize, FIRSTNAME_LENGTH), i, j);
                //compare first names
                /*
                    if(firstnames1 = firstname2){
                        lirechaine(lastname2)
                        if(lastname1= lastname2){
                            priority to the smallest ID
                        }
                        else {
                            decide whether to advance based on the result:
                                1- if not advancing make sure to assign tempI and tempJ to i and j
                                2- if advancing make sure to take the right offset (last name size + gender size)
                        }
                    } else{
                        decide whether to advance based on the result
                            1- if not advancing make sure to assign tempI and tempJ to i and j
                            2- if advancing make sure to take the right offset (only gender size)
                    }
                 */

            }
        } else if (class > student.class) {
            //passed the potential student's class ==> stop
            printf("stopped... current 'class' value is %d\n", class);
            *i = tempI;
            *j = tempJ;
            return; //to be reviewed
        } else {
            //either next student or end of file
            offset = STUDENT_ID_SIZE + IS_DELETED_SIZE + MARK_LENGTH * numberOfSubjectsPerLevel[studentLevel]
                     + stringToInt(firstNameSize, FIRSTNAME_LENGTH) +
                     stringToInt(lastNameSize, LASTNAME_LENGTH) + GENDER_SIZE;

            skip(fichier, offset, i, j);
        }

        if (*i == getEntete(fichier, 1)) {
            if (*j >= getEntete(fichier, 2)) {
                //reached last element ==> quit the loop
                printf("last element... current 'class' value is %d\n", class);

                return; //i and j already have the correct values (but to be tested to confirm)
            }
        }
    }
}


//void updateStudentInfo(FichierTovc* fichier, int numberOfArguments, ...) {
//    //this "..." syntax is used so to receive an argument of dynamic type (field number & value)
//

//    // initialize argument list
//    va_list list;
//    va_start(list, numberOfArguments);
//    int fieldNumber = va_arg(list, int);
//    //now I got the filed number...
//    /*
//        1- switch-case according to field number
//        2-
//     */
//}

//don't implement one function for the updates, implement different ones:
/*
    1- transfer student (update class ID) ==> this one requires circular shifting
    2- update marks
    3- update IDs
    4- update names (first or last name) ==> this one requires shifting
 */

void insertStudent(FichierTovc *fichier, Student student) {
    int i = 0;
    int j = 0;
    bool found = false;
    searchStudent(fichier, student, &i, &j, &found);
    if (!found) {
        //some code to create the student string
        char container1[4];//used to do the int => string conversion
        char stringBuffer[
                STUDENT_ID_SIZE + CLASS_ID_SIZE + IS_DELETED_SIZE + LASTNAME_LENGTH + FIRSTNAME_LENGTH + GENDER_SIZE +
                MAX_NUMBER_OF_SUBJECTS *
                (MARK_WHOLE_PART_LENGTH + MARK_DECIMAL_PART_LENGTH) + student.firstNameSize + student.lastNameSize];

        sprintf(container1, "%d%d", student.lastNameSize / 10,
                student.lastNameSize % 10); //lastNameSize can be a number of one digit

        //Write First Name size
        strcpy(stringBuffer, container1);
        char firstNameSizeString[FIRSTNAME_LENGTH + 1]; //+1 for the '\0' character
        sprintf(container1, "%d%d", student.firstNameSize / 10,
                student.firstNameSize % 10); //firstNameSize can be a number of one digit
        strcat(stringBuffer, container1);
        //the string that we are going to insert
        //Write ClassID
        char classIDString[CLASS_ID_SIZE + 1];
        char roomString[ROOM_SIZE + 1];
        if ((student.class / 100) % 10 == 0) {
            strcpy(classIDString, "p");
        }
        sprintf(roomString, "%d%d", (student.class / 10) % 10, student.class % 10);
        strcat(classIDString, roomString);

        strcat(stringBuffer, classIDString);
        //Write ID
        char studentIdString[STUDENT_ID_SIZE + 1];
        sprintf(studentIdString, "%d%d%d%d", student.id / 1000, (student.id / 100) % 10, (student.id / 10) % 10,
                student.id % 10);

        strcat(stringBuffer, studentIdString);

        //Write isDeleted
        strcat(stringBuffer, &student.isDeleted);
        //Write marks array
        int level = (student.class / 100) % 10;
        int markWholePart;
        int markDecimalPart;
        int intMark;
        char markWholePartString[MARK_WHOLE_PART_LENGTH + 1];
        char markDecimalPartString[MARK_DECIMAL_PART_LENGTH + 1];
        for (int k = 0; k < numberOfSubjectsPerLevel[level]; ++k) {
            intMark = student.marks[k] * 100;
            markWholePart = intMark / 100;
            markDecimalPart = intMark % 100;

            sprintf(markWholePartString, "%d%d", (markWholePart / 10) % 10, markWholePart % 10);
            sprintf(markDecimalPartString, "%d%d", (markDecimalPart / 10) % 10, markDecimalPart % 10);

            strcat(stringBuffer, markWholePartString);
            strcat(stringBuffer, markDecimalPartString);
        }



        //Write Full name
        strcat(stringBuffer, student.fullName);

        //Write gender
        strcat(stringBuffer, &student.gender);

        bool endOfFile = false;
        int k = 0;
        int m = -1;
        char c;


        while ((!endOfFile) && (k != m+1)){
            if (k >= strlen(stringBuffer)) k = 0;
            if (j >= TOVC_BUFFER_SIZE){
                j = 0;
                i++;
                ecrireBloc(fichier, i, bufferTovc);
            } else {
                c = bufferTovc.tab[j];


                }
            }



        }

        setEntete(fichier, 1, i);
//    if (*j >= buffer->positionLibre) buffer->positionLibre = *j; ==> j will be auto set inside ecrire chaine
        setEntete(fichier, 2, j);
        ecrireBloc(fichier, i, &bufferTovc);
    }
}