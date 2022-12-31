//
// Created by AOUFAR FARES on 23/10/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "tovcFunctions.h"
#include <stdbool.h>
#include <time.h>

void setEntete(FichierTovc *fichier, int pos, int value) {
    if (pos == 1) {
        fichier->entete.numberOfBlocs = value;
    } else if (pos == 2) {
        fichier->entete.lastPositionInTheLastBloc = value;
    } else if (pos == 3) {
        fichier->entete.NumberOfCharsInserted = value;
    } else if (pos == 4) {
        fichier->entete.numberOfCharsDeleted;
    }
}

int getEntete(FichierTovc *fichier, int pos) {
    if (pos == 1) {
        return fichier->entete.numberOfBlocs;
    } else if (pos == 2) {
        return fichier->entete.lastPositionInTheLastBloc;
    } else if (pos == 3) {
        return fichier->entete.NumberOfCharsInserted;
    } else if (pos == 4) {
        return fichier->entete.numberOfCharsDeleted;
    } else return -1; // <====== NULL is incompatible with int type
}

void setFile(FichierTovc *fichier, FILE *f) {
    fichier->file = f;
}

FILE *getFile(FichierTovc *fichier) {
    return fichier->file;
}

FichierTovc *ouvrirFichierTovc(char *name, char mode) {
    FichierTovc *fichier = malloc(sizeof(FichierTovc));
    if (mode == 'N') { //Nouveau fichier
        fichier->file = fopen(name, "wb+");
        setEntete(fichier, 1, 0);
        setEntete(fichier, 2, 0);
        setEntete(fichier, 3, 0);
        setEntete(fichier, 4, 0);
        rewind(getFile(fichier));
        fwrite(&fichier->entete, sizeof(EnteteTovc), 1, getFile(fichier));
    } else {//ancien fichier
        fichier->file = fopen(name, "rb+");
        if (getFile(fichier) != NULL) {
            fread(&fichier->entete, sizeof(EnteteTovc), 1, getFile(fichier));
        } else {
            printf("Erreur, fichier inexistant");
        }
    }
    return fichier;
}

void fermerFichier(FichierTovc *fichier) {
    rewind(getFile(fichier));
    fwrite(&fichier->entete, sizeof(EnteteTovc), 1, getFile(fichier));
    fclose(getFile(fichier));
    free(fichier);
}

void lireBloc(FichierTovc *fichier, int i, BufferTovc *bufferTovc) {
    fseek(getFile(fichier), sizeof(EnteteTovc) + sizeof(BufferTovc) * i, 0);
    fread(bufferTovc, sizeof(BufferTovc), 1, getFile(fichier));
}

void ecrireBloc(FichierTovc *fichier, int i, BufferTovc *bufferTovc) {
    fseek(getFile(fichier), sizeof(EnteteTovc) + sizeof(BufferTovc) * i, 0);
    fwrite(bufferTovc, sizeof(BufferTovc), 1, getFile(fichier));
    //setEnteteTof(fichier, 2, getEnteteTof(fichier,2) + 1); on les fait individuellement dans chaque fonction
}

void ecrireChaine(FichierTovc *fichier, BufferTovc *bufferTovc, char *chaine, int taille, int *i, int *j) {

    for (int k = 0; k < taille; ++k) {
        if (*j < TOVC_BUFFER_SIZE) {
            bufferTovc->tab[*j] = chaine[k];
            (*j)++;
        } else {
            ecrireBloc(fichier, *i, bufferTovc);
            (*i)++;
            bufferTovc->tab[0] = chaine[k];
            (*j) = 1;
        }
    }

    setEntete(fichier, 2, *j); //to check
    setEntete(fichier, 3, getEntete(fichier, 3) + taille); //move this to "Ecrire Enregistrement
}

