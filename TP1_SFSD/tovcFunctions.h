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
typedef struct EnteteTof EnteteTof;

struct Fichier{
    FILE* file;
    EnteteTof entete;
};
typedef struct FichierTof FichierTof;

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



void setEntete(FichierTof *fichier, int pos, int value);

int getEntete(FichierTof *fichier, int pos);

void setFile(FichierTof *fichier, FILE *f);

FILE *getFile(FichierTof *fichier);

FichierTof * ouvrirFichier(char *name, char mode);

void fermerFichier(FichierTof *fichier);

void lireBloc(FichierTof* fichier, int i, Buffer* buffer);

void ecrireBloc(FichierTof* fichier, int i, Buffer* buffer);

void printFile(FichierTof* fichier);

void chargementInitiale(FichierTof *fichier, int n, Buffer* buffer);

bool recherche(FichierTof* fichier, int k, int* i, int* j, Buffer* buffer);

void insertion(FichierTof* fichier, Record record, Buffer* buffer);

void supression(FichierTof* fichier, int k, Buffer* buffer);

void ecrireChaine(FichierTof* fichier, Buffer* buffer, char* chaine, int taille, int* i, int* j);

void lirechaine(FichierTof* fichier, Buffer* buffer, char* chaine, int taille, int* i, int* j);
void lirechaine2(FichierTof *fichier, Buffer *buffer, char *chaine, int taille, int *i, int *j);

#endif //TP1_SFSD_TOVCFUNCTIONS_H
