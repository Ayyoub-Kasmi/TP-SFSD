#ifndef UNTITLED_FILES_LIBRARY_H
#define UNTITLED_FILES_LIBRARY_H

#define MAX 4 //This is the maximum size of a block

//typedef struct {
//    int data;
//}TDATA;

typedef struct {
//    TDATA tab[MAX];
    int tab[MAX];
    int nb; //number of elements within the block
    int next; //pointer to the next block in the file
} BUFF;

typedef struct {
    int numberOfBlocks; //number of blocks in the file
    int root; //the first block of the file
    int tail; //the last block of the file
    int firstFreeIndex; //the first free index in the tail block
    int numberOfDeletedData; //number of data deleted
    int numberOfTotalElements; //total number of the elements of the whole file
} HEADER;

typedef struct {
    FILE* pointer;
    char* name;
    HEADER header;
} LnOF;

LnOF* openFile(char* fileName, char mode);
void closeFile(LnOF* file);
void setHeader(LnOF* file, int field, int value);
void printHeaderInfo(LnOF* file);



#endif //UNTITLED_FILES_LIBRARY_H
