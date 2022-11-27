//
// Created by AOUFAR FARES on 24/11/2022.
//

#ifndef TP1_SFSD_TOVCFUNCTIONS_H
#define TP1_SFSD_TOVCFUNCTIONS_H

#include <stdbool.h>

#define MAX 15
#define MAX_CHAINE 15

struct Entete{
    int LastBloc;
    int NumbrOfRecords;
};
typedef struct Entete Entete;

struct Fichier{
    FILE* file;
    Entete entete;
};
typedef struct Fichier Fichier;

struct Record{
    int key;
    int data;
};
typedef struct Record Record;

struct Buffer{
    Record tab[MAX];
    int maxIndex;
};
typedef struct Buffer Buffer;

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


#endif //TP1_SFSD_TOVCFUNCTIONS_H
