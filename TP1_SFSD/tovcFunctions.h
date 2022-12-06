//
// Created by AOUFAR FARES on 24/11/2022.
//

#ifndef TP1_SFSD_TOVCFUNCTIONS_H
#define TP1_SFSD_TOVCFUNCTIONS_H

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFFER_SIZE 250
#define STUDENT_ID_SIZE 4
#define CLASS_ID_SIZE 3
#define IS_DELETED_SIZE 1
#define CLASS_NUMBER_SIZE 2
#define SCHOOL_LEVEL_SIZE 1
#define GENDER_SIZE 1
#define EFF_SIZE 1
#define LENGTH_SIZE 4  // MAY CHANGE
#define FIRST_LOAD_OF_STUDENTS 120
#define FIRST_LOAD_OF_CLASSES 30
#define WHOLE_PART_SIZE 2
#define DECIMAL_PART_SIZE 2
struct Entete{
    int numberOfBlocs;
    int lastPositionInTheLastBloc;
    int NumberOfCharsInserted;
    int numberOfCharsDeleted;
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
    char tab[BUFFER_SIZE];
    int positionLibre;
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

void ecrireChaine(Fichier* fichier, Buffer* buffer,char* chaine, int taille, int* i, int* j);

void lirechaine(Fichier* fichier, Buffer* buffer, char* chaine, int taille, int* i, int* j);
void lirechaine2(Fichier *fichier, Buffer *buffer, char *chaine, int taille, int *i, int *j);

#endif //TP1_SFSD_TOVCFUNCTIONS_H
