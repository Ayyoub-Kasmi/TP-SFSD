//
// Created by AOUFAR FARES on 10/12/2022.
//

#ifndef TP1_SFSD_TOFINDEXFUNCTIONS_H
#define TP1_SFSD_TOFINDEXFUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>

#define TOF_BUFFER_SIZE 55

typedef struct {
    int NumberOfBlocks;
    int NumberOfRecordsInserted;
    int NumberOfRecordsDeleted;
}EnteteTof;

typedef struct {
    FILE* file;
    EnteteTof entete;
}FichierTof;

typedef struct {
    int id;
    int i;
    int j;
    bool isDeleted;
}IndexRecord;

typedef struct {
    IndexRecord tab[TOF_BUFFER_SIZE];
    int nb; //number of records per buffer or bloc
}BufferTof;

extern BufferTof bufferTofClass;

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

void insertionTof(FichierTof* classIndexFile, IndexRecord recordToBeInserted, BufferTof* buffer);

void supressionTof(FichierTof* fichier, int k, BufferTof* buffer);

void printClassIndex(FichierTof* classIndexFile);

void insertionTofWithoutSearch(FichierTof *classIndexFile, IndexRecord recordToBeInserted, int indexI, int indexJ, BufferTof *buffer);

#endif //TP1_SFSD_TOFINDEXFUNCTIONS_H
