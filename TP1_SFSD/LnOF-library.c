#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "LnOF-library.h"

/*side notes:
 * Make sure to update the name property of the file in the correct function
 * Declare buffers as global variables
*/

/*                          Abstract Machine for LnOf                       */
LnOF* openFile(char* fileName, char mode){
    //allocate the file structure variable
    LnOF* file = (LnOF*)malloc(sizeof(LnOF));

    //open the file according to the indicated mode
    if(toupper(mode) == 'A') {
        //setting the pointer to the file
        file->pointer = fopen(fileName, "r+");

        //checking the existence of the file if mode is 'A'
        if(file->pointer == NULL){
            printf("File doesn't exist!\n");
            free(file);
        }
        else{
            //loading the header
            fread(&(file->header), sizeof(HEADER), 1, file->pointer);
        }
        return NULL;
    }
    else if(toupper(mode) == 'N') {
        //setting the pointer to the new file
        file->pointer = fopen(fileName, "w+");
        file->name = fileName;

        //setting up the default values of the header
        setHeader(file, 1, 0);
        setHeader(file, 1, -1);
        setHeader(file, 1, -1);
        setHeader(file, 1, 0);
        setHeader(file, 1, 0);
        setHeader(file, 1, 0);

        //returning the file structure
        return file;
    }
    else {
        printf("Invalid mode!\n");
        return NULL;
    }
};

void closeFile(LnOF* file){
    //saving the file info (header) in the disk
    rewind(file->pointer);
    fwrite(&(file->header), sizeof(HEADER), 1, file->pointer);

    //close the file pointer
    rewind(file->pointer);
    fclose(file->pointer);

    //free the file structure
    free(file);
}

void setHeader(LnOF* file, int field, int value){
    switch (field) {
        case 1: file->header.numberOfBlocks = value; break;
        case 2: file->header.root = value; break;
        case 3: file->header.tail = value; break;
        case 4: file->header.firstFreeIndex = value; break;
        case 5: file->header.numberOfDeletedData = value; break;
        case 6: file->header.numberOfTotalElements = value; break;
        default:
            printf("Invalid header field number!\n");
    }
}

int getHeaderInformation(LnOF* file, int field){
    //checking the existence of the file
    if(file->pointer == NULL) printf("No file opened!\n");
    else {
        switch (field) {
            case 1: return file->header.numberOfBlocks;
            case 2: return file->header.root;
            case 3: return file->header.tail;
            case 4: return file->header.firstFreeIndex;
            case 5: return file->header.numberOfDeletedData;
            case 6: return file->header.numberOfTotalElements;
            default:
                printf("Invalid header field number!\n");
        }
    }
}


/*                          Print File Info                                 */
void printHeaderInfo(LnOF* file){
    if(file->pointer == NULL){
        printf("File doesn't exists! Make sure you opened the file correctly\n");
        return;
    }

    printf("Header information of %s: \n", file->name);
    printf("Number of total blocks: %d\n", file->header.numberOfBlocks);
    printf("Number of total elements: %d\n", file->header.numberOfTotalElements);
    printf("Number of the root block: %d\n", file->header.root);
    printf("Number of the tail block: %d\n", file->header.tail);
    printf("Number of the last free index (for the last block): %d\n", file->header.firstFreeIndex);
    printf("Number of deleted i elements: %d\n", file->header.numberOfDeletedData);
}


