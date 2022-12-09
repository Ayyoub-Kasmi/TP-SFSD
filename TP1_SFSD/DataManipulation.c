#include "DataManipulation.h"
#include "tovcFunctions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

/*************************************** Auxiliary functions ***********************************************/

// Générer aléatoirement le numéro d’identification de l’élève
int generateStudentID(int seed) {
    int randomID;
    srand((unsigned) time(0) + seed);
    for (int counter = 0; counter < 2; ++counter) {
        //this loop is to ensure the randomness of the generated value
        randomID = rand() % 10000;
    }
    return randomID;
}

void getLastName(char *lastName, int number) {
    //open the first names file
    FILE *lastNameFile;
    lastNameFile = fopen(LAST_NAMES_FILE_PATH, "r");
    if (lastNameFile == NULL) {
        printf("First name file not found!\n");
        exit(1);
    }
    //"number" was kept to ensure the randomness of the firstNameposition value
    int lastNamePosition = generate4positionInt(number) % FIRST_NAME_FILE_SIZE;

    //read the first name from the file
    for (int counter = 0; counter < lastNamePosition; ++counter) {

        //the current solution is to read the nth name is to use a for loop until we reach the desired string
        fscanf(lastNameFile, "%[^,],", lastName);
    }

}

void getFirstNameAndGender(char *firstName, char *gender, int number) {
    FILE *FirstNameAndGenderFile;
    FirstNameAndGenderFile = fopen(FIRST_NAMES_AND_GENDER_FILE_PATH, "r");
    if (FirstNameAndGenderFile == NULL) {
        printf("first names & genders file not found!\n");
        exit(1);
    }
    //"number" was kept to ensure the randomness of the lastNamePosition value


    //Max number of names is currently 614
    int FirstNamePosition = generate4positionInt(number) % FIRST_NAME_FILE_SIZE;

    //read the first name from the file
    for (int counter = 0; counter < FirstNamePosition; ++counter) {
        fscanf(FirstNameAndGenderFile, "%[^,],%[^;];", firstName, gender);
    }
}

void getMarks(float *tableOfMarks, int level) {
    //The level will determine the number and type of subjects to generate marks for
    //I will suppose that all necessary information is saved in a global table (array)
    int numberOfSubjects = numberOfSubjectsPerLevel[level]; // probleme here

    for (int i = 0; i < numberOfSubjects; ++i) {
        tableOfMarks[i] = rand() % 41 * 0.25; //0.25 * 40 = 10
        srand((unsigned) time(NULL) + i);
    }
}

int generate4positionInt(int seed) {
    int randomID;
    srand((unsigned) time(0) + seed);
    for (int counter = 0; counter < 2; ++counter) {
        //this loop is to ensure the randomness of the generated value
        randomID = rand() % 10000;
    }
    return randomID;
}

void generateStudentId(StudentsIdArray *studentsIdArray) {
    int i = 0;
    int id = 0;
    bool found = true;
    if (studentsIdArray->nb <= 0) {
        id = generate4positionInt(id);
        insertStudentId(studentsIdArray, id);
        return;
    }
    while (found) {
        id = generate4positionInt(id);
        searchStudentId(studentsIdArray, id, &i, &found);
    }
    insertStudentIdWithoutSearching(studentsIdArray, id, i);
}

void searchStudentId(StudentsIdArray *studentsIdArray, int id, int *i, bool *found) {
    //normal binary search in the studentsIdArray
    *found = false;
    if (studentsIdArray->nb > 0) {
        int inf = 0;
        int sup = studentsIdArray->nb - 1;
        while ((inf <= sup) && (!(*found))) {
            *i = (inf + sup) / 2;
            if (id > studentsIdArray->tab[*i].id) {
                inf = *i + 1;
            } else if (id < studentsIdArray->tab[*i].id) {
                sup = *i - 1;
            } else {
                (*found) = true;
            }
        }
        if ((!(*found))) {
            *i = inf;
        }
    } else {
        *i = 0;
    }
}

void insertStudentId(StudentsIdArray *studentsIdArray, int id) {
    //insertion with delays to keep the order in the studentsIdArray
    if (studentsIdArray->nb <= 0) {
        studentsIdArray->tab[0].id = id;
        studentsIdArray->nb++;
    } else {
        int i = 0;
        bool found = false;
        searchStudentId(studentsIdArray, id, &i, &found);
        if (!found) {
            if (id < studentsIdArray->tab[i].id) {
                for (int k = studentsIdArray->nb; k >= i; --k) {
                    studentsIdArray->tab[k] = studentsIdArray->tab[k - 1];
                }
            }
            studentsIdArray->tab[i].id = id;
            studentsIdArray->nb++;
        }
    }

}

