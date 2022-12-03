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
#define FIRST_LOAD_OF_STUDENTS 750
#define FIRST_LOAD_OF_ROOMS 30
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
    int tab[FIRST_LOAD_OF_STUDENTS];
    int nb; //number of elements within the block
} StudentsIdArray;

typedef struct {
    int tab[FIRST_LOAD_OF_ROOMS];
    int nb; //number of elements within the block
} RoomIdArray;

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

int generate4positionInt(int seed);

void generateStudentId(StudentsIdArray *studentsIdArray);

void searchStudentId(StudentsIdArray *studentsIdArray, int id, int *i, bool *found);

void insertStudentId(StudentsIdArray *studentsIdArray, int id);

void insertStudentIdWithoutSearching(StudentsIdArray *studentsIdArray, int id, int i);

int generate2positionInt(int seed);

int generateTheLevel(int seed);

void generateClassId(RoomIdArray *roomIdArray);

void searchRoomNumber(RoomIdArray *roomIdArray, int roomNumber, bool *found);

void searchClassId(RoomIdArray *roomIdArray, int id, int *i, bool *found);

void insertRoomId(RoomIdArray *roomIdArray, int id);

void insertRoomIdWithoutSearching(RoomIdArray *roomIdArray, int id, int i);

#endif //TP1_SFSD_TOVCFUNCTIONS_H
