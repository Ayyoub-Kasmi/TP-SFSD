//
// Created by AOUFAR FARES on 24/12/2022.
//

#include "ArchiveManipulation.h"
#include "tovcFunctions.h"
#include "TofIndexFunctions.h"
#include "DataManipulation.h"
#include "student-library.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>


/* this library will manage the index moyenne
 *1 arhcive the current year
 *2 some intermediate functions to use in the archive function
 *3 the transfert function
 *
 *
 */


void setEnteteMoyenne(FichierTofMoyenne *fichier, int pos, int value) {
    if (pos == 1) {
        fichier->entete.LastBloc = value;
    } else if (pos == 2) {
        fichier->entete.NumberOfRecordsInserted = value;
    }
}

int getEnteteMoyenne(FichierTofMoyenne *fichier, int pos) {
    if (pos == 1) {
        return fichier->entete.LastBloc;
    } else if (pos == 2) {
        return fichier->entete.NumberOfRecordsInserted;
    } else return -1;
}

void setFileMoyenne(FichierTofMoyenne *fichier, FILE *f) {
    fichier->file = f;
}

FILE *getFileMoyenne(FichierTofMoyenne *fichier) {
    return fichier->file;
}

FichierTofMoyenne *ouvrirFichierMoyenne(char *name, char mode) {
    FichierTofMoyenne *fichier = malloc(sizeof(FichierTofMoyenne));
    if (mode == 'N') { //Nouveau fichier
        fichier->file = fopen(name, "wb+");
        setEnteteMoyenne(fichier, 1, 0);
        setEnteteMoyenne(fichier, 2, 0);
        rewind(getFileMoyenne(fichier));
        fwrite(&fichier->entete, sizeof(EnteteMoyenne), 1, getFileMoyenne(fichier));
    } else {//ancien fichier
        fichier->file = fopen(name, "rb+");
        if (getFileMoyenne(fichier) != NULL) {
            fread(&fichier->entete, sizeof(EnteteMoyenne), 1, getFileMoyenne(fichier));
        } else {
            printf("Erreur, fichier inexsistant");
        }
    }
    return fichier;
}

void fermerFichierMoyenne(FichierTofMoyenne *fichier) {
    rewind(getFileMoyenne(fichier));
    fwrite(&fichier->entete, sizeof(EnteteMoyenne), 1, getFileMoyenne(fichier));
    fclose(getFileMoyenne(fichier));
    free(fichier);
}

void lireBlocMoyenne(FichierTofMoyenne *fichier, int i, BufferTofMoyenne *buffer) {
    fseek(getFileMoyenne(fichier), sizeof(EnteteMoyenne) + sizeof(BufferTofMoyenne) * i, 0);
    fread(buffer, sizeof(BufferTofMoyenne), 1, getFileMoyenne(fichier));
}

void ecrireBlocMoyenne(FichierTofMoyenne *fichier, int i, BufferTofMoyenne *buffer) {
    fseek(getFileMoyenne(fichier), sizeof(EnteteMoyenne) + sizeof(BufferTofMoyenne) * i, 0);
    fwrite(buffer, sizeof(BufferTofMoyenne), 1, getFileMoyenne(fichier));
}
//USELESS FUNCTION

//void chargementInitialeMoyenne(FichierTofMoyenne *fichier, int n, BufferTofMoyenne *buffer) {
//
//
//    int i = 0, j = 0;
//    StudentsMoyenneArrayElement record;
//    //BufferTof buffer;
//    for (int k = 0; k < n; ++k) {
//        printf("La cle: ");
//        scanf("%f", &record.moyenne);
//        printf("L\'information: ");
//        scanf("%d", &record.i);
//        printf("\n");
//        if (j < TOF_BUFFER_SIZE) {
//            buffer->tab[j] = record;
//            j++;
//        } else {
//            buffer->nb = j - 1;
//            //fwrite(&buffer, sizeof(BufferTof), 1, getFileTof(fichier));
//            ecrireBlocMoyenne(fichier, i, buffer);
//            i++;
//            buffer->tab[0] = record;
//            j = 1;
//        }
//    }
//    buffer->nb = j - 1;
//    //fwrite(&buffer, sizeof(BufferTof), 1, getFileTof(fichier));
//    ecrireBlocMoyenne(fichier, i, buffer);
//    setEnteteMoyenne(fichier, 1, i);
//    setEnteteMoyenne(fichier, 2, n);
//}

void printFileMoyenne(FichierTofMoyenne *fichier) {

    for (int i = 0; i <= getEnteteMoyenne(fichier, 1); ++i) {
        lireBlocMoyenne(fichier, i, &bufferTofMoyenne);
        for (int j = 0; j <= bufferTofMoyenne.nb; j++) {
            printf("\nbloc: %d, position: %d Key: %f \n", bufferTofMoyenne.tab[j].i, bufferTofMoyenne.tab[j].j,
                   bufferTofMoyenne.tab[j].moyenne);
        }
    }
}