void insertStudentIdWithoutSearching(StudentsIdArray *studentsIdArray, int id, int i) {
    //insertion with delays to keep the order in the studentsIdArray
    if (studentsIdArray->nb <= 0) {
        studentsIdArray->tab[0].id = id;
        studentsIdArray->nb++;
    } else {
        if (id < studentsIdArray->tab[i].id) {
            for (int k = studentsIdArray->nb; k > i; --k) {
                studentsIdArray->tab[k] = studentsIdArray->tab[k - 1];
            }
        }
        studentsIdArray->tab[i].id = id;
        studentsIdArray->nb++;

    }

}

int generate2positionInt(int seed) {
    int randomID;
    srand((unsigned) time(0) + seed);
//    for (int counter = 0; counter < 2; ++counter) {
//        //this loop is to ensure the randomness of the generated value
//        randomID = (rand() % 98) + 1; // So that the room numbers will be from 1 to 100
//    }
    return rand() % 98 + 1;
}

int generateTheLevel(int seed) {
    int level;
    srand((unsigned) time(0) + seed);
//    level = rand() % 10;
//    while (level > 5) {
//        //this loop is to ensure the randomness of the generated value
//        level = rand() % 10;
//        // we'll consider for now that 0 represents the preparative year and we'll change it later
//    }
    level = rand() % 6;
    return level;
}

void generateClassId(ClassIdArray *classIdArray) {
    //initialize classIdArray.nb with 0 (outside) before running this function

    int classID = 0, classNumber = 0, level = 0;
    int seed = classIdArray->tab[classIdArray->nb].id;
    if (classIdArray->nb != 0) seed += classIdArray->tab[classIdArray->nb - 1].id;

    //generate a "unique" class number
    bool found = true;
    while (found) {
        classNumber = generate2positionInt(seed);
        checkRoomNumber(classIdArray, classNumber, &found);
        seed = classNumber;
    }
    //class number has been generated. Now assign a "unique" level for this class
    found = true;
    int temp = classNumber;
    while (found) {
        level = generateTheLevel(seed);
        temp = classNumber + 100 * level;
        checkClassID(classIdArray, temp, &found);
        seed = classIdArray->tab[classIdArray->nb].id;
    }
    classID = temp;

    insertClassId(classIdArray, classID);
}

void searchClassId(ClassIdArray *roomIdArray, int id, int *i, bool *found) {
    //normal binary search in the studentsIdArray
    *found = false;
    if (roomIdArray->nb > 0) {
        int inf = 0;
        int sup = roomIdArray->nb - 1;
        while ((inf <= sup) && (!(*found))) {
            *i = (inf + sup) / 2;
            if (id > roomIdArray->tab[*i].id) { // to check only the room number and ignore the last one
                inf = *i + 1;
            } else if (id < roomIdArray->tab[*i].id) {
                sup = *i - 1;
            } else {
                (*found) = true;
            }
        }
        if ((!(*found))) {
            *i = inf;
        }
    } else {
        *i = 0;
    }
}

void checkRoomNumber(ClassIdArray *ClassIdArray, int roomNumber, bool *found) {
    //normal binary search in the studentsIdArray

    *found = false;
    if (ClassIdArray->nb > 0) {
        //the search will be sequentiel since the classes that are ordered by the school level and then the
        //roomNumber
        for (int j = 0; j < ClassIdArray->nb; ++j) {
            if (ClassIdArray->tab[j].id % 100 == roomNumber) {
                *found = true;
//                printf("FOUND!\tClassIdArray: %d\troomNumber: %d\n", ClassIdArray->tab[j], roomNumber);
            }
        }
    }
}

void checkClassID(ClassIdArray *classIdArray, int classID, bool *found) {
    *found = false;
    if (classIdArray->nb > 0) {
        //the search will be sequential since the classes that are ordered by the school level and then the
        //classID
        for (int j = 0; j < classIdArray->nb; ++j) {
            if (classIdArray->tab[j].id == classID) {
                *found = true;
//                printf("FOUND!\tclassIdArray: %d\tclassID: %d\n", classIdArray->tab[j], classID);
            }
        }
    }
}

