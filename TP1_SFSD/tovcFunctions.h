//
// Created by AOUFAR FARES on 24/11/2022.
//

#ifndef TP1_SFSD_TOVCFUNCTIONS_H
#define TP1_SFSD_TOVCFUNCTIONS_H

#include <stdbool.h>

#define MAX 250
#define T_NUM_IDENTIFICATION 4
#define T_ANNEE_SCOLARISATION 1
#define T_GENRE 1
#define T_EFF 1
#define T_LONGEUR 4  // MAY CHANGE
#define FIRST_LOAD 750
struct Entete{
    int numberOfBlocs;
    int NumbrOfCharsInsered;
    int numberOfCharsSupressed
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
    char tab[MAX];
    int positionLibre;
};
typedef struct Buffer Buffer;

typedef struct {
//    TDATA tab[MAX_LOF];
    int tab[FIRST_LOAD];
    int nb; //number of elements within the block
} StudentsIdTable;

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

void ecrireChaine(Fichier* fichier, Buffer* buffer,char* chaine, int taille, int* i, int* j);

void lirechaine(Fichier* fichier, Buffer* buffer, char* chaine, int taille, int* i, int* j);


#endif //TP1_SFSD_TOVCFUNCTIONS_H