void
rechercheMoyenne(FichierTofMoyenne *archiveFileIndex, float moyenne, int *moyenneIndexI, int *moyenneIndexJ) {
    //don't forget to check if it's not erased !!!

    //TO BE CHANGED ASAP
//
//    *i = 0;
//    *j = 0;
//    int bi = 0;
//    int bs = getEnteteMoyenne(archiveFileIndex, 1) - 1;
//    int sup = 0;
//    int inf = 0;
//    bool stop = false;
//    *found = false;
//    while ((bi <= bs) && (!*(found)) && (!stop)) {
//        *i = (bi + bs) / 2;
//        lireBlocMoyenne(archiveFileIndex, *i, buffer);
//        if ((moyenne >= buffer->tab[0].moyenne) && (moyenne <= buffer->tab[buffer->nb].moyenne)) {
//            inf = 0;
//            sup = buffer->nb - 1;
//            while ((inf <= sup) && (!*(found))) {
//                *j = (inf + sup) / 2;
//                if (moyenne < buffer->tab[*j].moyenne) sup = (*j) - 1;
//                else if (moyenne > buffer->tab[*j].moyenne) inf = (*j) + 1;
//                else {
//                    *found = true;
//                }
//            }
//            if (inf > sup) {
//                *j = inf;
//                stop = true;
//            }
//        } else if ((moyenne < buffer->tab[0].moyenne)) bs = (*i) - 1;
//        else if (moyenne > buffer->tab[buffer->nb].moyenne) bi = (*i) + 1;
//    }
//    if (bi > bs) {
//        *i = bi;
//        *j = 0;
//    }



    int nonDenseIndexPos = 0;

    //Looking for rthe starting position in the indexFile
    while (moyenne <= moyenneNonDenseIndex.tab[nonDenseIndexPos].maxMoyenne) {
        nonDenseIndexPos++;
        if (nonDenseIndexPos == moyenneNonDenseIndex.nb) {
            printf("\nNo student got this mark that year\n");
            *moyenneIndexI = getEnteteMoyenne(archiveFileIndex, 1) - 1;
            lireBlocMoyenne(archiveFileIndex, *moyenneIndexI, &bufferTofMoyenne);
            *moyenneIndexJ = bufferTofMoyenne.nb - 1;
            return;
        }
    }

    *moyenneIndexI = nonDenseIndexPos;
    lireBlocMoyenne(archiveFileIndex, *moyenneIndexI, &bufferTofMoyenne);
    while (moyenne >= bufferTofMoyenne.tab[*moyenneIndexJ].moyenne) moyenneIndexJ++;
    *moyenneIndexI = bufferTofMoyenne.tab[*moyenneIndexJ].i;
    *moyenneIndexI = bufferTofMoyenne.tab[*moyenneIndexJ].j;


}

void insertionMoyenne(FichierTofMoyenne *archiveFileIndex, StudentsMoyenneArrayElement recordToBeInserted) {
    int archiveIndexI, archiveIndexJ, borneSup;
    StudentsMoyenneArrayElement container;
    rechercheMoyenne(archiveFileIndex, recordToBeInserted.moyenne, &archiveIndexI, &archiveIndexJ);

    while (archiveIndexI < getEnteteMoyenne(archiveFileIndex, 1)) {
        lireBlocMoyenne(archiveFileIndex, archiveIndexI, &bufferTofMoyenne);
        container = bufferTofMoyenne.tab[bufferTofMoyenne.nb - 1];
        borneSup = bufferTofMoyenne.nb - 1;

        while (borneSup > archiveIndexJ) {
            bufferTofMoyenne.tab[borneSup] = bufferTofMoyenne.tab[borneSup - 1];
            borneSup--;
        }
        bufferTofMoyenne.tab[archiveIndexJ] = recordToBeInserted;
        if (bufferTofMoyenne.nb < TOF_MOYENNE_BUFFER_SIZE) {
            bufferTofMoyenne.tab[bufferTofMoyenne.nb] = container;
            bufferTofMoyenne.nb++;
            ecrireBlocMoyenne(archiveFileIndex, archiveIndexI, &bufferTofMoyenne);
            //Updating the nonDenseIndexArray
            moyenneNonDenseIndex.tab[archiveIndexI].minMoyenne = bufferTofMoyenne.tab[0].moyenne;
            moyenneNonDenseIndex.tab[archiveIndexI].maxMoyenne = bufferTofMoyenne.tab[bufferTofMoyenne.nb - 1].moyenne;
            break; //So that we don't use another boolean variable
        } // NO need to use an else because if we enter this bloc the loop will stop
        ecrireBlocMoyenne(archiveFileIndex, archiveIndexI, &bufferTofMoyenne);
        //Updating the nonDenseIndexArray
        moyenneNonDenseIndex.tab[archiveIndexI].minMoyenne = bufferTofMoyenne.tab[0].moyenne;
        moyenneNonDenseIndex.tab[archiveIndexI].maxMoyenne = bufferTofMoyenne.tab[bufferTofMoyenne.nb - 1].moyenne;
        archiveIndexI++;
        archiveIndexJ = 0;
        recordToBeInserted = container;
    }
    if (archiveIndexI >= getEnteteMoyenne(archiveFileIndex, 1)) {
        bufferTofMoyenne.tab[0] = recordToBeInserted;
        bufferTofMoyenne.nb = 1;
        //Updating the nonDenseIndexArray
        moyenneNonDenseIndex.tab[archiveIndexI].minMoyenne = bufferTofMoyenne.tab[0].moyenne;
        moyenneNonDenseIndex.tab[archiveIndexI].maxMoyenne = bufferTofMoyenne.tab[bufferTofMoyenne.nb - 1].moyenne;
        ecrireBlocMoyenne(archiveFileIndex, archiveIndexI, &bufferTofMoyenne);
        setEnteteMoyenne(archiveFileIndex, 1, archiveIndexI + 1);
    }
    setEnteteMoyenne(archiveFileIndex, 2, getEnteteMoyenne(archiveFileIndex, 2) + 1);


}