void insertClassId(ClassIdArray *roomIdArray, int id) {
    //insertion with delays to keep the order in the studentsIdArray
    if (roomIdArray->nb == 0) {
        roomIdArray->tab[0].id = id;
        roomIdArray->nb++;
    } else {
        int i = 0;
        bool found = false;
        searchClassId(roomIdArray, id, &i, &found);

        if (id < roomIdArray->tab[i].id) {
            for (int k = roomIdArray->nb; k >= i; --k) {
                roomIdArray->tab[k].id = roomIdArray->tab[k - 1].id;
            }
        }
        roomIdArray->tab[i].id = id;
        roomIdArray->nb++;
    }

}

void insertRoomIdWithoutSearching(ClassIdArray *roomIdArray, int id, int i) {
    //insertion with delays to keep the order in the studentsIdArray
    if (roomIdArray->nb <= 0) {
        roomIdArray->tab[0].id = id;
        roomIdArray->nb++;
    } else {
        if (id < roomIdArray->tab[i].id) {
            for (int k = roomIdArray->nb; k > i; --k) {
                roomIdArray->tab[k].id = roomIdArray->tab[k - 1].id;
            }
        }
        roomIdArray->tab[i].id = id;
        roomIdArray->nb++;

    }
}

/*************************************** Main functions ***********************************************/

//initialize file:
/*
 1- create student array => avoid repetition of id
 2- create classes array => avoid repetition of class id
 3- forEachClass {
    for(i: 1 => studentPerClass){
        get a student id
        get name and gender
        create marks table
        write student in the file
    }
 }
*/

void createSchoolYear(Fichier *fichier, Buffer *buffer, int *i, int *j) {
    int year = CURRENT_YEAR;
    *i = 0;
    *j = 0;
    Student student;

    ClassIdArray classIdArray;
    classIdArray.nb = 0;
    StudentsIdArray studentsIdArray;
    studentsIdArray.nb = 0;
    StudentsNamesArray studentsNamesArray;
    studentsNamesArray.nb = 0;
    int firstNamePosition = generate4positionInt(13) % FIRST_NAME_FILE_SIZE; //upgarde this part with constante
    int lastNamePosition = generate4positionInt(15) % FIRST_NAME_FILE_SIZE;

    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {
        generateClassId(&classIdArray);
    }
    for (int k = 0; k < FIRST_LOAD_OF_STUDENTS; ++k) {
        generateStudentId(&studentsIdArray);
    }
    for (int k = 0; k < FIRST_LOAD_OF_STUDENTS; ++k) {
        generateStudentName(&studentsNamesArray);
    }

    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {
        for (int l = 0; l < STUDENT_PER_CLASS; ++l) {
            //get student information
//            firstNamePosition = generate4positionInt(k * STUDENT_PER_CLASS + l) % FIRST_NAME_FILE_SIZE;
//            lastNamePosition = generate4positionInt(k * STUDENT_PER_CLASS + l) % FIRST_NAME_FILE_SIZE;
            student.id = studentsIdArray.tab[k * STUDENT_PER_CLASS + l].id;
            strcpy(student.fullName, studentsNamesArray.tab[k * STUDENT_PER_CLASS + l].fullName);
            student.gender = studentsNamesArray.tab[k * STUDENT_PER_CLASS + l].gender;
            student.class = classIdArray.tab[k].id;
            printf("student class: %d\n", student.class);
//            getFirstName(student.firstName, firstNamePosition); //integrate the random number inside the function
//            getlastNameAndGender(student.lastName, &student.gender,
//                                 lastNamePosition);
// change gender from array[1] to char

            int level = (student.class / 100) % 10; //refactor it using variables
            getMarks(student.marks, level);
//            printf("id: %d, class: %d, firstname: %s, lastname: %s, gender: %c \n", student.id, student.class,
//                   student.firstName, student.lastName, student.gender);

            student.isDeleted = '0';
            if (*j >= BUFFER_SIZE) {
                (*i)++;
                (*j) = 1;
            }
            studentsIdArray.tab[k * STUDENT_PER_CLASS + l].i = *i;
            studentsIdArray.tab[k * STUDENT_PER_CLASS + l].j = *j;

            classIdArray.tab[k].i = *i;
            classIdArray.tab[k].j = *j;

            writeStudent(fichier, &student, buffer, i, j);

        }
    }

    setEntete(fichier, 1, *i); //Number of the last block
    setEntete(fichier, 2, *j); //Last position in the lastBloc
    setEntete(fichier, 3, BUFFER_SIZE * (*i + 1) + (*j) + 1); //Total number of characters in the file
    setEntete(fichier, 4, 0); //number of chars deleted


}

