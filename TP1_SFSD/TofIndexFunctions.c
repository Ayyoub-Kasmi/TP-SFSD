//
// Created by AOUFAR FARES on 10/12/2022.
//

#include "TofIndexFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

void setEnteteTof(FichierTof *fichier, int pos, int value) {
    if (pos == 1) {
        fichier->entete.NumberOfBlocks = value;
    } else if (pos == 2) {
        fichier->entete.NumberOfRecordsInserted = value;
    } else if (pos == 3) {
        fichier->entete.NumberOfRecordsDeleted = value;
    }
}

int getEnteteTof(FichierTof *fichier, int pos) {
    if (pos == 1) {
        return fichier->entete.NumberOfBlocks;
    } else if (pos == 2) {
        return fichier->entete.NumberOfRecordsInserted;
    } else if (pos == 3) {
        return fichier->entete.NumberOfRecordsDeleted;
    } else return -1;
}

void setFileTof(FichierTof *fichier, FILE *f) {
    fichier->file = f;
}

FILE *getFileTof(FichierTof *fichier) {
    return fichier->file;
}

FichierTof *ouvrirFichierTof(char *name, char mode) {
    FichierTof *fichier = malloc(sizeof(FichierTof));
    if (mode == 'N') { //Nouveau fichier
        fichier->file = fopen(name, "wb+");
        setEnteteTof(fichier, 1, 0);
        setEnteteTof(fichier, 2, 0);
        rewind(getFileTof(fichier));
        fwrite(&fichier->entete, sizeof(EnteteTof), 1, getFileTof(fichier));
    } else {//ancien fichier
        fichier->file = fopen(name, "rb+");
        if (getFileTof(fichier) != NULL) {
            fread(&fichier->entete, sizeof(EnteteTof), 1, getFileTof(fichier));
        } else {
            printf("Erreur, fichier inexsistant");
        }
    }
    return fichier;
}

void fermerFichierTof(FichierTof *fichier) {
    rewind(getFileTof(fichier));
    fwrite(&fichier->entete, sizeof(EnteteTof), 1, getFileTof(fichier));
    fclose(getFileTof(fichier));
    free(fichier);
}

void lireBlocTof(FichierTof *fichier, int i, BufferTof *buffer) {
    fseek(getFileTof(fichier), sizeof(EnteteTof) + sizeof(BufferTof) * i, 0);
    fread(buffer, sizeof(BufferTof), 1, getFileTof(fichier));
}

void ecrireBlocTof(FichierTof *fichier, int i, BufferTof *buffer) {
    fseek(getFileTof(fichier), sizeof(EnteteTof) + sizeof(BufferTof) * i, 0);
    fwrite(buffer, sizeof(BufferTof), 1, getFileTof(fichier));
    //setEnteteTof(fichier, 2, getEnteteTof(fichier,2) + 1); on les fait individuellement dans chaque fonction
}

//void chargementInitialeTof(FichierTof *fichier, int n, BufferTof *buffer) {
//    int i = 0, j = 0;
//    IndexRecord record;
//    //BufferTof buffer;
//    for (int k = 0; k < n; ++k) {
//        printf("La cle: ");
//        scanf("%d", &record.id);
//        printf("L\'information: ");
//        scanf("%d", &record.i);
//        printf("\n");
//        if (j < TOF_BUFFER_SIZE) {
//            buffer->tab[j] = record;
//            j++;
//        } else {
//            buffer->nb = j - 1;
//            //fwrite(&buffer, sizeof(BufferTof), 1, getFileTof(fichier));
//            ecrireBlocTof(fichier, i, buffer);
//            i++;
//            buffer->tab[0] = record;
//            j = 1;
//        }
//    }
//    buffer->nb = j - 1;
//    //fwrite(&buffer, sizeof(BufferTof), 1, getFileTof(fichier));
//    ecrireBlocTof(fichier, i, buffer);
//    setEnteteTof(fichier, 1, i);
//    setEnteteTof(fichier, 2, n);
//}

void printFileTof(FichierTof *fichier) {
    BufferTof buffer;
    buffer.nb = 0;

    for (int i = 0; i <= getEnteteTof(fichier, 1); ++i) {
        lireBlocTof(fichier, i, &buffer);
        for (int j = 0; j <= buffer.nb; j++) {
            printf("\nData: %d, Key: %d \n", buffer.tab[j].i, buffer.tab[j].id);
        }
    }
}

void rechercheTof(FichierTof *fichier, int key, int *i, int *j, BufferTof *buffer, bool *found, bool *isDeleted) {
    //don't forget to check if it's not erased !!!
    *i = 0;
    *j = 0;
    int bi = 0;
    int bs = getEnteteTof(fichier, 1);
    int sup = 0;
    int inf = 0;
    bool stop = false;
    *found = false;
    *isDeleted = false;
    while ((bi <= bs) && (!*(found)) && (!stop)) {
        *i = (bi + bs) / 2;
        lireBlocTof(fichier, *i, buffer);
        if ((key >= buffer->tab[0].id) && (key <= buffer->tab[buffer->nb-1].id)) {
            inf = 0;
            sup = buffer->nb - 1;
            while ((inf <= sup) && (!*(found))) {
                *j = (inf + sup) / 2;
                if (key < buffer->tab[*j].id) sup = (*j) - 1;
                else if (key > buffer->tab[*j].id) inf = (*j) + 1;
                else {
                    *found = true;
                    if (buffer->tab[*j].isDeleted) *isDeleted = true;
                }
            }
            if (inf > sup) {
                *j = inf;
                stop = true;
            }
        } else if ((key < buffer->tab[0].id)) bs = (*i) - 1;
        else if (key > buffer->tab[buffer->nb].id) bi = (*i) + 1;
    }
    if (bi > bs){
        if(bi >= getEnteteTof(fichier, 1)){
            *i = INT_MAX; //a value to mean that we exceeded the file size
        }else{
            *i = bi;
            *j = 0;
        }
    }

}