void supressionMoyenne(FichierTofMoyenne *fichier, float moyenne, BufferTofMoyenne *buffer) {
    int i, j;
    StudentsMoyenneArrayElement record;
    bool found = false;
    rechercheMoyenne(fichier, moyenne, &i, &j);
    if (found) {
        lireBlocMoyenne(fichier, i, buffer);
        record = buffer->tab[buffer->nb];
        buffer->nb--;
        if (buffer->nb < 0) setEnteteMoyenne(fichier, 1, getEnteteMoyenne(fichier, 1) - 1);
        ecrireBlocMoyenne(fichier, i, buffer);
        lireBlocMoyenne(fichier, i, buffer);
        buffer->tab[j] = record;
        ecrireBlocMoyenne(fichier, i, buffer);
        setEnteteMoyenne(fichier, 2, getEnteteMoyenne(fichier, 2) - 1);
    }

}

void
createNewPrepaStudents(FichierTovc *nextYearFile, ClassIdArray *classIdArray, FichierTof *currentYearClassIndexFile,
                       int *newYearI, int *newYearJ) {
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

    classIdArray->nb = 0;
    StudentsIdArray studentsIdArray;
    studentsIdArray.nb = 0;
    StudentsNamesArray studentsNamesArray;
    studentsNamesArray.nb = 0;

    for (int k = 0; k < MAX_NUMBER_OF_PREPA_STUDENTS; ++k) {
        generateStudentId(&studentsIdArray);
    }
    for (int k = 0; k < MAX_NUMBER_OF_PREPA_STUDENTS; ++k) {
        generateStudentName(lastNamesFile, firstNamesAndGendersFile, &studentsNamesArray);
    }
    Student student;
    int level = 0;

    int indexI = 0;
    int indexJ = 0;
    int k = 0;
    *newYearI = 0;
    *newYearJ = 0;
    lireBlocTof(currentYearClassIndexFile, indexI, &bufferTofClass);

    while (bufferTofClass.tab[indexJ].id < MIN_1TH_GRADE_CLASS_ID) { //because that's the smallest classId of a 1st year class
        if (indexJ >= bufferTofClass.nb) {
            if (indexI < getEnteteTof(currentYearClassIndexFile, 1) - 1) {
                indexI++;
                lireBlocTof(currentYearClassIndexFile, indexI, &bufferTofClass);
                indexJ = 0;
            } else break;
        }

        //writing the class positions into the index
        classIdArray->tab[k].id = bufferTofClass.tab[indexJ].id;
        classIdArray->tab[k].i = *newYearI;
        classIdArray->tab[k].j = *newYearJ;


        for (int l = 0; l < STUDENT_PER_CLASS; ++l) {
            student.id = studentsIdArray.tab[k * STUDENT_PER_CLASS + l].id;
            student.class = classIdArray->tab[k].id;
            strcpy(student.fullName, studentsNamesArray.tab[k * STUDENT_PER_CLASS + l].fullName);
            student.firstNameSize = studentsNamesArray.tab[k * STUDENT_PER_CLASS + l].firstNameSize;
            student.lastNameSize = studentsNamesArray.tab[k * STUDENT_PER_CLASS + l].lastNameSize;
            student.gender = studentsNamesArray.tab[k * STUDENT_PER_CLASS + l].gender;

            level = (student.class / 100) % 10; //refactor it using variables
            getMarks(student.marks, level);

            student.isDeleted = '0';

            writeStudent(nextYearFile, &student, newYearI, newYearJ, &bufferTovcNewYear);

        }
        k++;
        indexJ++;

    }
    classIdArray->nb = k;

    setEntete(nextYearFile, 1, (*newYearI) + 1); //Total number blocs
    setEntete(nextYearFile, 2, *newYearJ); //Last position in the lastBloc
    setEntete(nextYearFile, 3, TOVC_BUFFER_SIZE * (*newYearI + 1) + (*newYearJ)); //Total number of characters in the file
    setEntete(nextYearFile, 4, 0); //number of chars deleted

    //close first names file
    fclose(firstNamesAndGendersFile);

    //close last names file
    fclose(lastNamesFile);

}

void createNewClass(ClassIdArray *classIdArray, int level, int min, int max) {
    //initialize classIdArray.nb with 0 (outside) before running this function

    int classID = 0, roomNumber = 0;

    int seed = classIdArray->tab[classIdArray->nb].id;
    if (classIdArray->nb != 0) seed += classIdArray->tab[classIdArray->nb - 1].id;

    //generate a "unique" class number
    bool found = true;
     while (found) {
        roomNumber = generate2positionInt(seed);
        if ((roomNumber >= min) && (roomNumber < max)) {
            checkRoomNumber(classIdArray, roomNumber, &found);
        }
        seed += roomNumber + seed % 47; // Don't ask us why :)
    }
    //class number has been generated. Now assign a level for this class

    classID = roomNumber + 100 * level;

    insertClassId(classIdArray, classID);

}

