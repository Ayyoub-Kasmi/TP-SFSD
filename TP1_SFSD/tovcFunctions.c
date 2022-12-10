//
// Created by AOUFAR FARES on 23/10/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include "tovcFunctions.h"
#include <stdbool.h>
#include <time.h>

void setEntete(FichierTof *fichier, int pos, int value) {
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

int getEntete(FichierTof *fichier, int pos) {
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

void setFile(FichierTof *fichier, FILE *f) {
    fichier->file = f;
}

FILE *getFile(FichierTof *fichier) {
    return fichier->file;
}

FichierTof *ouvrirFichierTof(char *name, char mode) {
    FichierTof *fichier = malloc(sizeof(fichier));
    if (mode == 'N') { //Nouveau fichier
        fichier->file = fopen(name, "wb+");
        setEntete(fichier, 1, 0);
        setEntete(fichier, 2, 0);
        setEntete(fichier, 3, 0);
        setEntete(fichier, 4, 0);
        rewind(getFile(fichier));
        fwrite(&fichier->entete, sizeof(EnteteTof), 1, getFile(fichier));
    } else {//ancien fichier
        fichier->file = fopen(name, "rb+");
        if (getFile(fichier) != NULL) {
            fread(&fichier->entete, sizeof(EnteteTof), 1, getFile(fichier));
        } else {
            printf("Erreur, fichier inexistant");
        }
    }
    return fichier;
}

void fermerFichier(FichierTof *fichier) {
    rewind(getFile(fichier));
    fwrite(&fichier->entete, sizeof(EnteteTof), 1, getFile(fichier));
    fclose(getFile(fichier));
    free(fichier);
}

void lireBloc(FichierTof *fichier, int i, BufferTof *buffer) {
    fseek(getFile(fichier), sizeof(EnteteTof) + sizeof(BufferTof) * i, 0);
    fread(buffer, sizeof(BufferTof), 1, getFile(fichier));
}

void ecrireBloc(FichierTof *fichier, int i, BufferTof *buffer) {
    fseek(getFile(fichier), sizeof(EnteteTof) + sizeof(BufferTof) * i, 0);
    fwrite(buffer, sizeof(BufferTof), 1, getFile(fichier));
    //setEnteteTof(fichier, 2, getEnteteTof(fichier,2) + 1); on les fait individuellement dans chaque fonction
}

void ecrireChaine(FichierTof *fichier, BufferTof *buffer, char *chaine, int taille, int *i, int *j) {

    for (int k = 0; k < taille; ++k) {
        if (*j < BUFFER_SIZE) {
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
    setEntete(fichier, 3, getEntete(fichier, 3) + taille); //move this to "Ecrire Enregistrement
}

void lirechaine(FichierTof *fichier, BufferTof *buffer, char *chaine, int taille, int *i, int *j) {
    for (int k = 0; k < taille; ++k) {
        if (*i == getEntete(fichier, 1)) {
            if (*j < getEntete(fichier, 2)) {
                chaine[k] = buffer->tab[*j];
                (*j)++;
            } else return;
        } else {
            if (*j < BUFFER_SIZE) {
                (*i)++;
                lireBloc(fichier, *i, buffer);
                chaine[k] = buffer->tab[0];
                (*j) = 0;
            } else {
                (*i)++;
                lireBloc(fichier, *i, buffer);
                chaine[k] = buffer->tab[0];
                (*j) = 0;
            }
            (*j)++;
        }
    }

}

void lirechaine2(FichierTof *fichier, BufferTof *buffer, char *chaine, int taille, int *i, int *j) {
    for (int k = 0; k < taille; ++k) {
        if (*i == getEntete(fichier, 1)) {
            //if the current bloc is the last block

            if (*j < getEntete(fichier, 2)) {
                //if j is before the free position
                chaine[k] = buffer->tab[*j];
                (*j)++;
            } else return;

        } else {
            if (*j < BUFFER_SIZE) {
                //if the current character is not the last character in the buffer
                chaine[k] = buffer->tab[*j];
            } else {
                //if the limit of the buffer is exceeded, so move to the next block
                (*i)++;
                lireBloc(fichier, *i, buffer);
                chaine[k] = buffer->tab[0];
            }
            (*j)++;
        }
    }
}



//void chargementInitialeTof(FichierTof *fichier, int n, BufferTof* buffer) {
//    int i = 0, j = 0;
//    StudentIndexRecord record;
//    //BufferTof buffer;
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
//            //fwrite(&buffer, sizeof(BufferTof), 1, getFileTof(fichier));
//            ecrireBlocTof(fichier, i, buffer);
//            i++;
//            buffer->tab[0] = record;
//            j = 1;
//        }
//    }
//    buffer->positionLibre = j - 1;
//    //fwrite(&buffer, sizeof(BufferTof), 1, getFileTof(fichier));
//    ecrireBlocTof(fichier, i, buffer);
//    setEnteteTof(fichier, 1, i);
//    setEnteteTof(fichier, 2, n);
//}
//
//void printFileTof(FichierTof* fichier) {
//    BufferTof buffer;
//    buffer.positionLibre = 0;
//
//    for(int i = 0; i <= getEnteteTof(fichier,1); ++i) {
//        lireBlocTof(fichier, i, &buffer);
//        for (int j = 0; j <= buffer.positionLibre; j++) {
//            printf("\nData: %d, Key: %d \n", buffer.tab[j].data, buffer.tab[j].key);
//        }
//    }
//}
//
//bool rechercheTof(FichierTof* fichier, int k, int* i, int* j, BufferTof* buffer){
//    *i = 0;
//    *j = 0;
//    bool trouv = false;
//    while((*i <= getEnteteTof(fichier, 1)) && (!trouv)){
//        lireBlocTof(fichier, *i, buffer);
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
//void insertionTof(FichierTof* fichier, StudentIndexRecord record, BufferTof* buffer){
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
//void supressionTof(FichierTof* fichier, int k, BufferTof* buffer){
//    int i, j;
//    StudentIndexRecord record;
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