void insertionTof(FichierTof *classIndexFile, IndexRecord recordToBeInserted, BufferTof *buffer) {
    int indexI, indexJ, borneSup;
    IndexRecord container;
    bool isDeleted = false, isFound = false;
    rechercheTof(classIndexFile, recordToBeInserted.id, &indexI, &indexJ,&bufferTofClass, &isFound,&isDeleted);

    while (indexI < getEnteteTof(classIndexFile, 1)) {
        lireBlocTof(classIndexFile, indexI, &bufferTofClass);
        container = bufferTofClass.tab[bufferTofClass.nb - 1];
        borneSup = bufferTofClass.nb - 1;

        while (borneSup > indexJ) {
            bufferTofClass.tab[borneSup] = bufferTofClass.tab[borneSup - 1];
            borneSup--;
        }
        bufferTofClass.tab[indexJ] = recordToBeInserted;
        if (bufferTofClass.nb < TOF_BUFFER_SIZE) {
            bufferTofClass.tab[bufferTofClass.nb] = container;
            bufferTofClass.nb++;
            ecrireBlocTof(classIndexFile, indexI, &bufferTofClass);

            break; //So that we don't use another boolean variable
        } // NO need to use an else because if we enter this bloc the loop will stop
        ecrireBlocTof(classIndexFile, indexI, &bufferTofClass);
        //Updating the nonDenseIndexArray

        indexI++;
        indexJ = 0;
        recordToBeInserted = container;
    }
    if (indexI >= getEnteteTof(classIndexFile, 1)) {
        bufferTofClass.tab[0] = recordToBeInserted;
        bufferTofClass.nb = 1;

        ecrireBlocTof(classIndexFile, indexI, &bufferTofClass);
        setEnteteTof(classIndexFile, 1, indexI + 1);
    }

    setEnteteTof(classIndexFile, 2, getEnteteTof(classIndexFile, 2) + 1);

}

void insertionTofWithoutSearch(FichierTof *classIndexFile, IndexRecord recordToBeInserted, int indexI, int indexJ, BufferTof *buffer) {
    int borneSup;
    IndexRecord container;
    bool isDeleted = false, isFound = false;

    while (indexI < getEnteteTof(classIndexFile, 1)) {
        lireBlocTof(classIndexFile, indexI, &bufferTofClass);
        container = bufferTofClass.tab[bufferTofClass.nb - 1];
        borneSup = bufferTofClass.nb - 1;

        while (borneSup > indexJ) {
            bufferTofClass.tab[borneSup] = bufferTofClass.tab[borneSup - 1];
            borneSup--;
        }
        bufferTofClass.tab[indexJ] = recordToBeInserted;
        if (bufferTofClass.nb < TOF_BUFFER_SIZE) {
            bufferTofClass.tab[bufferTofClass.nb] = container;
            bufferTofClass.nb++;
            ecrireBlocTof(classIndexFile, indexI, &bufferTofClass);

            break; //So that we don't use another boolean variable
        } // NO need to use an else because if we enter this bloc the loop will stop
        ecrireBlocTof(classIndexFile, indexI, &bufferTofClass);

        indexI++;
        indexJ = 0;
        recordToBeInserted = container;
    }
    if (indexI >= getEnteteTof(classIndexFile, 1)) {
        bufferTofClass.tab[0] = recordToBeInserted;
        bufferTofClass.nb = 1;

        ecrireBlocTof(classIndexFile, indexI, &bufferTofClass);
        setEnteteTof(classIndexFile, 1, indexI + 1);
    }

    setEnteteTof(classIndexFile, 2, getEnteteTof(classIndexFile, 2) + 1);

}

void supressionTof(FichierTof *fichier, int k, BufferTof *buffer) {
    int i, j;
    IndexRecord record;
    bool found = false;
    rechercheTof(fichier, k, &i, &j, buffer, &found, NULL);
    if (found) {
        lireBlocTof(fichier, i, buffer);
        record = buffer->tab[buffer->nb];
        buffer->nb--;
        if (buffer->nb < 0) setEnteteTof(fichier, 1, getEnteteTof(fichier, 1) - 1);
        ecrireBlocTof(fichier, i, buffer);
        lireBlocTof(fichier, i, buffer);
        buffer->tab[j] = record;
        ecrireBlocTof(fichier, i, buffer);
        setEnteteTof(fichier, 2, getEnteteTof(fichier, 2) - 1);
    }

}

void printClassIndex(FichierTof* classIndexFile){
    int i= 0;
    int j;
    while (i < getEnteteTof(classIndexFile, 1)){
        lireBlocTof(classIndexFile, 1, &bufferTofClass);
        j = 0;
        while (j < bufferTofClass.nb){
            printf("\nclass id: %d\t i: %d\t j: %d\n", bufferTofClass.tab[j].id, bufferTofClass.tab[j].i, bufferTofClass.tab[j].j);
            j++;
        }
        i++;
    }
}