void archive(FichierTovc *currentYearFile, FichierTof *currentYearClassIndexFile, FichierTovc *archiveFile,
             FichierTofMoyenne *moyennefile, FichierTovc *nextYearFile, FichierTof *nextYearClassIndexFile) {
    // the file pointers will be passed as parameters in the menu
    // Testing if the file pointers are NULL will be in the MENU interface !!!

    //prepare to create new joiners to the next Year
    int newYearI = 0;
    int newYearJ = 0;
    ClassIdArray classIdArray; //to create an index for the new year at the end
    createNewPrepaStudents(nextYearFile, &classIdArray, currentYearClassIndexFile, &newYearI, &newYearJ);
    //now the first part of our new year file is filled with prepa students who just joined us in this new year

    StudentsMoyenneArray studentsMoyenneArray;
    studentsMoyenneArray.nb = 0;
    StudentsWhoFailed studentsWhoFailed;
    studentsWhoFailed.nb = 0;
    bool endOfFile = false;
    int currentYearI = 0;
    int currentYearJ = 0;
    int archiveI = 0;
    int archiveJ = 0;
    int classIndexI = 0;
    int classIndexJ = 0;
    int lastNameSize = 0;
    int firstNameSize = 0;
    int intMoyenne = 0;
    int level;
    int markWholePart;
    int markDecimalPart;
    float moyenne = 0;
    char gender;
    char markWholePartString[MARK_WHOLE_PART_LENGTH + 1];
    char markDecimalPartString[MARK_DECIMAL_PART_LENGTH + 1];
    char archiveStringBuffer[
            STUDENT_ID_SIZE + CLASS_ID_SIZE + IS_DELETED_SIZE + LASTNAME_LENGTH + FIRSTNAME_LENGTH + GENDER_SIZE +
            MAX_NUMBER_OF_SUBJECTS *
            (MARK_WHOLE_PART_LENGTH + MARK_DECIMAL_PART_LENGTH) + MAX_LAST_NAME_SIZE + MAX_FIRST_NAME_SIZE];
    Student student;
    char lastNameSizeString[LASTNAME_LENGTH + 1];
    char firstNameSizeString[FIRSTNAME_LENGTH + 1];
    char classIdString[CLASS_ID_SIZE + 1];
    char roomString[ROOM_SIZE + 1];
    char ID[STUDENT_ID_SIZE + 1];
    char fullName[MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE + 1];

    if (currentYearI == getEntete(currentYearFile, 1)) {
        if (currentYearJ == getEntete(currentYearFile, 2)) endOfFile = true;
    }

    lireBlocTof(currentYearClassIndexFile, classIndexI, &bufferTofClass);

    level = 1;
    int count = 0, numberOfClassesAtThisLevel = numberOfClassesPerLevel[level];

    if (bufferTofClass.tab[classIndexJ].id < MIN_5TH_GRADE_CLASS_ID) {
        createNewClass(&classIdArray, level, count * 100 / numberOfClassesAtThisLevel,
                       (count + 1) * 100 / numberOfClassesAtThisLevel);
        classIdArray.tab[classIdArray.nb - 1].i = newYearI;
        classIdArray.tab[classIdArray.nb - 1].j = newYearJ;

    }

    level = (bufferTofClass.tab[classIndexJ].id / 100) % 10; //Used to get the number marks in the table of marks
    int nextClassI = bufferTofClass.tab[classIndexJ + 1].i;
    int nextClassJ = bufferTofClass.tab[classIndexJ + 1].j;

    lireBloc(currentYearFile, currentYearI, &bufferTovcData);

    while (!endOfFile) {
        if ((currentYearI == nextClassI) && (currentYearJ == nextClassJ)) {
            classIndexJ++; //Normally we're considering that the index file can be fully uploaded in the buffer

            //WE HAVE TO RECHECK THIS !!!!!
            level = (bufferTofClass.tab[classIndexJ].id / 100) % 10;
            if (bufferTofClass.tab[classIndexJ].id <
                MIN_5TH_GRADE_CLASS_ID) { //Because that's the lowest id a 5th grade class can take
                //HERE
                if (count == numberOfClassesAtThisLevel) {
                    level++;
                    numberOfClassesAtThisLevel = numberOfClassesPerLevel[level];
                    count = 0;
                }
                createNewClass(&classIdArray, level + 1, count * 100 / numberOfClassesAtThisLevel,
                               (count + 1) * 100 / numberOfClassesAtThisLevel);
                classIdArray.tab[classIdArray.nb - 1].i = newYearI;
                classIdArray.tab[classIdArray.nb - 1].j = newYearJ;
                count++;
                //HERE
            }

            if (classIndexJ + 1 < bufferTofClass.nb) { // ELSE !!!!!
                nextClassI = bufferTofClass.tab[classIndexJ + 1].i;
                nextClassJ = bufferTofClass.tab[classIndexJ + 1].j;
            }
        }

        lirechaine(currentYearFile, &bufferTovcData, lastNameSizeString, LASTNAME_LENGTH, &currentYearI, &currentYearJ);
        strcpy(archiveStringBuffer, lastNameSizeString);
        student.lastNameSize = stringToInt(lastNameSizeString, LASTNAME_LENGTH);
        lastNameSize = stringToInt(lastNameSizeString, LASTNAME_LENGTH);

        lirechaine(currentYearFile, &bufferTovcData, firstNameSizeString, FIRSTNAME_LENGTH, &currentYearI,
                   &currentYearJ);
        strcat(archiveStringBuffer, firstNameSizeString);
        student.firstNameSize = stringToInt(firstNameSizeString, FIRSTNAME_LENGTH);
        firstNameSize = stringToInt(firstNameSizeString, FIRSTNAME_LENGTH);

        //we don't have to extract the level from the class ID because we're already having it from the index
        lirechaine(currentYearFile, &bufferTovcData, classIdString, CLASS_ID_SIZE, &currentYearI, &currentYearJ);
        classIdString[CLASS_ID_SIZE] = '\0';
        strcat(archiveStringBuffer, classIdString);
        student.class = classIdArray.tab[classIdArray.nb - 1].id;

        lirechaine(currentYearFile, &bufferTovcData, ID, STUDENT_ID_SIZE, &currentYearI, &currentYearJ);
        ID[STUDENT_ID_SIZE] = '\0';
        strcat(archiveStringBuffer, ID);
        student.id = stringToInt(ID, STUDENT_ID_SIZE);

        //now we'll be at the effacement char so we'll have to test it to see if we're going to archibe this student or not
        if (bufferTovcData.tab[currentYearJ] == '1') {
            //skip to the field of "firstName"
            skip(currentYearFile, IS_DELETED_SIZE +
                                  MARK_LENGTH * numberOfSubjectsPerLevel[level] + firstNameSize + lastNameSize +
                                  GENDER_SIZE, &currentYearI, &currentYearJ);
            //We also have to test if it's not the end of the file
            if (currentYearI == getEntete(currentYearFile, 1)) {
                if (currentYearJ == getEntete(currentYearFile, 2)) endOfFile = true;
            }
            continue; // SAFELY jump to the next iteration
        }
        student.isDeleted = '0'; // because if we reached this place it means that this student isn't deleted

        //We're going to update the classIdArray here to make sur that the student isn't deleted and to
        //avoid conflicts

        //IF WE WANT WE CAN ADD THE DELETED CHAR BUT IT'S USELESS

        skip(currentYearFile, IS_DELETED_SIZE, &currentYearI, &currentYearJ);
        moyenne = 0;
        for (int k = 0; k < numberOfSubjectsPerLevel[level]; ++k) {
            lirechaine(currentYearFile, &bufferTovcData, markWholePartString, MARK_WHOLE_PART_LENGTH, &currentYearI,
                       &currentYearJ);
            markWholePart = stringToInt(markWholePartString, MARK_WHOLE_PART_LENGTH);

            lirechaine(currentYearFile, &bufferTovcData, markDecimalPartString, MARK_DECIMAL_PART_LENGTH, &currentYearI,
                       &currentYearJ);
            markDecimalPart = stringToInt(markDecimalPartString, MARK_DECIMAL_PART_LENGTH);

            moyenne += (float) markWholePart + (float) markDecimalPart / 100;
        }
        moyenne /= (float) numberOfSubjectsPerLevel[level];
        //new marks for the new year
        getMarks(student.marks, level);
        //to make the string -> int conversion easier
        intMoyenne = moyenne * 100;
        markWholePart = intMoyenne / 100;
        markDecimalPart = intMoyenne % 100;
        intToString(markWholePartString, markWholePart, MARK_WHOLE_PART_LENGTH);
        intToString(markDecimalPartString, markDecimalPart, MARK_DECIMAL_PART_LENGTH);

        markDecimalPartString[MARK_DECIMAL_PART_LENGTH] = '\0';
        markWholePartString[MARK_WHOLE_PART_LENGTH] = '\0';
        strcat(archiveStringBuffer, markWholePartString);
        strcat(archiveStringBuffer, markDecimalPartString);
        insertStudentMoyenneInArray(&studentsMoyenneArray, archiveI, archiveJ, moyenne);

        lirechaine(currentYearFile, &bufferTovcData, fullName, firstNameSize + lastNameSize, &currentYearI,
                   &currentYearJ);
        fullName[firstNameSize + lastNameSize] = '\0';
        strcat(archiveStringBuffer, fullName);
        strcpy(student.fullName, fullName);
        lirechaine(currentYearFile, &bufferTovcData, &gender, GENDER_SIZE, &currentYearI,
                   &currentYearJ);
        strcat(archiveStringBuffer, &gender);
        student.gender = gender;

        ecrireChaine(archiveFile, &bufferTovcArchive, archiveStringBuffer, (int) strlen(archiveStringBuffer), &archiveI,
                     &archiveJ);
        printf("class: %d\tId: %d\tlastNameSize: %d\tfirstNameSize: %d\tname: %s", student.class, student.id, student.lastNameSize, student.firstNameSize, student.fullName);

        /*
        if (currentYearI == getEntete(currentYearFile, 1)) {
            if (currentYearJ == getEntete(currentYearFile, 2)) endOfFile = true;
        }

        //Check wether the student passed, failed or graduated from the school
        if (student.class >= MIN_5TH_GRADE_CLASS_ID + 100) { //was a 5th grade student
            if (moyenne < 10) {
                student.class -= 100;
                if (studentsWhoFailed.nb == 0)
                    studentsWhoFailed.tab[0] = student;
                else studentsWhoFailed.tab[studentsWhoFailed.nb] = student;
                studentsWhoFailed.nb++;
            }
        } else { //CHANGE THE OREDER OF THE CONDITIONS
            if (moyenne < 10) {
                student.class -= 100;
                if (studentsWhoFailed.nb == 0)
                    studentsWhoFailed.tab[0] = student;
                else studentsWhoFailed.tab[studentsWhoFailed.nb] = student;
                studentsWhoFailed.nb++;
            } else {
                writeStudent(nextYearFile, &student, &newYearI, &newYearJ, &bufferTovcNewYear);
            }
        }
         */

    }
    // This should go outside the loop !!!
    ecrireBloc(archiveFile, archiveI, &bufferTovcArchive);
    setEntete(archiveFile, 1, archiveI + 1);
    setEntete(archiveFile, 2, archiveJ);
    setEntete(archiveFile, 4, 0);

    //function to create the indexFile

    int i1 = 0, j1 = 0;
    //BufferTof bufferTovcData;
    for (int k = 0; k < studentsMoyenneArray.nb; ++k) {
        if (j1 < TOF_MOYENNE_BUFFER_SIZE) {
            bufferTofMoyenne.tab[j1] = studentsMoyenneArray.tab[k];
            j1++;
        } else {
            bufferTofMoyenne.nb = j1;
            moyenneNonDenseIndex.tab[i1].minMoyenne = bufferTofMoyenne.tab[0].moyenne;
            moyenneNonDenseIndex.tab[i1].maxMoyenne = bufferTofMoyenne.tab[j1 - 1].moyenne;
            ecrireBlocMoyenne(moyennefile, i1, &bufferTofMoyenne);
            i1++;
            bufferTofMoyenne.tab[0] = studentsMoyenneArray.tab[k];
            j1 = 1;
        }
    }
    bufferTofMoyenne.nb = j1;
    moyenneNonDenseIndex.tab[i1].minMoyenne = bufferTofMoyenne.tab[0].moyenne;
    moyenneNonDenseIndex.tab[i1].maxMoyenne = bufferTofMoyenne.tab[j1 - 1].moyenne;
    moyenneNonDenseIndex.nb;
    ecrireBlocMoyenne(moyennefile, i1, &bufferTofMoyenne);

    setEnteteMoyenne(moyennefile, 1, i1 + 1);
    setEnteteMoyenne(moyennefile, 2, studentsMoyenneArray.nb);

    //Create the next year index file
    i1 = 0;
    j1 = 0;
    IndexRecord record;
    for (int k = 0; k < classIdArray.nb; ++k) {
        record.id = classIdArray.tab[k].id;
        record.isDeleted = false;
        record.i = classIdArray.tab[k].i;
        record.j = classIdArray.tab[k].j;
        if (j1 < TOF_BUFFER_SIZE) {
            bufferTofClass.tab[j1] = record;
            j1++;
        } else {
            bufferTofClass.nb = j1;
            ecrireBlocTof(nextYearClassIndexFile, i1, &bufferTofClass);
            i1++;
            bufferTofClass.tab[0] = record;
            j1 = 1;
        }
    }
    bufferTofClass.nb = j1;
    ecrireBlocTof(nextYearClassIndexFile, i1, &bufferTofClass);
    setEnteteTof(nextYearClassIndexFile, 1, i1 + 1);
    setEnteteTof(nextYearClassIndexFile, 2, classIdArray.nb);
    updateNumberOfClassesPerLevel(&bufferTofClass);

    //========= adding students who failed
    level = 0;
    int studentWhoFailedI = 0, classIdArrayPos = 0, firstClassOfThisLevelPosition = 0, firstClassOfTheNextLevelPosition = numberOfClassesPerLevel[level];

    while (studentWhoFailedI < studentsWhoFailed.nb) {
        if (studentsWhoFailed.tab[studentWhoFailedI].class > (level + 1) * 100) {

            level = (studentsWhoFailed.tab[studentWhoFailedI].class / 100) % 10;

            firstClassOfThisLevelPosition = firstClassOfTheNextLevelPosition;
            firstClassOfTheNextLevelPosition += numberOfClassesPerLevel[level];
        }
        student.class = classIdArray.tab[classIdArrayPos].id;
        insertStudent(nextYearFile, nextYearClassIndexFile, student);
        classIdArrayPos++;
        if (classIdArrayPos == firstClassOfTheNextLevelPosition) classIdArrayPos = firstClassOfThisLevelPosition;

        classIdArrayPos++;
    }

}


