//
// Created by AOUFAR FARES on 24/12/2022.
//

#ifndef TP1_SFSD_ARCHIVEMANIPULATION_H
#define TP1_SFSD_ARCHIVEMANIPULATION_H


#include <stdbool.h>
#include <stdio.h>
#include "DataManipulation.h"
#include "TofIndexFunctions.h"

#define TOF_MOYENNE_BUFFER_SIZE 55

typedef struct {
    int LastBloc;
    int NumberOfRecordsInserted;
}EnteteMoyenne;

typedef struct {
    FILE* file;
    EnteteMoyenne entete;
}FichierTofMoyenne;

typedef struct {
    float moyenne;//the moyenne
    int i;//number of the bloc
    int j; //position in the bloc
} StudentsMoyenneArrayElement;

typedef struct {
    StudentsMoyenneArrayElement tab[TOF_MOYENNE_BUFFER_SIZE];
    int nb; //number of records per buffer or bloc
}BufferTofMoyenne;

typedef struct {
    StudentsMoyenneArrayElement tab[MAX_STUDENTS_PER_YEAR];
    int nb; //number of elements within the array
} StudentsMoyenneArray;

typedef struct {
    float minMoyenne;
    float maxMoyenne;
}NonDenseIndexElement;

typedef struct {
    NonDenseIndexElement tab[MAX_STUDENTS_PER_YEAR/TOF_BUFFER_SIZE + TOF_BUFFER_SIZE];
    int nb;
}MoyenneNonDenseIndex;

extern BufferTofMoyenne bufferTofMoyenne;
extern BufferTovc bufferTovcArchive;
extern MoyenneNonDenseIndex moyenneNonDenseIndex;
extern int numberOfClassesPerLevel[6];

void setEnteteMoyenne(FichierTofMoyenne *fichier, int pos, int value);

int getEnteteMoyenne(FichierTofMoyenne *fichier, int pos);

void setFileMoyenne(FichierTofMoyenne *fichier, FILE *f);

FILE *getFileMoyenne(FichierTofMoyenne *fichier);

FichierTofMoyenne *ouvrirFichierMoyenne(char *name, char mode);

void fermerFichierMoyenne(FichierTofMoyenne *fichier);

void lireBlocMoyenne(FichierTofMoyenne* fichier, int i, BufferTofMoyenne* buffer);

void ecrireBlocMoyenne(FichierTofMoyenne* fichier, int i, BufferTofMoyenne* buffer);

void printFileMoyenne(FichierTofMoyenne* fichier);

void chargementInitialeMoyenne(FichierTofMoyenne *fichier, int n, BufferTofMoyenne* buffer);

void rechercheMoyenne(FichierTofMoyenne *archiveFileIndex, float moyenne, int *archiveFileI, int *archiveFileJ);

void insertionMoyenne(FichierTofMoyenne *archiveFileIndex, StudentsMoyenneArrayElement recordToBeInserted);

void supressionMoyenne(FichierTofMoyenne* fichier, float moyenne, BufferTofMoyenne* buffer);

void searchStudentMoyenneInArray(StudentsMoyenneArray *studentsMoyenneArray, int archiveI, int archiveJ, float moyenne, int *k);

void insertStudentMoyenneInArray(StudentsMoyenneArray *studentsMoyenneArray, int archiveI, int archiveJ,float moyenne);

void insertStudentMoyenneWithoutSearchingInArray(StudentsMoyenneArray *studentsMoyenneArray, float moyenne, int i);

void createNewClass(ClassIdArray *classIdArray, int level, int min, int max);

void printStudentInArchiveFile(FichierTovc *archiveFile, int* archiveFileI, int* archiveFileJ);

void insertStudentInArchive(FichierTovc* archiveFile, FichierTofMoyenne* archiveFileIndex,Student student);

void printArchiveFile(FichierTovc *archiveFile);

void archive(FichierTovc *currentYearFile, FichierTof *currentYearClassIndexFile, FichierTovc *archiveFile,
             FichierTofMoyenne *moyennefile, FichierTovc *nextYearFile, FichierTof *nextYearClassIndexFile);





#endif //TP1_SFSD_ARCHIVEMANIPULATION_H
