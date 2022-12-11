//
// Created by AOUFAR FARES on 10/12/2022.
//

#include "TofIndexFunctions.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void setEnteteTof(FichierTof *fichier, int pos, int value) {
    if (pos == 1) {
        fichier->entete.LastBloc = value;
    } else if (pos == 2) {
        fichier->entete.NumberOfRecordsInserted = value;
    } else if (pos == 3) {
        fichier->entete.NumberOfRecordsDeleted = value;
    }
}

int getEnteteTof(FichierTof *fichier, int pos) {
    if (pos == 1) {
        return fichier->entete.LastBloc;
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
    FichierTof *fichier = malloc(sizeof(fichier));
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

void chargementInitialeTof(FichierTof *fichier, int n, BufferTof *buffer) {
    int i = 0, j = 0;
    StudentIndexRecord record;
    //BufferTof buffer;
    for (int k = 0; k < n; ++k) {
        printf("La cle: ");
        scanf("%d", &record.key);
        printf("L\'information: ");
        scanf("%d", &record.data);
        printf("\n");
        if (j < MAX) {
            buffer->tab[j] = record;
            j++;
        } else {
            buffer->nb = j - 1;
            //fwrite(&buffer, sizeof(BufferTof), 1, getFileTof(fichier));
            ecrireBlocTof(fichier, i, buffer);
            i++;
            buffer->tab[0] = record;
            j = 1;
        }
    }
    buffer->nb = j - 1;
    //fwrite(&buffer, sizeof(BufferTof), 1, getFileTof(fichier));
    ecrireBlocTof(fichier, i, buffer);
    setEnteteTof(fichier, 1, i);
    setEnteteTof(fichier, 2, n);
}

void printFileTof(FichierTof *fichier) {
    BufferTof buffer;
    buffer.nb = 0;

    for (int i = 0; i <= getEnteteTof(fichier, 1); ++i) {
        lireBlocTof(fichier, i, &buffer);
        for (int j = 0; j <= buffer.nb; j++) {
            printf("\nData: %d, Key: %d \n", buffer.tab[j].data, buffer.tab[j].key);
        }
    }
}

void rechercheTof(FichierTof *fichier, int key, int *i, int *j, BufferTof *buffer, bool *found, bool *isDeleted) {
    //don't forget to check if it's not erased !!!
    *i = 0;
    *j = 0;
    int bi = 0;
    int bs = getEnteteTof(fichier, 1) - 1;
    int sup = 0;
    int inf = 0;
    bool stop = false;
    *found = false;
    *isDeleted = false;
    while ((bi <= bs) && (!*(found)) && (!stop)) {
        *i = (bi + bs) / 2;
        lireBlocTof(fichier, *i, buffer);
        if ((key >= buffer->tab[0].key) && (key <= buffer->tab[buffer->nb].key)) {
            inf = 0;
            sup = buffer->nb - 1;
            while ((inf <= sup) && (!*(found))) {
                *j = (inf + sup) / 2;
                if (key < buffer->tab[*j].key) sup = (*j) - 1;
                else if (key > buffer->tab[*j].key) inf = (*j) + 1;
                else {
                    *found = true;
                    if (buffer->tab[*j].isDeleted) *isDeleted = true;
                }
            }
            if (inf > sup) {
                *j = inf;
                stop = true;
            }
        } else if ((key < buffer->tab[0].key)) bs = (*i) - 1;
        else if (key > buffer->tab[buffer->nb].key) bi = (*i) + 1;
    }
    if (bi > bs){
        *i = bi;
        *j = 0;
    }

}

void insertionTof(FichierTof *fichier, StudentIndexRecord record, BufferTof *buffer) {

    lireBlocTof(fichier, getEnteteTof(fichier, 1), buffer);
    if (buffer->nb < MAX - 1) {
        buffer->tab[buffer->nb] = record;
        buffer->nb++;
    } else {
        buffer->tab[0] = record;
        buffer->nb = 0;
        setEnteteTof(fichier, 1, getEnteteTof(fichier, 1));
    }
    ecrireBlocTof(fichier, getEnteteTof(fichier, 1), buffer);
    setEnteteTof(fichier, 2, getEnteteTof(fichier, 2) + 1);

}

void supressionTof(FichierTof *fichier, int k, BufferTof *buffer) {
    int i, j;
    StudentIndexRecord record;
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