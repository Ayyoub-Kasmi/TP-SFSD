//
// Created by AOUFAR FARES on 23/10/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "tovcFunctions.h"
#include <stdbool.h>
#include <time.h>

void setEntete(Fichier *fichier, int pos, int value) {
    if (pos == 1) {
        fichier->entete.numberOfBlocs = value;
    } else if (pos == 2) {
        fichier->entete.NumbrOfCharsInsered = value;
    } else if (pos == 3) {
        fichier->entete.numberOfCharsSupressed = value;
    }
}

int getEntete(Fichier *fichier, int pos) {
    if (pos == 1) {
        return fichier->entete.numberOfBlocs;
    } else if (pos == 2) {
        return fichier->entete.NumbrOfCharsInsered;
    } else if (pos == 3) {
        return fichier->entete.numberOfCharsSupressed;
    } else return NULL;
}

void setFile(Fichier *fichier, FILE *f) {
    fichier->file = f;
}

FILE *getFile(Fichier *fichier) {
    return fichier->file;
}

Fichier *ouvrirFichier(char *name, char mode) {
    Fichier *fichier = malloc(sizeof(fichier));
    if (mode == 'N') { //Nouveau fichier
        fichier->file = fopen(name, "wb+");
        setEntete(fichier, 1, 0);
        setEntete(fichier, 2, 0);
        setEntete(fichier, 3, 0);
        rewind(getFile(fichier));
        fwrite(&fichier->entete, sizeof(Entete), 1, getFile(fichier));
    } else {//ancien fichier
        fichier->file = fopen(name, "rb+");
        if (getFile(fichier) != NULL) {
            fread(&fichier->entete, sizeof(Entete), 1, getFile(fichier));
        } else {
            printf("Erreur, fichier inexistant");
        }
    }
    return fichier;
}

void fermerFichier(Fichier *fichier) {
    rewind(getFile(fichier));
    fwrite(&fichier->entete, sizeof(Entete), 1, getFile(fichier));
    fclose(getFile(fichier));
    free(fichier);
}

void lireBloc(Fichier *fichier, int i, Buffer *buffer) {
    fseek(getFile(fichier), sizeof(Entete) + sizeof(Buffer) * i, 0);
    fread(buffer, sizeof(Buffer), 1, getFile(fichier));
}

void ecrireBloc(Fichier *fichier, int i, Buffer *buffer) {
    fseek(getFile(fichier), sizeof(Entete) + sizeof(Buffer) * i, 0);
    fwrite(buffer, sizeof(Buffer), 1, getFile(fichier));
    //setEntete(fichier, 2, getEntete(fichier,2) + 1); on les fait individuellement dans chaque fonction
}

//void chargementInitiale(Fichier *fichier, int n, Buffer* buffer) {
//    int i = 0, j = 0;
//    Record record;
//    //Buffer buffer;
//    for (int k = 0; k < n; ++k) {
//        printf("La cle: ");
//        scanf("%d", &record.key);
//        printf("L\'information: ");
//        scanf("%d", &record.data);
//        printf("\n");
//        if (j < MAX_LOF) {
//            buffer->tab[j] = record;
//            j++;
//        } else {
//            buffer->positionLibre = j - 1;
//            //fwrite(&buffer, sizeof(Buffer), 1, getFile(fichier));
//            ecrireBloc(fichier, i, buffer);
//            i++;
//            buffer->tab[0] = record;
//            j = 1;
//        }
//    }
//    buffer->positionLibre = j - 1;
//    //fwrite(&buffer, sizeof(Buffer), 1, getFile(fichier));
//    ecrireBloc(fichier, i, buffer);
//    setEntete(fichier, 1, i);
//    setEntete(fichier, 2, n);
//}
//
//void printFile(Fichier* fichier) {
//    Buffer buffer;
//    buffer.positionLibre = 0;
//
//    for(int i = 0; i <= getEntete(fichier,1); ++i) {
//        lireBloc(fichier, i, &buffer);
//        for (int j = 0; j <= buffer.positionLibre; j++) {
//            printf("\nData: %d, Key: %d \n", buffer.tab[j].data, buffer.tab[j].key);
//        }
//    }
//}
//
//bool recherche(Fichier* fichier, int k, int* i, int* j, Buffer* buffer){
//    *i = 0;
//    *j = 0;
//    bool trouv = false;
//    while((*i <= getEntete(fichier, 1)) && (!trouv)){
//        lireBloc(fichier, *i, buffer);
//        while(*j <= buffer->positionLibre){
//            if(buffer->tab[*j].key == k){
//                trouv = true;
//                break;
//            }else (*j)++;
//        }
//        if(!trouv) (*i)++;
//    }
//    if(trouv){
//        return true;
//    }else{
//        return false;
//    }
//}
//
//void insertion(Fichier* fichier, Record record, Buffer* buffer){
//
//    lireBloc(fichier, getEntete(fichier,1), buffer);
//    if(buffer->positionLibre < MAX_LOF - 1){
//        buffer->tab[buffer->positionLibre] = record;
//        buffer->positionLibre++;
//    } else {
//        buffer->tab[0] = record;
//        buffer->positionLibre = 0;
//        setEntete(fichier, 1, getEntete(fichier, 1));
//    }
//    ecrireBloc(fichier , getEntete(fichier, 1), buffer);
//    setEntete(fichier, 2, getEntete(fichier, 2) + 1);
//
//}
//
//void supression(Fichier* fichier, int k, Buffer* buffer){
//    int i, j;
//    Record record;
//
//    if(recherche(fichier, k, &i, &j, buffer)){
//        lireBloc(fichier, i ,buffer);
//        record = buffer->tab[buffer->positionLibre];
//        buffer->positionLibre --;
//        if(buffer->positionLibre < 0) setEntete(fichier, 1, getEntete(fichier, 1) - 1);
//        ecrireBloc(fichier, i, buffer);
//        lireBloc(fichier, i ,buffer);
//        buffer->tab[j] = record;
//        ecrireBloc(fichier, i, buffer);
//        setEntete(fichier, 2, getEntete(fichier, 2) - 1);
//    }
//
//}