/*                          Content Manipulation                            */
void initialFileCreation(LnOF* file){
    //Caution: if the file wasn't opened yet:
    if(file->pointer == NULL){
        printf("Error: No file opened!\n");
        return;
    }

    //initializations & variables
    BUFF buffer;
    int data;
    int n; //The number of elements
    int numberOfBlocks=0; //To count the number of blocks that will be created
    int firstFreeIndex; //This index will point to the first available index in the last block
    int currentBlockNumber=1;
    buffer.nb = 0;

    //getting the number of elements to be inserted
    printf("Enter the number of elements: ");
    scanf("%d", &n);

    //inserting elements into the file
    for(int k=0; k<n; k++){
        //get i from user
        printf("Enter a number: ");
        scanf("%d", &data);

        //fill in the buffer
        buffer.tab[buffer.nb] = data;
        buffer.nb++;

        // if the buffer is full
        if(buffer.nb == TOVC_BUFFER_SIZE){
            buffer.next = currentBlockNumber + 1; //for an initial file creation, blocks will be in sequence
            fwrite(&buffer, sizeof(BUFF), 1, file->pointer);
            currentBlockNumber++;
            numberOfBlocks++;
            buffer.nb = 0;
            firstFreeIndex=0;
        }
    }

    // if there are some more elements remaining
    if(buffer.nb > 0){
        buffer.next = -1;
        fwrite(&buffer, sizeof(BUFF), 1, file->pointer);
        numberOfBlocks++;
        firstFreeIndex=buffer.nb+1;
    }

    //updating header information of the file
    setHeader(file, 1, numberOfBlocks);
    setHeader(file, 2, 1); //index of the root block
    setHeader(file, 3, currentBlockNumber);
    setHeader(file, 4, firstFreeIndex);
    setHeader(file, 6, n); //Total elements
}

int searchElement(LnOF* file, int value, int* blockNumber, int* index){
    //initializations & variables
    BUFF buffer;
    int root = getHeaderInformation(file, 2);
    *blockNumber = root;

    //getting the root block
    fseek(file->pointer, sizeof(HEADER)+sizeof(BUFF)*root, SEEK_SET);

    //the search loop
    while(buffer.next != -1){
        fread(&buffer, sizeof(BUFF), 1, file->pointer);
        for(int k=0; k<buffer.nb; k++){
            if(buffer.tab[k] == value) {
                *index = k;
                return 1; //This will cause the function to quit with a success code
            }
        }

        //reached the end of the current block, go to the next block
        if(buffer.next != -1){ //next block exists
            *blockNumber = buffer.next;
            fseek(file->pointer, sizeof(HEADER)+sizeof(BUFF)*buffer.next, SEEK_SET);
        }
    }
    return 0; //value not found
}

void insertElement(LnOF* file, int value){
    //variables and initializations
    BUFF buffer;
    int tail = getHeaderInformation(file, 3); //get the number of the last block
    int firstFreeIndex = getHeaderInformation(file, 4);

    //get the address of the tail block
    rewind(file->pointer);
    fseek(file->pointer, sizeof(HEADER)+sizeof(BUFF)*tail, SEEK_SET);

    //load the block into memory
    fread(&buffer, sizeof(BUFF), 1, file->pointer);
    fseek(file->pointer, -sizeof(BUFF), SEEK_CUR);

    //if the last block isn't full
    if(firstFreeIndex > 0){
        buffer.tab[firstFreeIndex] = value;
        buffer.nb++;
        fwrite(&buffer, sizeof(BUFF), 1, file->pointer);
    }
    else{
        //The last block is full. Firstly update the "next" field of the last block and save
        buffer.next = tail+1;
        fwrite(&buffer, sizeof(BUFF), 1, file->pointer);

        //Use the same buffer for the new block. Update the related fields
        buffer.next = -1;
        buffer.nb = 1;
        buffer.tab[0]=value;

        //write the new block
        fwrite(&buffer, sizeof(BUFF), 1, file->pointer);
    }

    //update the header information
    setHeader(file, 4, (firstFreeIndex+1) % TOVC_BUFFER_SIZE);
    setHeader(file, 6, getHeaderInformation(file, 6)+1);
}

void deleteElement(LnOF* file, int value){
    //initializations and variables
    int blockNumber, index;

    //look if the element exists
    if( searchElement(file, value, &blockNumber, &index) ){

    }
}
