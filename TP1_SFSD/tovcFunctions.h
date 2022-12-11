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

typedef struct{
    int numberOfBlocs;
    int lastPositionInTheLastBloc;
    int NumberOfCharsInserted;
    int numberOfCharsDeleted;
}EnteteTovc;

typedef struct {
    FILE* file;
    EnteteTovc entete;
}FichierTovc;

typedef struct {
    int key;
    int data;
}StudentIndexRecord;

typedef struct {
    char tab[BUFFER_SIZE];
}BufferTovc;

void setEntete(FichierTovc *fichier, int pos, int value);

int getEntete(FichierTovc *fichier, int pos);

void setFile(FichierTovc *fichier, FILE *f);

FILE *getFile(FichierTovc *fichier);

FichierTovc * ouvrirFichierTovc(char *name, char mode);

void fermerFichier(FichierTovc *fichier);

void lireBloc(FichierTovc* fichier, int i, BufferTovc* buffer);

void ecrireBloc(FichierTovc* fichier, int i, BufferTovc* buffer);

void printFile(FichierTovc* fichier);

void chargementInitiale(FichierTovc *fichier, int n, BufferTovc* buffer);

bool recherche(FichierTovc* fichier, int k, int* i, int* j, BufferTovc* buffer);

void ecrireChaine(FichierTovc* fichier, BufferTovc* buffer,char* chaine, int taille, int* i, int* j);

void lirechaine(FichierTovc *fichier, BufferTovc *buffer, char *chaine, int taille, int *i, int *j);

void printFile(FichierTovc* fichier);

void insertion(FichierTovc* fichier, StudentIndexRecord record, BufferTovc* buffer);

void supression(FichierTovc* fichier, int k, BufferTovc* buffer);

#endif //TP1_SFSD_TOVCFUNCTIONS_H