void writeStudent(Fichier *fichier, Student *student, Buffer *buffer, int *i, int *j) {
    /*
         Structure of data inside the file (or buffer):

         1- Size of the first name
         2- Size of the last name
         3- Class id
         4- Student id
         5- isDeleted (boolean)
         6- Marks array
         7- First name
         8- Last name
         9- Gender
    */


    //Write LastName size
    char lastNameSizeString[LASTNAME_LENGTH_SIZE + 1]; //+1 for the '\0' character
    sprintf(lastNameSizeString, "%d%d", student->lastNameSize / 10,
            student->lastNameSize % 10); //lastNameSize can be a number of one digit
    ecrireChaine(fichier, buffer, lastNameSizeString, LASTNAME_LENGTH_SIZE, i, j);


    //Write First Name size
    char firstNameSizeString[FIRSTNAME_LENGTH_SIZE + 1]; //+1 for the '\0' character
    sprintf(firstNameSizeString, "%d%d", student->firstNameSize / 10,
            student->firstNameSize % 10); //firstNameSize can be a number of one digit
    ecrireChaine(fichier, buffer, firstNameSizeString, FIRSTNAME_LENGTH_SIZE, i, j);

    //Write ClassID
    //TO CHANGE ASAP
    char classIDString[CLASS_ID_SIZE + 1];//don't forget the 'p'
    sprintf(classIDString, "%d%d%d", (student->class / 100) % 10, (student->class / 10) % 10, student->class % 10); //
    ecrireChaine(fichier, buffer, classIDString, CLASS_ID_SIZE, i, j);

    //Write ID
    char studentIdString[STUDENT_ID_SIZE + 1];
    sprintf(studentIdString, "%d%d%d%d", student->id / 1000, (student->id / 100) % 10, (student->id / 10) % 10,
            student->id % 10);
    ecrireChaine(fichier, buffer, studentIdString, STUDENT_ID_SIZE, i, j);

    //Write isDeleted
    ecrireChaine(fichier, buffer, &student->isDeleted, IS_DELETED_SIZE, i, j);

    //Write marks array
    int level = (student->class / 100) % 10;
    int markWholePart;
    int markDecimalPart;
    int intMark;
    char markWholePartString[WHOLE_PART_SIZE + 1];
    char markDecimalPartString[DECIMAL_PART_SIZE + 1];
    for (int k = 0; k < numberOfSubjectsPerLevel[level]; ++k) {
        intMark = student->marks[k] * 100;
        markWholePart = intMark / 100;
        markDecimalPart = intMark % 100;

        sprintf(markWholePartString, "%d%d", (markWholePart / 10) % 10, markWholePart % 10);
        sprintf(markDecimalPartString, "%d%d", (markDecimalPart / 10) % 10, markDecimalPart % 10);

        ecrireChaine(fichier, buffer, markWholePartString, MARK_WHOLE_PART_LENGTH, i, j);
        ecrireChaine(fichier, buffer, markDecimalPartString, DECIMAL_WHOLE_PART_LENGTH, i, j);
    }



    //Write Full names
    ecrireChaine(fichier, buffer, student->fullName, student->lastNameSize + student->firstNameSize, i, j);

    //Write gender
    ecrireChaine(fichier, buffer, &student->gender, GENDER_SIZE, i, j);

    setEntete(fichier, 1, *i);
    if (*j >= buffer->positionLibre) buffer->positionLibre = *j;
    setEntete(fichier, 2, *j);
    ecrireBloc(fichier, *i, buffer);
}

void generateStudentName(StudentsNamesArray *studentsNamesArray) {
    int i = 0;
    int id = 0;
    bool found = true;
    char firstName[MAX_FIRST_NAME_SIZE];
    char lastName[MAX_LAST_NAME_SIZE];
    char fullName[MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE + GENDER_SIZE];
    char gender;
    int randomSeed = 0;
    int firstNameSize;
    int lastNameSize;
    if (studentsNamesArray->nb <= 0) {
        getLastName(lastName, 0); //integrate the random number inside the function
        getFirstNameAndGender(firstName, &gender,
                             0);
        //we first have to put the first caractere before concatinating
        firstNameSize = (int) strlen(firstName);
        lastNameSize = (int) strlen(lastName);
        strcpy(fullName, lastName);
        strcat(fullName, firstName);
        insertStudentNameWithoutSearching(studentsNamesArray, fullName, gender,firstNameSize, lastNameSize, i);
        return;
    }
    while (found) {
        randomSeed++;
        getLastName(lastName, randomSeed); //integrate the random number inside the function
        getFirstNameAndGender(firstName, &gender,
                             randomSeed);
        firstNameSize = (int) strlen(firstName);
        lastNameSize = (int) strlen(lastName);
        strcpy(fullName, lastName);
        strcat(fullName, firstName);
        searchStudentName(studentsNamesArray, fullName, &i, &found);
    }
    insertStudentNameWithoutSearching(studentsNamesArray, fullName, gender, firstNameSize, lastNameSize, i);
}

