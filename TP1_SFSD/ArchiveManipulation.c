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
    FichierTofMoyenne *fichier = malloc(sizeof(fichier));
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
            printf("\nbloc: %d, position: %d Key: %f \n", bufferTofMoyenne.tab[j].i, bufferTofMoyenne.tab[j].j,bufferTofMoyenne.tab[j].moyenne);
        }
    }
}

void rechercheMoyenne(FichierTofMoyenne *fichier, float moyenne, int *i, int *j, BufferTofMoyenne *buffer, bool *found) {
    //don't forget to check if it's not erased !!!

    //TO BE CHANGED ASAP

    *i = 0;
    *j = 0;
    int bi = 0;
    int bs = getEnteteMoyenne(fichier, 1) - 1;
    int sup = 0;
    int inf = 0;
    bool stop = false;
    *found = false;
    while ((bi <= bs) && (!*(found)) && (!stop)) {
        *i = (bi + bs) / 2;
        lireBlocMoyenne(fichier, *i, buffer);
        if ((moyenne >= buffer->tab[0].moyenne) && (moyenne <= buffer->tab[buffer->nb].moyenne)) {
            inf = 0;
            sup = buffer->nb - 1;
            while ((inf <= sup) && (!*(found))) {
                *j = (inf + sup) / 2;
                if (moyenne < buffer->tab[*j].moyenne) sup = (*j) - 1;
                else if (moyenne > buffer->tab[*j].moyenne) inf = (*j) + 1;
                else {
                    *found = true;
                }
            }
            if (inf > sup) {
                *j = inf;
                stop = true;
            }
        } else if ((moyenne < buffer->tab[0].moyenne)) bs = (*i) - 1;
        else if (moyenne > buffer->tab[buffer->nb].moyenne) bi = (*i) + 1;
    }
    if (bi > bs) {
        *i = bi;
        *j = 0;
    }

}

void insertionMoyenne(FichierTofMoyenne *fichier, StudentsMoyenneArrayElement record, BufferTofMoyenne *buffer) {

    lireBlocMoyenne(fichier, getEnteteMoyenne(fichier, 1), buffer);
    if (buffer->nb < TOF_BUFFER_SIZE - 1) {
        buffer->tab[buffer->nb] = record;
        buffer->nb++;
    } else {
        buffer->tab[0] = record;
        buffer->nb = 0;
        setEnteteMoyenne(fichier, 1, getEnteteMoyenne(fichier, 1));
    }
    ecrireBlocMoyenne(fichier, getEnteteMoyenne(fichier, 1), buffer);
    setEnteteMoyenne(fichier, 2, getEnteteMoyenne(fichier, 2) + 1);

}

