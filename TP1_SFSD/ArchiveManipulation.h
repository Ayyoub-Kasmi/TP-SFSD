//
// Created by AOUFAR FARES on 24/12/2022.
//

#ifndef TP1_SFSD_ARCHIVEMANIPULATION_H
#define TP1_SFSD_ARCHIVEMANIPULATION_H


#include <stdbool.h>
#include <stdio.h>
#include "DataManipulation.h"

#define TOF_MOYENNE_BUFFER_SIZE 35

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

extern BufferTofMoyenne bufferTofMoyenne;
extern BufferTovc bufferTovcArchive;

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

void rechercheMoyenne(FichierTofMoyenne *fichier, float moyenne, int *i, int *j, BufferTofMoyenne *buffer, bool *found);

void insertionMoyenne(FichierTofMoyenne* fichier, StudentsMoyenneArrayElement record, BufferTofMoyenne* buffer);

void supressionMoyenne(FichierTofMoyenne* fichier, float moyenne, BufferTofMoyenne* buffer);

void searchStudentMoyenneInArray(StudentsMoyenneArray *studentsMoyenneArray, int archiveI, int archiveJ, float moyenne, int *k);

void insertStudentMoyenneInArray(StudentsMoyenneArray *studentsMoyenneArray, int archiveI, int archiveJ,float moyenne);

void insertStudentMoyenneWithoutSearchingInArray(StudentsMoyenneArray *studentsMoyenneArray, float moyenne, int i);





#endif //TP1_SFSD_ARCHIVEMANIPULATION_H
