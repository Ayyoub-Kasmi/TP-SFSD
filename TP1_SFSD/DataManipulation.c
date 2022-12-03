//
// Created by hp on 12/2/2022.
//

#include "DataManipulation.h"
#include "tovcFunctions.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>

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
    firstNameFile = fopen(FIRST_NAMES_FILE_PATH, "r");

    //read the first name from the file
    for (int counter = 0; counter < number; ++counter) {
        //the current solution to read the nth name is to use a for loop until we reach the desired string
        fscanf(firstNameFile, "%[^,],", *firstName);
    }

}

void getlastNameAndGender(char **lastName, char *gender, int number) {
    FILE *lastNameAndGenderFile;
    lastNameAndGenderFile = fopen(LAST_NAMES_AND_GENDER_FILE_PATH, "r");
    if (lastNameAndGenderFile == NULL){
        printf("Last names & genders file not found!\n");
        exit(1);
    }

    //Max number of names is currently 614
    if(number > 614) number = number % 614;

    //read the first name from the file
    for (int counter = 0; counter < number; ++counter) {
        fscanf(lastNameAndGenderFile, "%[^,],%[^;];", *lastName, gender);
    }
}

void getMarks(float *tableOfMarks, int level) {
    //The level will determine the number and type of subjects to generate marks for
    //I will suppose that all necessary information is saved in a global table (array)
    int numberOfSubjects = numberOfSubjectsPerLevel[level];

    for (int i = 0; i < numberOfSubjects; ++i) {
        tableOfMarks[i] = rand() % 41 * 0.25; //0.25 * 40 = 10
        srand( (unsigned) time(NULL)+i);
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
        if ((!(*found)) ) {
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
        if ((!(*found)) ) {
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
            if (roomIdArray->tab[j] % 100 == roomNumber){
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

//intiialize file:
/*
 1- create student array => avoid repition of id
 2- create classes array => avoid repition of class id
 3- forEachClass {
    for(i: 1 => studentPerClass){
        get a student id
        get name and gender
        create marks table
        write student in the file
    }
 }
*/

void createSchoolYear(){
    int year = CURRENT_YEAR;
    Student student;

    ClassIdArray classIdArray;
    classIdArray.nb = 0;
    StudentsIdArray studentsIdArray;
    studentsIdArray.nb = 0;

    for (int i = 0; i < FIRST_LOAD_OF_CLASSES; ++i) {
        generateClassId(&classIdArray);
    }
    for (int i = 0; i < FIRST_LOAD_OF_STUDENTS; ++i) {
        generateStudentId(&studentsIdArray);
    }

    for (int i = 0; i < FIRST_LOAD_OF_CLASSES; ++i) {
        for (int j = 0; j < STUENDT_PER_CLASS; ++j) {
            //get student information
            student.id = 1234;
            student.class = 202;
            getFirstName(&student.firstName, 1); //integrate the random number inside the function
            getlastNameAndGender(&student.lastName, &student.gender, 3); //change gender from array[1] to char
            student.gender = 'X';
            int level = student.class /100;
            getMarks(student.marks, level);

            //writeStudent(file, e, buff);
        }
    }

}