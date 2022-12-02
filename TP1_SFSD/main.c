#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "tovcFunctions.h"
#include "LnOF-library.h"

StudentsIdArray studentsIdArray;
RoomIdArray roomIdArray;

int main() {
//    srand(time(NULL));
//    Fichier fichier;
//    Buffer buffer;
//    char chaine[5];
//    int j = 0;
//    int i = 0;
//    int i1 = 247593;
//    char str[10];
//
//    sprintf(str, "%d", i1);
//    buffer.tab[0] = 'f' ;
//    buffer.tab[1] = 'a';
//    buffer.tab[2] = 'r';
//    buffer.tab[3] = 'e';
//    buffer.tab[4] = 's';
//    buffer.positionLibre = 5;
//    printf("%d", sizeof(chaine));
//    lirechaine(&fichier, &buffer, chaine, sizeof(chaine), &i, &j);
//
//    for (int k = 0; k < 10; ++k) {
//        printf("%s %d", chaine, rand());
//    }
//
//
//    printf("\n%s", str);
//
//    char str1[10] = "213";
//    sscanf(str1, "%d", &i1);
//    printf("\n%d", i1);

studentsIdArray.nb = 0;
studentsIdArray.nb = 0;

//    for (int i = 0; i < 100; ++i) {
//        generateStudentId(&studentsIdArray);
//    }
//
//    for (int i = 0; i < 100; ++i) {
//        printf("%d\n", studentsIdArray.tab[i]);
//    }

    for (int i = 0; i < 30; ++i) {
        generateClassId(&roomIdArray);
    }

    for (int i = 0; i < 30; ++i) {
        printf("%d\n", roomIdArray.tab[i]);
    }



    return 0;
}


//char text[20];
//int digit;
//for (digit = 0; digit < 10; ++digit)
//{
//text[digit] = digit + '0';
//puts(text);
//}