void lirechaine(FichierTovc *fichier, BufferTovc *bufferTovc, char *chaine, int taille, int *i, int *j) {
    for (int k = 0; k < taille; ++k) {
        if (*i == getEntete(fichier, 1) -1) {
            //if the current bloc is the last block

            if (*j < getEntete(fichier, 2)) {
                //if j is before the free position
                chaine[k] = bufferTovc->tab[*j];
                (*j)++;
            } else return;

        } else {
            if (*j == TOVC_BUFFER_SIZE) {
                (*i)++;
                lireBloc(fichier, *i, bufferTovc);
                *j = 0;
            }
            chaine[k] = bufferTovc->tab[*j];
            (*j)++;
        }
    }

    if(*j == TOVC_BUFFER_SIZE){
        (*i)++;
        lireBloc(fichier, *i, bufferTovc);
        *j = 0;
    }
}



//void chargementInitialeTof(FichierTovc *fichier, int n, BufferTovc* buffer) {
//    int i = 0, j = 0;
//    IndexRecord record;
//    //BufferTovc buffer;
//    for (int k = 0; k < n; ++k) {
//        printf("La cle: ");
//        scanf("%d", &record.id);
//        printf("L\'information: ");
//        scanf("%d", &record.i);
//        printf("\n");
//        if (j < MAX_LOF) {
//            buffer->tab[j] = record;
//            j++;
//        } else {
//            buffer->positionLibre = j - 1;
//            //fwrite(&buffer, sizeof(BufferTovc), 1, getFileTof(fichier));
//            ecrireBlocTof(fichier, i, buffer);
//            i++;
//            buffer->tab[0] = record;
//            j = 1;
//        }
//    }
//    buffer->positionLibre = j - 1;
//    //fwrite(&buffer, sizeof(BufferTovc), 1, getFileTof(fichier));
//    ecrireBlocTof(fichier, i, buffer);
//    setEnteteTof(fichier, 1, i);
//    setEnteteTof(fichier, 2, n);
//}
//
//void printFileTof(FichierTovc* fichier) {
//    BufferTovc buffer;
//    buffer.positionLibre = 0;
//
//    for(int i = 0; i <= getEnteteTof(fichier,1); ++i) {
//        lireBlocTof(fichier, i, &buffer);
//        for (int j = 0; j <= buffer.positionLibre; j++) {
//            printf("\nData: %d, Key: %d \n", buffer.tab[j].i, buffer.tab[j].id);
//        }
//    }
//}
//
//bool rechercheTof(FichierTovc* fichier, int k, int* i, int* j, BufferTovc* buffer){
//    *i = 0;
//    *j = 0;
//    bool trouv = false;
//    while((*i <= getEnteteTof(fichier, 1)) && (!trouv)){
//        lireBlocTof(fichier, *i, buffer);
//        while(*j <= buffer->positionLibre){
//            if(buffer->tab[*j].id == k){
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
//void insertionTof(FichierTovc* fichier, IndexRecord record, BufferTovc* buffer){
//
//    lireBlocTof(fichier, getEnteteTof(fichier,1), buffer);
//    if(buffer->positionLibre < MAX_LOF - 1){
//        buffer->tab[buffer->positionLibre] = record;
//        buffer->positionLibre++;
//    } else {
//        buffer->tab[0] = record;
//        buffer->positionLibre = 0;
//        setEnteteTof(fichier, 1, getEnteteTof(fichier, 1));
//    }
//    ecrireBlocTof(fichier , getEnteteTof(fichier, 1), buffer);
//    setEnteteTof(fichier, 2, getEnteteTof(fichier, 2) + 1);
//
//}
//
//void supressionTof(FichierTovc* fichier, int k, BufferTovc* buffer){
//    int i, j;
//    IndexRecord record;
//
//    if(rechercheTof(fichier, k, &i, &j, buffer)){
//        lireBlocTof(fichier, i ,buffer);
//        record = buffer->tab[buffer->positionLibre];
//        buffer->positionLibre --;
//        if(buffer->positionLibre < 0) setEnteteTof(fichier, 1, getEnteteTof(fichier, 1) - 1);
//        ecrireBlocTof(fichier, i, buffer);
//        lireBlocTof(fichier, i ,buffer);
//        buffer->tab[j] = record;
//        ecrireBlocTof(fichier, i, buffer);
//        setEnteteTof(fichier, 2, getEnteteTof(fichier, 2) - 1);
//    }
//
//}
