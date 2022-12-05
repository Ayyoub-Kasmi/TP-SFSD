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

void getFirstName(char *firstName, int number) {
    //open the first names file
    FILE *firstNameFile;
    firstNameFile = fopen(FIRST_NAMES_FILE_PATH, "r");
    if (firstNameFile == NULL) {
        printf("First name file not found!\n");
        exit(1);
    }

    //read the first name from the file
    for (int counter = 0; counter < number; ++counter) {
        //the current solution is to read the nth name is to use a for loop until we reach the desired string
        fscanf(firstNameFile, "%[^,],", firstName);
    }

}

void getlastNameAndGender(char *lastName, char *gender, int number) {
    FILE *lastNameAndGenderFile;
    lastNameAndGenderFile = fopen(LAST_NAMES_AND_GENDER_FILE_PATH, "r");
    if (lastNameAndGenderFile == NULL) {
        printf("Last names & genders file not found!\n");
        exit(1);
    }

    //Max number of names is currently 614
    if (number > 614) number = number % 614;

    //read the first name from the file
    for (int counter = 0; counter < number; ++counter) {
        fscanf(lastNameAndGenderFile, "%[^,],%[^;];", lastName, gender);
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
            if (id > studentsIdArray->tab[*i]) {
                inf = *i + 1;
            } else if (id < studentsIdArray->tab[*i]) {
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
        studentsIdArray->tab[0] = id;
        studentsIdArray->nb++;
    } else {
        int i = 0;
        bool found = false;
        searchStudentId(studentsIdArray, id, &i, &found);
        if (!found) {
            if (id < studentsIdArray->tab[i]) {
                for (int k = studentsIdArray->nb; k >= i; --k) {
                    studentsIdArray->tab[k] = studentsIdArray->tab[k - 1];
                }
            }
            studentsIdArray->tab[i] = id;
            studentsIdArray->nb++;
        }
    }

}

void insertStudentIdWithoutSearching(StudentsIdArray *studentsIdArray, int id, int i) {
    //insertion with delays to keep the order in the studentsIdArray
    if (studentsIdArray->nb <= 0) {
        studentsIdArray->tab[0] = id;
        studentsIdArray->nb++;
    } else {
        if (id < studentsIdArray->tab[i]) {
            for (int k = studentsIdArray->nb; k > i; --k) {
                studentsIdArray->tab[k] = studentsIdArray->tab[k - 1];
            }
        }
        studentsIdArray->tab[i] = id;
        studentsIdArray->nb++;

    }

}

int generate2positionInt(int seed) {
    int randomID;
    srand((unsigned) time(0) + seed);
    for (int counter = 0; counter < 2; ++counter) {
        //this loop is to ensure the randomness of the generated value
        randomID = (rand() % 100) + 1; // So that the room numbers will be from 1 to 100
    }
    return randomID;
}

int generateTheLevel(int seed) {
    int randomID;
    srand((unsigned) time(0) + seed);
    randomID = rand() % 10;
    while (randomID > 5) {
        //this loop is to ensure the randomness of the generated value
        randomID = rand() % 10;
        // we'll consider for now that 0 represents the preparative year and we'll change it later
    }
    return randomID;
}

void generateClassId(ClassIdArray *roomIdArray) {
    int id = 0;
    bool found = true;
    if (roomIdArray->nb <= 0) {
        id = generate2positionInt(id);
        id += 100 * generateTheLevel(id);
        insertRoomId(roomIdArray, id);
        return;
    }
    while (found) {
        id = generate2positionInt(id);
        searchRoomNumber(roomIdArray, id, &found);
    }
    id += 100 * generateTheLevel(id);
    insertRoomId(roomIdArray, id);
}

void searchClassId(ClassIdArray *roomIdArray, int id, int *i, bool *found) {
    //normal binary search in the studentsIdArray
    *found = false;
    if (roomIdArray->nb > 0) {
        int inf = 0;
        int sup = roomIdArray->nb - 1;
        while ((inf <= sup) && (!(*found))) {
            *i = (inf + sup) / 2;
            if (id > roomIdArray->tab[*i]) { // to check only the room number and ignore the last one
                inf = *i + 1;
            } else if (id < roomIdArray->tab[*i]) {
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

void searchRoomNumber(ClassIdArray *roomIdArray, int roomNumber, bool *found) {
    //normal binary search in the studentsIdArray
    *found = false;
    if (roomIdArray->nb > 0) {
        //the search will be sequentiel due to the classes that are ordered by the school level and then the
        //roomNumber
        for (int j = 0; j < roomIdArray->nb; ++j) {
            if (roomIdArray->tab[j] % 100 == roomNumber) {
                *found = true;
            }
        }
    }
}

void insertRoomId(ClassIdArray *roomIdArray, int id) {
    //insertion with delays to keep the order in the studentsIdArray
    if (roomIdArray->nb <= 0) {
        roomIdArray->tab[0] = id;
        roomIdArray->nb++;
    } else {
        int i = 0;
        bool found = false;
        searchClassId(roomIdArray, id, &i, &found);
        if (!found) {
            if (id < roomIdArray->tab[i]) {
                for (int k = roomIdArray->nb; k >= i; --k) {
                    roomIdArray->tab[k] = roomIdArray->tab[k - 1];
                }
            }
            roomIdArray->tab[i] = id;
            roomIdArray->nb++;
        }
    }

}

void insertRoomIdWithoutSearching(ClassIdArray *roomIdArray, int id, int i) {
    //insertion with delays to keep the order in the studentsIdArray
    if (roomIdArray->nb <= 0) {
        roomIdArray->tab[0] = id;
        roomIdArray->nb++;
    } else {
        if (id < roomIdArray->tab[i]) {
            for (int k = roomIdArray->nb; k > i; --k) {
                roomIdArray->tab[k] = roomIdArray->tab[k - 1];
            }
        }
        roomIdArray->tab[i] = id;
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

void createSchoolYear(Fichier *fichier, Buffer *buffer, int* i, int* j) {
    int year = CURRENT_YEAR;
    *i = 0;
    *j = 0;
    Student student;

    ClassIdArray classIdArray;
    classIdArray.nb = 0;
    StudentsIdArray studentsIdArray;
    studentsIdArray.nb = 0;
    int firstNamePosition = generate4positionInt(13) % FIRST_NAME_FILE_SIZE; //upgarde this part with constante
    int lastNamePosition = generate4positionInt(15) % FIRST_NAME_FILE_SIZE;

    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {
        generateClassId(&classIdArray);
    }
    for (int k = 0; k < FIRST_LOAD_OF_STUDENTS; ++k) {
        generateStudentId(&studentsIdArray);
    }

    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {
        for (int l = 0; l < STUDENT_PER_CLASS; ++l) {
            //get student information
            firstNamePosition = generate4positionInt(k * STUDENT_PER_CLASS + l) % FIRST_NAME_FILE_SIZE;
            lastNamePosition = generate4positionInt(k * STUDENT_PER_CLASS + l) % FIRST_NAME_FILE_SIZE;
            student.id = studentsIdArray.tab[k * STUDENT_PER_CLASS + l];
            student.class = classIdArray.tab[k];
            getFirstName(student.firstName, firstNamePosition); //integrate the random number inside the function
            getlastNameAndGender(student.lastName, &student.gender,
                                 lastNamePosition); //change gender from array[1] to char

            int level = (student.class / 100)%10;
            getMarks(student.marks, level);
//            printf("id: %d, class: %d, firstname: %s, lastname: %s, gender: %c \n", student.id, student.class,
//                   student.firstName, student.lastName, student.gender);

            student.isDeleted = '0';
//            *i = k; //These instructions are total nonsense
//            *j = l;
            printf("current block: %d\t", *i);
            printf("position libre: %d\n", *j);
            writeStudent(fichier, &student, buffer, i, j);

        }
    }

    setEntete(fichier, 1, *i); //Number of the last block
    setEntete(fichier,2, *j); //Last position in the lastBloc
    setEntete(fichier, 3 ,BUFFER_SIZE * (*i + 1) + (*j) + 1); //Total number of characters in the file
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
         7- Gender
         8- fFirst name
         9- Last name
    */
    int firstNameSize = (int) strlen(student->firstName);
    int lastNameSize = (int) strlen(student->lastName);


    //Write First Name size
    char firstNameSizeString[FIRSTNAME_LENGTH_SIZE + 1]; //+1 for the '\0' character
    sprintf(firstNameSizeString, "%d%d", firstNameSize / 10,
            firstNameSize % 10); //firstNameSize can be a number of one digit
    ecrireChaine(fichier, buffer, firstNameSizeString, FIRSTNAME_LENGTH_SIZE, i, j);

    //Write LastName size
    char lastNameSizeString[LASTNAME_LENGTH_SIZE + 1]; //+1 for the '\0' character
    sprintf(lastNameSizeString, "%d%d", lastNameSize / 10,
            lastNameSize % 10); //lastNameSize can be a number of one digit
    ecrireChaine(fichier, buffer, lastNameSizeString, LASTNAME_LENGTH_SIZE, i, j);

    //Write ClassID
    char classIDString[CLASS_ID_SIZE + 1];//don't forget the 'p'
    sprintf(classIDString, "%d%d%d", (student->class / 100)%10, (student->class / 10)%10, student->class % 10); //
    ecrireChaine(fichier, buffer, classIDString, CLASS_ID_SIZE, i, j);

    //Write ID
    char studentIdString[STUDENT_ID_SIZE + 1];
    sprintf(studentIdString, "%d%d%d%d", student->id / 1000, (student->id / 100)%10, (student->id / 10)%10, student->id % 10);
    ecrireChaine(fichier, buffer, studentIdString, STUDENT_ID_SIZE, i, j);

    //Write isDeleted
    ecrireChaine(fichier, buffer, &student->isDeleted, IS_DELETED_SIZE, i, j);

    //Write marks array
    int level = (student->class / 100)%10;
    int markWholePart;
    int markDecimalPart;
    int intMark;
    char markWholePartString[WHOLE_PART_SIZE + 1];
    char markDecimalPartString[DECIMAL_PART_SIZE + 1];
    for (int k = 0; k < numberOfSubjectsPerLevel[level]; ++k) {
        intMark = student->marks[k] * 100;
        markWholePart = intMark / 100;
        markDecimalPart = intMark % 100;

        sprintf(markWholePartString, "%d%d", (markWholePart / 10)%10, markWholePart % 10);
        sprintf(markDecimalPartString, "%d%d", (markDecimalPart / 10)%10, markDecimalPart % 10);

        ecrireChaine(fichier, buffer, markWholePartString, MARK_WHOLE_PART_LENGTH, i, j);
        ecrireChaine(fichier, buffer, markDecimalPartString, DECIMAL_WHOLE_PART_LENGTH, i, j);
    }

    //Write gender
    ecrireChaine(fichier, buffer, &student->gender, GENDER_SIZE, i, j);

    //Write First and Last names
    ecrireChaine(fichier, buffer, student->firstName, firstNameSize, i, j);
    ecrireChaine(fichier, buffer, student->lastName, lastNameSize, i, j);

    setEntete(fichier, 1,*i);
    if (*j >= buffer->positionLibre) buffer->positionLibre = *j;
    setEntete(fichier, 2, *j);
    ecrireBloc(fichier, *i, buffer);

}