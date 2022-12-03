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
        fichier->entete.NumbrOfCharsInserted = value;
    } else if (pos == 3) {
        fichier->entete.numberOfCharsDeleted = value;
    }
}

int getEntete(Fichier *fichier, int pos) {
    if (pos == 1) {
        return fichier->entete.numberOfBlocs;
    } else if (pos == 2) {
        return fichier->entete.NumbrOfCharsInserted;
    } else if (pos == 3) {
        return fichier->entete.numberOfCharsDeleted;
    } else return -1; // <====== NULL is incompatible with int type
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

int generate4positionInt(int seed) {
    int randomID;
    srand((unsigned) time(0) + seed);
    for (int counter = 0; counter < 2; ++counter) {
        //this loop is to ensure the randomness of the generated value
        randomID = rand() % 10000;
    }
    return randomID;
}

void generateStudentId(StudentsIdArray *studentsIdArray) {
    int i = 0;
    int id = 0;
    bool found = true;
    if (studentsIdArray->nb <= 0) {
        id = generate4positionInt(id);
        insertStudentId(studentsIdArray, id);
        return;
    }
    while (found) {
        id = generate4positionInt(id);
        searchStudentId(studentsIdArray, id, &i, &found);
    }
    insertStudentIdWithoutSearching(studentsIdArray, id, i);
}

void searchStudentId(StudentsIdArray *studentsIdArray, int id, int *i, bool *found) {
    //normal binary search in the studentsIdArray
    *found = false;
    if (studentsIdArray->nb > 0) {
        int inf = 0;
        int sup = studentsIdArray->nb - 1;
        while ((inf <= sup) && (!(*found))) {
            *i = (inf + sup) / 2;
            if (id > studentsIdArray->tab[*i]) {
                inf = *i + 1;
            } else if (id < studentsIdArray->tab[*i]) {
                sup = *i - 1;
            } else {
                (*found) = true;
            }
        }
        if ((!(*found)) ) {
            *i = inf;
        }
    } else {
        *i = 0;
    }
}

void insertStudentId(StudentsIdArray *studentsIdArray, int id) {
    //insertion with delays to keep the order in the studentsIdArray
    if (studentsIdArray->nb <= 0) {
        studentsIdArray->tab[0] = id;
        studentsIdArray->nb++;
    } else {
        int i = 0;
        bool found = false;
        searchStudentId(studentsIdArray, id, &i, &found);
        if (!found) {
            if (id < studentsIdArray->tab[i]) {
                for (int k = studentsIdArray->nb; k >= i; --k) {
                    studentsIdArray->tab[k] = studentsIdArray->tab[k - 1];
                }
            }
            studentsIdArray->tab[i] = id;
            studentsIdArray->nb++;
        }
    }

}

void insertStudentIdWithoutSearching(StudentsIdArray *studentsIdArray, int id, int i) {
    //insertion with delays to keep the order in the studentsIdArray
    if (studentsIdArray->nb <= 0) {
        studentsIdArray->tab[0] = id;
        studentsIdArray->nb++;
    } else {
        if (id < studentsIdArray->tab[i]) {
            for (int k = studentsIdArray->nb; k > i; --k) {
                studentsIdArray->tab[k] = studentsIdArray->tab[k - 1];
            }
        }
        studentsIdArray->tab[i] = id;
        studentsIdArray->nb++;

    }

}

int generate2positionInt(int seed) {
    int randomID;
    srand((unsigned) time(0) + seed);
    for (int counter = 0; counter < 2; ++counter) {
        //this loop is to ensure the randomness of the generated value
        randomID = (rand() % 100) + 1; // So that the room numbers will be from 1 to 100
    }
    return randomID;
}

int generateTheLevel(int seed) {
    int randomID;
    srand((unsigned) time(0) + seed);
    randomID = rand() % 10;
    while (randomID > 5) {
        //this loop is to ensure the randomness of the generated value
        randomID = rand() % 10;
        // we'll consider for now that 0 represents the preparative year and we'll change it later
    }
    return randomID;
}

void generateClassId(RoomIdArray *roomIdArray) {
    int id = 0;
    bool found = true;
    if (roomIdArray->nb <= 0) {
        id = generate2positionInt(id);
        id += 100 * generateTheLevel(id);
        insertRoomId(roomIdArray, id);
        return;
    }
    while (found) {
        id = generate2positionInt(id);
        searchRoomNumber(roomIdArray, id, &found);
    }
    id += 100 * generateTheLevel(id);
    insertRoomId(roomIdArray, id);
}

void searchClassId(RoomIdArray *roomIdArray, int id, int *i, bool *found) {
    //normal binary search in the studentsIdArray
    *found = false;
    if (roomIdArray->nb > 0) {
        int inf = 0;
        int sup = roomIdArray->nb - 1;
        while ((inf <= sup) && (!(*found))) {
            *i = (inf + sup) / 2;
            if (id > roomIdArray->tab[*i]) { // to check only the room number and ignore the last one
                inf = *i + 1;
            } else if (id < roomIdArray->tab[*i]) {
                sup = *i - 1;
            } else {
                (*found) = true;
            }
        }
        if ((!(*found)) ) {
            *i = inf;
        }
    } else {
        *i = 0;
    }
}

void searchRoomNumber(RoomIdArray *roomIdArray, int roomNumber, bool *found) {
    //normal binary search in the studentsIdArray
    *found = false;
    if (roomIdArray->nb > 0) {
        //the search will be sequentiel due to the classes that are ordered by the school level and then the
        //roomNumber
        for (int j = 0; j < roomIdArray->nb; ++j) {
            if (roomIdArray->tab[j] % 100 == roomNumber){
                *found = true;
            }
        }
    }
}

void insertRoomId(RoomIdArray *roomIdArray, int id) {
    //insertion with delays to keep the order in the studentsIdArray
    if (roomIdArray->nb <= 0) {
        roomIdArray->tab[0] = id;
        roomIdArray->nb++;
    } else {
        int i = 0;
        bool found = false;
        searchClassId(roomIdArray, id, &i, &found);
        if (!found) {
            if (id < roomIdArray->tab[i]) {
                for (int k = roomIdArray->nb; k >= i; --k) {
                    roomIdArray->tab[k] = roomIdArray->tab[k - 1];
                }
            }
            roomIdArray->tab[i] = id;
            roomIdArray->nb++;
        }
    }

}

void insertRoomIdWithoutSearching(RoomIdArray *roomIdArray, int id, int i) {
    //insertion with delays to keep the order in the studentsIdArray
    if (roomIdArray->nb <= 0) {
        roomIdArray->tab[0] = id;
        roomIdArray->nb++;
    } else {
        if (id < roomIdArray->tab[i]) {
            for (int k = roomIdArray->nb; k > i; --k) {
                roomIdArray->tab[k] = roomIdArray->tab[k - 1];
            }
        }
        roomIdArray->tab[i] = id;
        roomIdArray->nb++;

    }

}