void
searchStudentMoyenneInArray(StudentsMoyenneArray *studentsMoyenneArray, int archiveI, int archiveJ, float moyenne,
                            int *k) {
    //we won't need the found variable because the values will be repetetive
    if (studentsMoyenneArray->nb > 0) {
        while ((*k < studentsMoyenneArray->nb)) {
            // YOU HAVE DONE ALL OF THAT FOR NOTHING BECAUSE THE DATA COMES IN AN INCREASING WAY !!!
            if (moyenne == studentsMoyenneArray->tab[*k].moyenne) {
                if (archiveI == studentsMoyenneArray->tab[*k].i) {
                    if (archiveJ > studentsMoyenneArray->tab[*k].j) (*k)++; else break;
                } else if (archiveI > studentsMoyenneArray->tab[*k].i) (*k)++; else break;
            } else if (moyenne > studentsMoyenneArray->tab[*k].moyenne) (*k)++;
            else break;
        }

    } else {
        *k = 0;
    }
}

void
insertStudentMoyenneInArray(StudentsMoyenneArray *studentsMoyenneArray, int archiveI, int archiveJ, float moyenne) {
    //insertionTof with delays to keep the order in the studentsIdArray
    if (studentsMoyenneArray->nb <= 0) {
        studentsMoyenneArray->tab[0].moyenne = moyenne;
        studentsMoyenneArray->tab[0].i = archiveI;
        studentsMoyenneArray->tab[0].j = archiveJ;
        studentsMoyenneArray->nb++;
    } else {
        int i = 0;
        searchStudentMoyenneInArray(studentsMoyenneArray, archiveI, archiveJ, moyenne, &i);
        //we have to recheck this
        if (moyenne < studentsMoyenneArray->tab[i].moyenne) {
            for (int k = studentsMoyenneArray->nb; k >= i; --k) {
                studentsMoyenneArray->tab[k] = studentsMoyenneArray->tab[k - 1];
            }
        }
        studentsMoyenneArray->tab[i].moyenne = moyenne;
        studentsMoyenneArray->tab[i].i = archiveI;
        studentsMoyenneArray->tab[i].j = archiveJ;
        studentsMoyenneArray->nb++;

    }

}