void searchStudentName(StudentsNamesArray *studentsNamesArray, char *fullName, int *i, bool *found) {
    //normal binary search in the studentsIdArray

    //strcmp compares two character strings ( str1 and str2 ) using the standard EBCDIC
    // collating sequence. The return value has the same relationship to 0 as str1 has to str2.
    // If two strings are equal up to the point at which one terminates
    // (that is, contains a null character), the longer string is considered greater.
    char currentName[MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE + GENDER_SIZE];
    *found = false;
    if (studentsNamesArray->nb > 0) {
        int numberOfCharsToCompare;
        int inf = 0;
        int sup = studentsNamesArray->nb - 1;
        while ((inf <= sup) && (!(*found))) {
            *i = (inf + sup) / 2;
            strcpy(currentName, studentsNamesArray->tab[*i].fullName);
            numberOfCharsToCompare = (int) strlen(fullName);
            if (numberOfCharsToCompare > strlen(currentName))
                numberOfCharsToCompare = (int) strlen(currentName);
            if (strncmp(fullName, currentName, numberOfCharsToCompare) > 0) {
                inf = *i + 1;
            } else if (strncmp(fullName, currentName, numberOfCharsToCompare) < 0) {
                sup = *i - 1;
            } else { //two levels of comparing to ensure the correctness of the functions.
                if (strcmp(fullName, currentName) > 0) {
                    inf = *i + 1;
                } else if (strcmp(fullName, currentName) < 0) {
                    sup = *i - 1;
                } else {
                    (*found) = true;
                }
            }
        }
        if ((!(*found))) {
            *i = inf;
        }
    } else {
        *i = 0;
    }
}

void insertStudentName(StudentsNamesArray *studentsNamesArray, char *fullName, char gender,int firstNameSize,
                       int lastNameSize) {
    //insertion with delays to keep the order in the studentsNamesArray
    if (studentsNamesArray->nb <= 0) {
        strcpy(studentsNamesArray->tab[0].fullName, fullName);
        studentsNamesArray->tab[0].gender = gender;
        studentsNamesArray->nb++;
    } else {
        int i = 0;
        bool found = false;
        searchStudentName(studentsNamesArray, fullName, &i, &found);
        if (!found) {
            if (strcmp(fullName, studentsNamesArray->tab[i].fullName) < 0) { // !!! we have to recheck this
                for (int k = studentsNamesArray->nb; k > i; --k) {
                    studentsNamesArray->tab[k] = studentsNamesArray->tab[k - 1];
                    //strcpy(studentsNamesArray->tab[k].fullName, studentsNamesArray->tab[k - 1].fullName);
                }
            }
            strcpy(studentsNamesArray->tab[i].fullName, fullName);
            studentsNamesArray->tab[i].gender = gender;
            studentsNamesArray->tab[i].firstNameSize = firstNameSize;
            studentsNamesArray->tab[i].lastNameSize = lastNameSize;
            studentsNamesArray->nb++;
        }
    }

}

void insertStudentNameWithoutSearching(StudentsNamesArray *studentsNamesArray, char *fullName, char gender, int firstNameSize,
                                       int lastNameSize, int i) {
    //insertion with delays to keep the order in the studentsIdArray
    if (studentsNamesArray->nb <= 0) {
        strcpy(studentsNamesArray->tab[0].fullName, fullName);
        studentsNamesArray->tab[0].gender = gender;
        studentsNamesArray->nb++;
        //ad the size of the name adn the size of the last name !!!
    } else {
        if (strcmp(fullName, studentsNamesArray->tab[i].fullName) < 0) {
            for (int k = studentsNamesArray->nb; k > i; --k) {
                studentsNamesArray->tab[k] = studentsNamesArray->tab[k - 1];
                //strcpy(studentsNamesArray->tab[k].fullName, studentsNamesArray->tab[k - 1].fullName);
            }
        }
        strcpy(studentsNamesArray->tab[i].fullName, fullName);
        studentsNamesArray->tab[i].gender = gender;
        studentsNamesArray->tab[i].firstNameSize = firstNameSize;
        studentsNamesArray->tab[i].lastNameSize = lastNameSize;
        studentsNamesArray->nb++;

    }

}
