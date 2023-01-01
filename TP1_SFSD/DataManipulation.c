#include "DataManipulation.h"
#include "tovcFunctions.h"
#include "TofIndexFunctions.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <limits.h>

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

void getLastName(FILE* lastNamesFile,char *lastName, int *seed) {

    rewind(lastNamesFile); //to start from the beginning of the file

    *seed = generate4positionInt(*seed);
    int lastNamePosition = (*seed) % FIRST_NAME_FILE_SIZE;

    //read the first name from the file
    for (int counter = 0; counter < lastNamePosition; ++counter) {

        //the current solution is to read the nth name is to use a for loop until we reach the desired string
        fscanf(lastNamesFile, "%[^,],", lastName);
    }
}

void getFirstNameAndGender(FILE *firstNamesAndGendersFile, char *firstName, char *gender, int *seed) {

    rewind(firstNamesAndGendersFile); //to start from the beginning of the file

    *seed = generate4positionInt(*seed);
    //Max seed of names is currently 614
    int FirstNamePosition = generate4positionInt(*seed) % FIRST_NAME_FILE_SIZE;

    //read the first name from the file
    for (int counter = 0; counter < FirstNamePosition; ++counter) {
        fscanf(firstNamesAndGendersFile, "%[^,],%[^;];", firstName, gender);
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
    //insertionTof with delays to keep the order in the studentsIdArray
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
    //insertionTof with delays to keep the order in the studentsIdArray
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
    return rand() % 99 + 1;
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
        seed += classNumber;
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
    //normal binary search in the classIdArray
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

void insertClassId(ClassIdArray *classIdArray, int id) {
    //insertionTof with delays to keep the order in the studentsIdArray
    if (classIdArray->nb == 0) {
        classIdArray->tab[0].id = id;
        classIdArray->nb++;
    } else {
        int i = 0;
        bool found = false;
        searchClassId(classIdArray, id, &i, &found);

        if (id < classIdArray->tab[i].id) {
            for (int k = classIdArray->nb; k >= i; --k) {
                classIdArray->tab[k].id = classIdArray->tab[k - 1].id;
            }
        }
        classIdArray->tab[i].id = id;
        classIdArray->nb++;
    }

}

void insertRoomIdWithoutSearching(ClassIdArray *roomIdArray, int id, int i) {
    //insertionTof with delays to keep the order in the studentsIdArray
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

int stringToInt(char* string, int length){
    int digit, result = 0;
    for (int i = 0; i < length; ++i) {
        digit = (int)string[i] - 48; // the character '0' is equivalent to the integer 48
        result = result*10 + digit;
    }
    return result;
}

void intToString(char *string, int number, int length) {
    int digit;
    //    string[length] = '\0'; <== this line can be enabled for printing purpose
    for (int i = length-1; i >= 0; i--) {
        digit = number % 10;
        string[i] = digit + '0';
        string[i] = '0' + digit;
        number/=10;
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

void createSchoolYear(FichierTovc *fichier, FichierTof *classIndexFile, int *i, int *j) {
    //open first names file
    FILE *firstNamesAndGendersFile;
    firstNamesAndGendersFile = fopen(FIRST_NAMES_AND_GENDER_FILE_PATH, "r");
    if (firstNamesAndGendersFile == NULL) {
        printf("first names & genders file not found!\n");
        exit(1);
    }

    //open the last names file
    FILE *lastNamesFile;
    lastNamesFile = fopen(LAST_NAMES_FILE_PATH, "r");
    if (lastNamesFile == NULL) {
        printf("Last names file not found!\n");
        exit(1);
    }

    //open the classes index file

    int level;

    *i = 0;
    *j = 0;
    Student student;

    ClassIdArray classIdArray;
    classIdArray.nb = 0;
    StudentsIdArray studentsIdArray;
    studentsIdArray.nb = 0;
    StudentsNamesArray studentsNamesArray;
    studentsNamesArray.nb = 0;

    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {
        generateClassId(&classIdArray);
    }
    for (int k = 0; k < FIRST_LOAD_OF_STUDENTS; ++k) {
        generateStudentId(&studentsIdArray);
    }
    for (int k = 0; k < FIRST_LOAD_OF_STUDENTS; ++k) {
        generateStudentName(lastNamesFile, firstNamesAndGendersFile, &studentsNamesArray);
    }

    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {

        //writing the class positions into the index
        classIdArray.tab[k].i=*i;
        classIdArray.tab[k].j=*j;


        for (int l = 0; l < STUDENT_PER_CLASS; ++l) {
            //get student information
            student.id = studentsIdArray.tab[k * STUDENT_PER_CLASS + l].id;
            student.class = classIdArray.tab[k].id;
            strcpy(student.fullName, studentsNamesArray.tab[k * STUDENT_PER_CLASS + l].fullName);
            student.firstNameSize = studentsNamesArray.tab[k * STUDENT_PER_CLASS + l].firstNameSize;
            student.lastNameSize = studentsNamesArray.tab[k * STUDENT_PER_CLASS + l].lastNameSize;
            student.gender = studentsNamesArray.tab[k * STUDENT_PER_CLASS + l].gender;

            level = (student.class / 100) % 10; //refactor it using variables
            getMarks(student.marks, level);

            student.isDeleted = '0';

            writeStudent(fichier, &student, i, j);

        }

    }


    setEntete(fichier, 1, (*i) + 1); //Total number blocs
    setEntete(fichier, 2, *j); //Last position in the lastBloc
    setEntete(fichier, 3, TOVC_BUFFER_SIZE * (*i + 1) + (*j)); //Total number of characters in the file
    setEntete(fichier, 4, 0); //number of chars deleted

    //saving the class index into the file
    int i1 = 0, j1 = 0;
    IndexRecord record;
    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {
        record.id = classIdArray.tab[k].id;
        record.isDeleted = false;
        record.i = classIdArray.tab[k].i;
        record.j = classIdArray.tab[k].j;
        if (j1 < TOF_BUFFER_SIZE) {
            bufferTofClass.tab[j1] = record;
            j1++;
        } else {
            bufferTofClass.nb = j1;
            ecrireBlocTof(classIndexFile, i1, &bufferTofClass);
            i1++;
            bufferTofClass.tab[0] = record;
            j1 = 1;
        }
    }
    bufferTofClass.nb = j1;
    ecrireBlocTof(classIndexFile, i1, &bufferTofClass);
    setEnteteTof(classIndexFile, 1, i1 + 1);
    setEnteteTof(classIndexFile, 2, FIRST_LOAD_OF_CLASSES);
    setEnteteTof(classIndexFile, 3, 0);

    updateNumberOfClassesPerLevel(&classIdArray);


    //close first names file
    fclose(firstNamesAndGendersFile);

    //close last names file
    fclose(lastNamesFile);

    //close the index file
}

void writeStudent(FichierTovc *fichier, Student *student, int *i, int *j) {
    /*
         Structure of records inside the file (or buffer):
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
    char lastNameSizeString[LASTNAME_LENGTH + 1]; //+1 for the '\0' character

    intToString(lastNameSizeString, student->lastNameSize, LASTNAME_LENGTH);

    ecrireChaine(fichier, &bufferTovcData, lastNameSizeString, LASTNAME_LENGTH, i, j);


    //Write First Name size
    char firstNameSizeString[FIRSTNAME_LENGTH + 1]; //+1 for the '\0' character

    intToString(firstNameSizeString, student->firstNameSize, FIRSTNAME_LENGTH);

    ecrireChaine(fichier, &bufferTovcData, firstNameSizeString, FIRSTNAME_LENGTH, i, j);

    //Write ClassID
    char classIDString[CLASS_ID_SIZE + 1];
    intToString(classIDString, student->class, CLASS_ID_SIZE);

    if ((student->class / 100) % 10 == 0){
        classIDString[0] = 'p';
    }

    ecrireChaine(fichier, &bufferTovcData, classIDString, CLASS_ID_SIZE, i, j);

    //Write ID
    char studentIdString[STUDENT_ID_SIZE + 1];

    intToString(studentIdString, student->id, STUDENT_ID_SIZE);

    ecrireChaine(fichier, &bufferTovcData, studentIdString, STUDENT_ID_SIZE, i, j);

    //Write isDeleted
    ecrireChaine(fichier, &bufferTovcData, &student->isDeleted, IS_DELETED_SIZE, i, j);

    //Write marks array
    int level = (student->class / 100) % 10;
    int markWholePart;
    int markDecimalPart;
    int intMark;
    char markWholePartString[MARK_WHOLE_PART_LENGTH + 1];
    char markDecimalPartString[MARK_DECIMAL_PART_LENGTH + 1];
    for (int k = 0; k < numberOfSubjectsPerLevel[level]; ++k) {
        intMark = student->marks[k] * 100;
        markWholePart = intMark / 100;
        markDecimalPart = intMark % 100;

        intToString(markWholePartString, markWholePart, MARK_WHOLE_PART_LENGTH);
        intToString(markDecimalPartString, markDecimalPart, DECIMAL_PART_SIZE);

        ecrireChaine(fichier, &bufferTovcData, markWholePartString, MARK_WHOLE_PART_LENGTH, i, j);
        ecrireChaine(fichier, &bufferTovcData, markDecimalPartString, MARK_DECIMAL_PART_LENGTH, i, j);
    }



    //Write Full names
    ecrireChaine(fichier, &bufferTovcData, student->fullName, student->lastNameSize + student->firstNameSize, i, j);

    //Write gender
    ecrireChaine(fichier, &bufferTovcData, &student->gender, GENDER_SIZE, i, j);
    ecrireBloc(fichier, *i, &bufferTovcData);

//    printf("student id: %d\t student class: %d\t fullname: %s\n", student->id, student->class, student->fullName);
}

void generateStudentName(FILE* lastNamesFile, FILE* firstNamesAndGendersFile,StudentsNamesArray *studentsNamesArray) {
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
        getLastName(lastNamesFile, lastName, &randomSeed); //integrate the random number inside the function
        getFirstNameAndGender(firstNamesAndGendersFile, firstName, &gender,
                              &randomSeed);
        //we first have to put the first caractere before concatinating
        firstNameSize = (int) strlen(firstName);
        lastNameSize = (int) strlen(lastName);
        strcpy(fullName, lastName);
        strcat(fullName, firstName);
        insertStudentNameWithoutSearching(studentsNamesArray, fullName, gender,firstNameSize, lastNameSize, i);
        return;
    }
    while (found) {
        getLastName(lastNamesFile, lastName, &randomSeed); //integrate the random number inside the function
        getFirstNameAndGender(firstNamesAndGendersFile, firstName, &gender,
                              &randomSeed);
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
    //insertionTof with delays to keep the order in the studentsNamesArray
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
    //insertionTof with delays to keep the order in the studentsIdArray
    if (studentsNamesArray->nb <= 0) {
        strcpy(studentsNamesArray->tab[0].fullName, fullName);
        studentsNamesArray->tab[0].gender = gender;
        studentsNamesArray->tab[i].firstNameSize = firstNameSize;
        studentsNamesArray->tab[i].lastNameSize = lastNameSize;
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

void updateNumberOfClassesPerLevel(BufferTof *bufferTof) {
    //calculate number of classes per level:
    int classSup = MIN_1TH_GRADE_CLASS_ID;
    int count = 0, i = 0;
    int level = 0;
    while (i < bufferTof->nb) {
        if (bufferTof->tab[i].id < classSup) {
            count++;
            i++;
        } else {
            numberOfClassesPerLevel[level] = count;
            level++;
            count = 0;
            classSup += 100;
        }
    }
    numberOfClassesPerLevel[level] = count; //Because at the end where going to quit the loop without saving the count

}

void printStudentsFile(FichierTovc *fichier){
    int i=0, j=0;
    Student student;

    char firstNameSize[FIRSTNAME_LENGTH + 1];
    char lastNameSize[LASTNAME_LENGTH + 1];
    char classID[CLASS_ID_SIZE + 1];
    char ID[STUDENT_ID_SIZE + 1];
    char fullName[MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE + 1];
    char mark[MARK_LENGTH + 1];

    lireBloc(fichier, i, &bufferTovcData);

    while( i< getEntete(fichier, 1)-1 || j < getEntete(fichier, 2)){
        //Reading all information of the current student from the file:

        //Reading first name and last name sizes
        lirechaine(fichier, &bufferTovcData, firstNameSize, FIRSTNAME_LENGTH, &i, &j);
        student.firstNameSize = stringToInt(firstNameSize, FIRSTNAME_LENGTH);
        lirechaine(fichier, &bufferTovcData, lastNameSize, LASTNAME_LENGTH, &i, &j);
        student.lastNameSize = stringToInt(lastNameSize, LASTNAME_LENGTH);

        //Reading the class ID
        lirechaine(fichier, &bufferTovcData, classID, CLASS_ID_SIZE, &i, &j);
        if(classID[0] == 'p') classID[0] = '0';
        student.class = stringToInt(classID, CLASS_ID_SIZE);

        //Reading the student ID
        lirechaine(fichier, &bufferTovcData, ID, STUDENT_ID_SIZE, &i, &j);
        student.id = stringToInt(ID, STUDENT_ID_SIZE);

        //Reading the isDeleted character
        student.isDeleted = bufferTovcData.tab[j];
        j++;
        if(j == TOVC_BUFFER_SIZE){
            i++;
            lireBloc(fichier, i, &bufferTovcData);
            j=0;
        }

        //Reading the marks
        int count = numberOfSubjectsPerLevel[student.class / 100];
        for(int k = 0; k< count; k++){
            lirechaine(fichier, &bufferTovcData, mark, MARK_LENGTH, &i, &j);
            student.marks[k] = stringToInt(mark, MARK_LENGTH) / 100.0;
        }

        //Reading last name and first name
        lirechaine(fichier, &bufferTovcData, student.fullName, student.lastNameSize + student.firstNameSize, &i, &j);
        student.fullName[student.lastNameSize + student.firstNameSize] = '\0';

        //Reading the gender character
        student.gender = bufferTovcData.tab[j];
        j++;
        if(j == TOVC_BUFFER_SIZE){
            i++;
            lireBloc(fichier, i, &bufferTovcData);
            j=0;
        }

        printf("class: %d\tID: %d\tname: %s\n", student.class, student.id, student.fullName);

    }
}