void insertStudentMoyenneWithoutSearchingInArray(StudentsMoyenneArray *studentsMoyenneArray, float moyenne, int i) {
    //insertionTof with delays to keep the order in the studentsIdArray
    if (studentsMoyenneArray->nb <= 0) {
        studentsMoyenneArray->tab[0].moyenne = moyenne;
        studentsMoyenneArray->nb++;
    } else {
        if (moyenne < studentsMoyenneArray->tab[i].moyenne) {
            for (int k = studentsMoyenneArray->nb; k > i; --k) {
                studentsMoyenneArray->tab[k] = studentsMoyenneArray->tab[k - 1];
            }
        }
        studentsMoyenneArray->tab[i].moyenne = moyenne;
        studentsMoyenneArray->nb++;

    }

}

void listerParArchive(FichierTovc *archiveFile, FichierTofMoyenne *archiveIndexFile, float moyenne) {
    int moyenneIndexI = 0;
    int moyenneIndexJ = 0;
    int archiveFileI;
    int archiveFileJ;
    int nonDenseIndexPos = 0;

    //Looking for rthe starting position in the indexFile
    while (moyenne < moyenneNonDenseIndex.tab[nonDenseIndexPos].minMoyenne) {
        nonDenseIndexPos++;
        if (nonDenseIndexPos == moyenneNonDenseIndex.nb) {
            printf("\nNo student got this mark that year\n");
            return;
        }
    }

    moyenneIndexI = nonDenseIndexPos;
    lireBlocMoyenne(archiveIndexFile, moyenneIndexI, &bufferTofMoyenne);
    while (moyenne < bufferTofMoyenne.tab[moyenneIndexJ].moyenne) moyenneIndexJ++;
    while (moyenneIndexI < getEnteteMoyenne(archiveIndexFile, 1)) {

        if (archiveFileI != bufferTofMoyenne.tab[moyenneIndexJ].i) {
            archiveFileI = bufferTofMoyenne.tab[moyenneIndexJ].i;
            lireBloc(archiveFile, archiveFileI, &bufferTovcArchive);
        }
        archiveFileJ = bufferTofMoyenne.tab[moyenneIndexJ].j;

        printStudentInArchiveFile(archiveFile, &archiveFileI, &archiveFileJ);

        moyenneIndexJ++;
        if (moyenneIndexJ >= bufferTofMoyenne.nb) {
            if (moyenneIndexI == getEnteteMoyenne(archiveIndexFile, 1) - 1) break;
            //We're using a break so that we don't waste a boolean
            moyenneIndexJ = 0;
            moyenneIndexI++;
            lireBlocMoyenne(archiveIndexFile, moyenneIndexI, &bufferTofMoyenne);
        }

    }
}