void ecrireChaine(Fichier *fichier, Buffer *buffer, char *chaine, int taille, int *i, int *j) {
    int k = 0;

    for (int k = 0; k < taille; ++k) {
        if (*j < MAX) {
            buffer->tab[*j] = chaine[k];
            (*j)++;
        } else {
            buffer->positionLibre = (*j);
            ecrireBloc(fichier, *i, buffer);
            (*i)++;
            buffer->tab[0] = chaine[k];
            (*j) = 1;
        }
    }
    setEntete(fichier, 2, getEntete(fichier, 2) + taille);
}

void lirechaine(Fichier *fichier, Buffer *buffer, char *chaine, int taille, int *i, int *j) {
    for (int k = 0; k < taille; ++k) {
        if (*j < buffer->positionLibre) {
            chaine[k] = buffer->tab[*j];
        } else {
            (*i)++;
            lireBloc(fichier, *i, buffer);
            chaine[k] = buffer->tab[0];
            (*j) = 0;
        }
        (*j)++;
    }

}

int generateStudentID(int seed) {
    int randomID;
    srand((unsigned) time(0) + seed);
    for (int counter = 0; counter < 2; ++counter) {
        //this loop is to ensure the randomness of the generated value
        randomID = rand() % 10000;
    }
    return randomID;
}

int GenerateStudentsId(StudentsIdTable *studentsIdTable) {
    return 0;
}

void searchStudentId(StudentsIdTable *studentsIdTable, int id, int *i, bool *found) {
    //normal binary search in the studentsIdTable
    *found = false;
    if (studentsIdTable->nb > 0) {
        int inf = 0;
        int sup = studentsIdTable->nb - 1;
        while ((inf <= sup) && (!(*found))) {
            i = (inf + sup) / 2;
            if (id > studentsIdTable->tab[*i]) {
                inf = *i + 1;
            } else if (id < studentsIdTable->tab[*i]) {
                sup = *i - 1;
            } else {
                (*found) = true;
            }
        }
        if (!(*found)) {
            *i = inf;
        }
    } else {
        *i = 0;
    }
}

void insertStudentId(StudentsIdTable *studentsIdTable, int id) {
    //insertion with delays to keep the order in the studentsIdTable
    if (studentsIdTable->nb <= 0) {
        studentsIdTable->tab[0] = id;
        studentsIdTable->nb++;
    } else {
        int i = 0;
        bool found = false;
        searchStudentId(studentsIdTable, id, &i, &found);
        if (!found) {
            for (int k = studentsIdTable->nb; k >= i; --k) {
                studentsIdTable->tab[k] = studentsIdTable->tab[k - 1];
            }
            studentsIdTable->tab[i] = id;
            studentsIdTable->nb++;
        }
    }

}