void supressionMoyenne(FichierTofMoyenne *fichier, float moyenne, BufferTofMoyenne *buffer) {
    int i, j;
    StudentsMoyenneArrayElement record;
    bool found = false;
    rechercheMoyenne(fichier, moyenne, &i, &j, buffer, &found);
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

void archive(FichierTovc *currentYearFile, FichierTof *classIndexFile, FichierTovc *archiveFile,
             FichierTofMoyenne *moyennefile) {
    // the file pointers will be passed as parameters in the menu
    // Testing if the file pointers are NULL will be in the MENU interface !!!
    StudentsMoyenneArray studentsMoyenneArray;
    studentsMoyenneArray.nb = 0;
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
    int markWholePart;
    int markDecimalPart;
    float moyenne = 0;
    char gender;
    char markWholePartString[MARK_WHOLE_PART_LENGTH + 1];
    char markDecimalPartString[MARK_DECIMAL_PART_LENGTH + 1];
    char stringBuffer[
            STUDENT_ID_SIZE + CLASS_ID_SIZE + IS_DELETED_SIZE + LASTNAME_LENGTH + FIRSTNAME_LENGTH + GENDER_SIZE +
            MAX_NUMBER_OF_SUBJECTS *
            (MARK_WHOLE_PART_LENGTH + MARK_DECIMAL_PART_LENGTH) + MAX_LAST_NAME_SIZE + MAX_FIRST_NAME_SIZE];
    char lastNameSizeString[LASTNAME_LENGTH + 1];
    char firstNameSizeString[FIRSTNAME_LENGTH + 1];
    char classID[CLASS_ID_SIZE + 1];
    char ID[STUDENT_ID_SIZE + 1];
    char fullName[MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE + 1];


    if (currentYearI == getEntete(currentYearFile, 1)) {
        if (currentYearJ == getEntete(currentYearFile, 2)) endOfFile = true;
    }

    lireBlocTof(classIndexFile, classIndexI, &bufferTofClass);
    int level = (bufferTofClass.tab[classIndexJ].id / 100) % 10;
    int nextClassI = bufferTofClass.tab[classIndexJ + 1].i;
    int nextClassJ = bufferTofClass.tab[classIndexJ + 1].j;

    lireBloc(currentYearFile, currentYearI, &bufferTovcData);
    while (!endOfFile) {
        if ((currentYearI == nextClassI) && (currentYearJ == nextClassJ)) {
            classIndexJ++;
            level = (bufferTofClass.tab[classIndexJ].id / 100) % 10;
            if (classIndexJ + 1 < bufferTofClass.nb) {
                nextClassI = bufferTofClass.tab[classIndexJ + 1].i;
                nextClassJ = bufferTofClass.tab[classIndexJ + 1].j;
            }
        }

        lirechaine(currentYearFile, &bufferTovcData, lastNameSizeString, LASTNAME_LENGTH, &currentYearI, &currentYearJ);
        strcpy(stringBuffer, lastNameSizeString);
        lastNameSize = stringToInt(lastNameSizeString, LASTNAME_LENGTH);
        lirechaine(currentYearFile, &bufferTovcData, firstNameSizeString, FIRSTNAME_LENGTH, &currentYearI,
                   &currentYearJ);
        strcat(stringBuffer, firstNameSizeString);
        firstNameSize = stringToInt(firstNameSizeString, FIRSTNAME_LENGTH);
        //we don't have to extract the level from the class ID because we're already having it from the index
        lirechaine(currentYearFile, &bufferTovcData, classID, CLASS_ID_SIZE, &currentYearI, &currentYearJ);
        strcat(stringBuffer, classID);

        lirechaine(currentYearFile, &bufferTovcData, ID, STUDENT_ID_SIZE, &currentYearI, &currentYearJ);
        strcat(stringBuffer, ID);

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

            moyenne += (float) markWholePart + (float) markDecimalPart / MARK_DECIMAL_PART_LENGTH;
        }
        moyenne /= (float) numberOfSubjectsPerLevel[level];
        //to make the string -> int conversion easier
        intMoyenne = (int) moyenne * 100;
        markWholePart = intMoyenne / 100;
        markDecimalPart = intMoyenne % 100;
        intToString(markWholePartString, markWholePart, MARK_WHOLE_PART_LENGTH);
        intToString(markDecimalPartString, markDecimalPart, MARK_DECIMAL_PART_LENGTH);
//
//        sprintf(markWholePartString, "%d%d", (markWholePart / 10) % 10, markWholePart % 10);
//        sprintf(markDecimalPartString, "%d%d", (markDecimalPart / 10) % 10, markDecimalPart % 10);
        strcat(stringBuffer, markWholePartString);
        strcat(stringBuffer, markDecimalPartString);
        insertStudentMoyenneInArray(&studentsMoyenneArray, archiveI, archiveJ, moyenne);

        lirechaine(currentYearFile, &bufferTovcData, fullName, MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE, &currentYearI,
                   &currentYearJ);
        strcat(stringBuffer, fullName);
        lirechaine(currentYearFile, &bufferTovcData, &gender, GENDER_SIZE, &currentYearI,
                   &currentYearJ);
        strcat(stringBuffer, &gender);

        ecrireChaine(archiveFile, &bufferTovcArchive, stringBuffer, (int)strlen(stringBuffer), &archiveI, &archiveJ);
        ecrireBloc(archiveFile, archiveI, &bufferTovcArchive);
        setEntete(archiveFile, 3, getEntete(archiveFile, 3) + (int)strlen(stringBuffer));

        if (currentYearI == getEntete(currentYearFile, 1)) {
            if (currentYearJ == getEntete(currentYearFile, 2)) endOfFile = true;
        }

    }
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
            ecrireBlocMoyenne(moyennefile, i1, &bufferTofMoyenne);
            i1++;
            bufferTofMoyenne.tab[0] = studentsMoyenneArray.tab[k];
            j1 = 1;
        }
    }
    bufferTofMoyenne.nb = j1;
    ecrireBlocMoyenne(moyennefile, i1, &bufferTofMoyenne);
    setEnteteMoyenne(moyennefile, 1, i1 + 1);
    setEnteteMoyenne(moyennefile, 2, studentsMoyenneArray.nb);
}

void
searchStudentMoyenneInArray(StudentsMoyenneArray *studentsMoyenneArray, int archiveI, int archiveJ, float moyenne, int *k) {
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