void printStudentInArchiveFile(FichierTovc *archiveFile, int *archiveFileI, int *archiveFileJ) {

    char stringBuffer[MAX_LAST_NAME_SIZE + MAX_FIRST_NAME_SIZE + 1];
    char lastName[MAX_LAST_NAME_SIZE];
    char firstName[MAX_FIRST_NAME_SIZE];
    int markWholePart, markDecimalPart;
    Student student;

    //LASTNAME LENGTH
    lirechaine(archiveFile, &bufferTovcArchive, stringBuffer, LASTNAME_LENGTH, archiveFileI, archiveFileJ);
    student.lastNameSize = stringToInt(stringBuffer, LASTNAME_LENGTH);

    //FIRSTNAME LENGTH
    lirechaine(archiveFile, &bufferTovcArchive, stringBuffer, FIRSTNAME_LENGTH, archiveFileI, archiveFileJ);
    student.firstNameSize = stringToInt(stringBuffer, FIRSTNAME_LENGTH);

    //CLASS_ID
    lirechaine(archiveFile, &bufferTovcArchive, stringBuffer, CLASS_ID_SIZE, archiveFileI, archiveFileJ);
    if (stringBuffer[0] == 'p') { //CHANGE IT'S PLACE
        stringBuffer[0] = '0';
    }
    student.class = stringToInt(stringBuffer, CLASS_ID_SIZE);

    //STUDENT_ID
    lirechaine(archiveFile, &bufferTovcArchive, stringBuffer, STUDENT_ID_SIZE, archiveFileI, archiveFileJ);
    student.id = stringToInt(stringBuffer, STUDENT_ID_SIZE);

    //MOYENNE
    lirechaine(archiveFile, &bufferTovcData, stringBuffer, MARK_WHOLE_PART_LENGTH, archiveFileI,
               archiveFileJ);
    markWholePart = stringToInt(stringBuffer, MARK_WHOLE_PART_LENGTH);
    lirechaine(archiveFile, &bufferTovcData, stringBuffer, MARK_DECIMAL_PART_LENGTH, archiveFileI,
               archiveFileJ);
    markDecimalPart = stringToInt(stringBuffer, MARK_DECIMAL_PART_LENGTH);
    //Where just putting it int the first element of the marks array so that we won't create another Student Structer
    student.marks[0] = (float) markWholePart + (float) markDecimalPart / 100;

    //FULLNAME
    lirechaine(archiveFile, &bufferTovcArchive, stringBuffer, student.firstNameSize + student.lastNameSize,
               archiveFileI, archiveFileJ);
    strcpy(student.fullName, stringBuffer);

    //GENDER
    lirechaine(archiveFile, &bufferTovcArchive, stringBuffer, GENDER_SIZE, archiveFileI, archiveFileJ);
    strcpy(&student.gender, stringBuffer);

    strncpy(lastName, student.fullName, student.lastNameSize);
    strncpy(firstName, student.fullName + student.lastNameSize, student.firstNameSize);

    //Printing the student
    printf("\nLast Name: %s, First Name: %s, ID: %d, ClassId: %d, Moyenne: %f, Gender: %c\n", lastName, firstName,
           student.class, student.id, student.marks[0], student.gender);
}

