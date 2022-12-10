//
// Created by AOUFAR FARES on 23/10/2022.
//

#ifndef SFSD_TOF_TO_FFUNCTIONS_H
#define SFSD_TOF_TO_FFUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>

#define MAX 15

typedef struct {
    int LastBloc;
    int NumbrOfRecords;
}Entete;

typedef struct Fichier{
    FILE* file;
    Entete entete;
}Fichier;

typedef struct Record{
    int key;
    int data;
}Record;

typedef struct Buffer{
    Record tab[MAX];
    int maxIndex;
}Buffer;

void setEntete(Fichier *fichier, int pos, int value);

int getEntete(Fichier *fichier, int pos);

void setFile(Fichier *fichier, FILE *f);

FILE *getFile(Fichier *fichier);

Fichier * ouvrirFichier( char *name, char mode);

void fermerFichier(Fichier *fichier);

void lireBloc(Fichier* fichier, int i, Buffer* buffer);

void ecrireBloc(Fichier* fichier, int i, Buffer* buffer);

void printFile(Fichier* fichier);

void chargementInitiale(Fichier *fichier, int n, Buffer* buffer);

bool recherche(Fichier* fichier, int k, int* i, int* j, Buffer* buffer);

void insertion(Fichier* fichier, Record record, Buffer* buffer);

void supression(Fichier* fichier, int k, Buffer* buffer);

#endif //SFSD_TOF_TO_FFUNCTIONS_H
