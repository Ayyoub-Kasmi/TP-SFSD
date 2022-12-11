//
// Created by AOUFAR FARES on 10/12/2022.
//

#ifndef TP1_SFSD_TOFINDEXFUNCTIONS_H
#define TP1_SFSD_TOFINDEXFUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>

#define MAX 15

typedef struct {
    int LastBloc;
    int NumberOfRecordsInserted;
    int NumberOfRecordsDeleted;
}EnteteTof;

typedef struct {
    FILE* file;
    EnteteTof entete;
}FichierTof;

typedef struct {
    int key;
    int data;
    bool isDeleted;
}StudentIndexRecord;

typedef struct {
    StudentIndexRecord tab[MAX];
    int nb; //number of records per buffer or bloc
}BufferTof;

void setEnteteTof(FichierTof *fichier, int pos, int value);

int getEnteteTof(FichierTof *fichier, int pos);

void setFileTof(FichierTof *fichier, FILE *f);

FILE *getFileTof(FichierTof *fichier);

FichierTof *ouvrirFichierTof(char *name, char mode);

void fermerFichierTof(FichierTof *fichier);

void lireBlocTof(FichierTof* fichier, int i, BufferTof* buffer);

void ecrireBlocTof(FichierTof* fichier, int i, BufferTof* buffer);

void printFileTof(FichierTof* fichier);

void chargementInitialeTof(FichierTof *fichier, int n, BufferTof* buffer);

void rechercheTof(FichierTof *fichier, int key, int *i, int *j, BufferTof *buffer, bool *found, bool *isDeleted);

void insertionTof(FichierTof* fichier, StudentIndexRecord record, BufferTof* buffer);

void supressionTof(FichierTof* fichier, int k, BufferTof* buffer);

#endif //TP1_SFSD_TOFINDEXFUNCTIONS_H