void insertStudentInArchive(FichierTovc *archiveFile, FichierTofMoyenne *archiveFileIndex, Student student) {

    int archiveFileI = getEntete(archiveFile, 1) - 1;
    int archiveFileJ = getEntete(archiveFile, 2);
    StudentsMoyenneArrayElement recordToBeInserted;
    recordToBeInserted.moyenne = student.marks[0];
    if (archiveFileJ == TOVC_BUFFER_SIZE) {
        archiveFileJ = 0;
        archiveFileI++;
    }
    recordToBeInserted.i = archiveFileI;
    recordToBeInserted.j = archiveFileJ;

    lireBloc(archiveFile, archiveFileI, &bufferTovcArchive);

    char container1[4];//used to do the int => string conversion
    int totalStudentSize = FIRSTNAME_LENGTH + LASTNAME_LENGTH + CLASS_ID_SIZE + STUDENT_ID_SIZE + IS_DELETED_SIZE
                           + MARK_LENGTH + student.firstNameSize
                           + student.lastNameSize + GENDER_SIZE;
    char stringBuffer[totalStudentSize + 1];
    stringBuffer[totalStudentSize] = '\0';

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
    strcpy(classIDString, "XXX");

    strcat(stringBuffer, classIDString);
    //Write ID
    char studentIdString[STUDENT_ID_SIZE + 1];
    strcpy(studentIdString, "XXXX");

    strcat(stringBuffer, studentIdString);

    //Write isDeleted
    char isDeletedString[IS_DELETED_SIZE + 1];
    isDeletedString[0] = student.isDeleted;
    isDeletedString[1] = '\0';
    strcat(stringBuffer, isDeletedString);
    //Write marks array
    int level = (student.class / 100) % 10;
    int markWholePart;
    int markDecimalPart;
    int intMark;
    char markWholePartString[MARK_WHOLE_PART_LENGTH + 1];
    char markDecimalPartString[MARK_DECIMAL_PART_LENGTH + 1];

    intMark = student.marks[0] * 100;
    markWholePart = intMark / 100;
    markDecimalPart = intMark % 100;

    sprintf(markWholePartString, "%d%d", (markWholePart / 10) % 10, markWholePart % 10);
    sprintf(markDecimalPartString, "%d%d", (markDecimalPart / 10) % 10, markDecimalPart % 10);

    strcat(stringBuffer, markWholePartString);
    strcat(stringBuffer, markDecimalPartString);


    //Write Full name
    strcat(stringBuffer, student.fullName);

    //Write gender
    strcat(stringBuffer, &student.gender);


    ecrireChaine(archiveFile, &bufferTovcArchive, stringBuffer, totalStudentSize, &archiveFileI,
                 &archiveFileJ);
    if (archiveFileI >= getEntete(archiveFile, 1)) {
        setEntete(archiveFile, 1, archiveFileI + 1);
    }
    insertionMoyenne(archiveFileIndex, recordToBeInserted);


}

void loadTheNonDenseIndex(FichierTofMoyenne *archiveIndex) {
    int archiveIndexI = 0;
    while (archiveIndexI < getEnteteMoyenne(archiveIndex, 1)) {
        lireBlocMoyenne(archiveIndex, archiveIndexI, &bufferTofMoyenne);
        moyenneNonDenseIndex.tab[archiveIndexI].minMoyenne = bufferTofMoyenne.tab[0].moyenne;
        moyenneNonDenseIndex.tab[archiveIndexI].maxMoyenne = bufferTofMoyenne.tab[bufferTofMoyenne.nb - 1].moyenne;
    }
    moyenneNonDenseIndex.nb = archiveIndexI;
}

void printArchiveFile(FichierTovc *archiveFile) {
    int i = 0, j = 0;
    Student student;

    char firstNameSize[FIRSTNAME_LENGTH + 1];
    char lastNameSize[LASTNAME_LENGTH + 1];
    char classID[CLASS_ID_SIZE + 1];
    char ID[STUDENT_ID_SIZE + 1];
    char fullName[MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE + 1];
    char mark[MARK_LENGTH + 1];

    lireBloc(archiveFile, i, &bufferTovcData);

    while (i < getEntete(archiveFile, 1) - 1 || j < getEntete(archiveFile, 2)) {
        //Reading all information of the current student from the file:

        //Reading first name and last name sizes
        lirechaine(archiveFile, &bufferTovcData, firstNameSize, FIRSTNAME_LENGTH, &i, &j);
        student.firstNameSize = stringToInt(firstNameSize, FIRSTNAME_LENGTH);
        lirechaine(archiveFile, &bufferTovcData, lastNameSize, LASTNAME_LENGTH, &i, &j);
        student.lastNameSize = stringToInt(lastNameSize, LASTNAME_LENGTH);

        //Reading the class ID
        lirechaine(archiveFile, &bufferTovcData, classID, CLASS_ID_SIZE, &i, &j);
        if (classID[0] == 'p') classID[0] = '0';
        student.class = stringToInt(classID, CLASS_ID_SIZE);

        //Reading the student ID
        lirechaine(archiveFile, &bufferTovcData, ID, STUDENT_ID_SIZE, &i, &j);
        student.id = stringToInt(ID, STUDENT_ID_SIZE);

        //Reading the isDeleted character
        student.isDeleted = bufferTovcData.tab[j];
        j++;
        if (j == TOVC_BUFFER_SIZE) {
            i++;
            lireBloc(archiveFile, i, &bufferTovcData);
            j = 0;
        }

        //Reading the marks

        lirechaine(archiveFile, &bufferTovcData, mark, MARK_LENGTH, &i, &j);
        student.marks[0] = stringToInt(mark, MARK_LENGTH) / 100.0;


        //Reading last name and first name
        lirechaine(archiveFile, &bufferTovcData, student.fullName, student.lastNameSize + student.firstNameSize, &i,
                   &j);
        student.fullName[student.lastNameSize + student.firstNameSize] = '\0';

        //Reading the gender character
        student.gender = bufferTovcData.tab[j];
        j++;
        if (j == TOVC_BUFFER_SIZE) {
            i++;
            lireBloc(archiveFile, i, &bufferTovcData);
            j = 0;
        }

        printf("class: %d\tID: %d\tname: %s\tMoyenne: %f\n", student.class, student.id, student.fullName, student.marks[0]);

    }
}