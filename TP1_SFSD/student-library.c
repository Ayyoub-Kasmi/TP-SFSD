#include <limits.h>
#include <string.h>
#include <stdarg.h>
#include "student-library.h"
#include "TofIndexFunctions.h"

/*************************************** Auxiliary functions ***********************************************/
void skip(FichierTovc *fichier, int steps, int *i, int *j) {
    (*j) += steps;
    if (*j >= TOVC_BUFFER_SIZE) {
        (*i)++;
        lireBloc(fichier, *i, &bufferTovcData);
        (*j) -= TOVC_BUFFER_SIZE;
    }
}

void searchClassIndex(FichierTof *indexFile, int *i, int *j, int id, int *indexI, int *indexJ, bool *found, bool *isDeleted) {

    //To change from here

    rechercheTof(indexFile, id, indexI, indexJ, &bufferTofClass, found, isDeleted);
    if( (*indexI) == INT_MAX){
        *i = INT_MAX;
    } else {
        lireBlocTof(indexFile, *indexI, &bufferTofClass);
        *i = bufferTofClass.tab[*indexJ].i;
        *j = bufferTofClass.tab[*indexJ].j;
    }
}

void insertClassInIndex(FichierTof *indexFile, int classID, int i, int j){

}

void removeClassFromIndex(int classID){

}

void searchClassIndexDichoSup(FichierTof *indexFile, int classID, int pos, bool* found, bool *isDeleted){

};

/*************************************** Main functions ***********************************************/

void
searchStudent(FichierTovc *fichier, FichierTof *indexFile, Student student, int *i, int *j, int *indexI, int *indexJ,
              bool *found) {
//    typedef struct {
//
//        char firstName[MAX_FIRST_NAME_SIZE];
//        char lastName[MAX_LAST_NAME_SIZE];
//        int class;
//        int id;
//        char gender;
//        char isDeleted;
//        float marks[MAX_NUMBER_OF_SUBJECTS];
//    } Student;

    //If we found him we're going to return the start of the record because we can have a lot of modifications
    //to do so we're going to decide later.

    //setting up some string buffers for reading from the file
    char firstNameSize[FIRSTNAME_LENGTH + 1];
    char lastNameSize[LASTNAME_LENGTH + 1];
    char classID[CLASS_ID_SIZE + 1];
    char ID[STUDENT_ID_SIZE + 1];
    char fullName[MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE + 1];
    char roomString[ROOM_SIZE + 1];

    //declaring of necessary variables
    int class, offset;
    *found = false;
    bool isDeleted; //make this a param

    //Getting the starting positions of the studentLevel
    searchClassIndex(indexFile, i, j, student.class, indexI, indexJ, found, &isDeleted);

    if(!(*found)){
        if( (*i) == INT_MAX){
            *i = getEntete(fichier, 1)-1;
            *j = getEntete(fichier, 2);
        }
        printf("class doesn't exist! ==> create a new class...\nHere are the coordinates: (%d , %d)\n", *i, *j);
        //set the correct i and j for the new class (or check if the search already does) then return
        return;
    }else{
        *found = false;
    }
    lireBloc(fichier, *i, &bufferTovcData);

    //variables to save positions i and j
    int tempI;
    int tempJ;

    while (!(*found)) {      //return statements are used to quit the loop if "stop" conditions are met to save variables

        //saving the starting positions of the read student before reading advancing and reading its information
        tempI = *i;
        tempJ = *j;

        //read the lengths of first name and last name so to skip directly if it's not the right student

        lirechaine(fichier, &bufferTovcData, firstNameSize, FIRSTNAME_LENGTH, i, j);
        int firstNameSizeInt = stringToInt(firstNameSize, FIRSTNAME_LENGTH);
        lirechaine(fichier, &bufferTovcData, lastNameSize, LASTNAME_LENGTH, i, j);
        int lastNameSizeInt = stringToInt(lastNameSize, LASTNAME_LENGTH);
        lirechaine(fichier, &bufferTovcData, classID, CLASS_ID_SIZE, i, j);

        if (classID[0] == 'p') {
            classID[0] = '0';
        }

        class = stringToInt(classID, CLASS_ID_SIZE);
        int studentLevel = (class / 100) % 10;

        if (student.class == class) {
            //class found ===> compare IDs until finding the student or stopping
            printf("class found!\n");
            //read the ID
            lirechaine(fichier, &bufferTovcData, ID, STUDENT_ID_SIZE, i, j);
            printf("\nstudent id read: %s", ID);


            int x = stringToInt(ID, STUDENT_ID_SIZE);
            if (student.id == stringToInt(ID, STUDENT_ID_SIZE)) {
                //student found ===> stop
                *i = tempI; //i will receive the starting position (and not the IsDeleted field) since
                // we will need to modify other fields as well
                *j = tempJ;
                *found = true;
                printf("student found!\t Here are the coordinates: (%d, %d)\n", *i, *j);
                return;
            } else {
                //student not found, decide whether to advance or stop ==> compare names
                offset = IS_DELETED_SIZE +
                         MARK_LENGTH * numberOfSubjectsPerLevel[studentLevel]; //skip to the field of "firstName"
                skip(fichier, offset, i, j);
                //considering that strcmp comparaison is relatively true even when using full name concatinated

                lirechaine(fichier, &bufferTovcData, fullName,firstNameSizeInt+ lastNameSizeInt, i,j);

                //compare first names
                fullName[firstNameSizeInt + lastNameSizeInt] = '\0';
                printf("This is the result of the comparison: %d\n", strcmp(student.fullName, fullName));
                printf("these are the last chars: %d %d\n", student.fullName[10], fullName[10]);
                if (strcmp(student.fullName, fullName) < 0) {

                    *i = tempI;
                    *j = tempJ;
                    return; //Because we're sure that he doesn't exist

                } else {
                    offset = GENDER_SIZE;
                    skip(fichier, offset, i, j);
                }


            }
        } else if (class > student.class) {
            //passed the potential student's class ==> stop
            printf("stopped... current 'class' value is %d\n", class);
            *i = tempI;
            *j = tempJ;
            //WE HAVE TO INSERT HIM IN THE LAST POSITION OF THAT CLASS
            return; //to be reviewed
        }

        if (*i == getEntete(fichier, 1)-1) {
            if (*j >= getEntete(fichier, 2)) {
                //reached last element ==> quit the loop
                printf("last element... current 'class' value is %d\n", class);

                return; //i and j already have the correct values (but to be tested to confirm)
            }
        }
    }
}
void insertStudent(FichierTovc *fichier, FichierTof *indexFile, Student student) {
    int i = 0;
    int j = 0;
    int indexI = 0;
    int indexJ = 0;
    bool found = false;
    searchStudent(fichier, indexFile, student, &i, &j, &indexI, &indexJ, &found);
    if (!found) {
        //some code to create the student string
        char container1[4];//used to do the int => string conversion
        int totalStudentSize = FIRSTNAME_LENGTH + LASTNAME_LENGTH + CLASS_ID_SIZE + STUDENT_ID_SIZE + IS_DELETED_SIZE
                + numberOfSubjectsPerLevel[student.class / 100] * MARK_LENGTH + student.firstNameSize
                + student.lastNameSize + GENDER_SIZE;
        char stringBuffer[totalStudentSize+1];
        stringBuffer[totalStudentSize] = '\0';

        sprintf(container1, "%d%d", student.lastNameSize / 10,
                student.lastNameSize % 10); //lastNameSize can be a number of one digit

        //Write First Name size
        strcpy(stringBuffer, container1);
        char firstNameSizeString[FIRSTNAME_LENGTH + 1]; //+1 for the '\0' character
        sprintf(container1, "%d%d", student.firstNameSize / 10,
                student.firstNameSize % 10); //firstNameSize can be a number of one digit
        strcat(stringBuffer, container1);
        //the string that we are going to insert
        //Write ClassID
        char classIDString[CLASS_ID_SIZE + 1];
        intToString(classIDString, student.class, CLASS_ID_SIZE);
        classIDString[CLASS_ID_SIZE] = '\0';
        if ((student.class / 100) % 10 == 0) {
            classIDString[0] = 'p';
        }

        strcat(stringBuffer, classIDString);
        //Write ID
        char studentIdString[STUDENT_ID_SIZE + 1];
        intToString(studentIdString, student.id, STUDENT_ID_SIZE);
        studentIdString[STUDENT_ID_SIZE] = '\0';

        strcat(stringBuffer, studentIdString);

        //Write isDeleted
        char isDeletedString[IS_DELETED_SIZE+1];
        isDeletedString[0] = student.isDeleted;
        isDeletedString[1] = '\0';
        strcat(stringBuffer, isDeletedString);
        //Write marks array
        int level = (student.class / 100) % 10;
        int markWholePart;
        int markDecimalPart;
        int intMark;
        char markWholePartString[MARK_WHOLE_PART_LENGTH + 1];
        char markDecimalPartString[MARK_DECIMAL_PART_LENGTH + 1];
        for (int k = 0; k < numberOfSubjectsPerLevel[level]; ++k) {
            intMark = student.marks[k] * 100;
            markWholePart = intMark / 100;
            markDecimalPart = intMark % 100;

            sprintf(markWholePartString, "%d%d", (markWholePart / 10) % 10, markWholePart % 10);
            sprintf(markDecimalPartString, "%d%d", (markDecimalPart / 10) % 10, markDecimalPart % 10);

            strcat(stringBuffer, markWholePartString);
            strcat(stringBuffer, markDecimalPartString);
        }

        //Write Full name
        strcat(stringBuffer, student.fullName);

        //Write gender
        strcat(stringBuffer, &student.gender);

        bool endOfFile = false;

        int k = 0;
        int m = -1;
        char c;
        int bufferPos = TOVC_BUFFER_SIZE; if (i == getEntete(fichier, 1)-1) bufferPos = getEntete(fichier, 2);
        bool new = false;

        while( !endOfFile || k != m +1){
            if(k >= totalStudentSize) k = 0;
            if( j >= TOVC_BUFFER_SIZE){
                ecrireBloc(fichier, i, &bufferTovcData);
                i++;
                j=0;
                if(i < getEntete(fichier, 1)) lireBloc(fichier, i, &bufferTovcData);
                if( i == getEntete(fichier, 1)-1) bufferPos = getEntete(fichier, 2);
            }else{

                if (j < bufferPos){
                    c = bufferTovcData.tab[j];
                    bufferTovcData.tab[j] = stringBuffer[k];
                    k++;
                    m++; if(m>=totalStudentSize) m = 0;
                    stringBuffer[m] = c;
                } else {
                    endOfFile = true;
                    bufferTovcData.tab[j] = stringBuffer[k];
                    k++;
                }
                j++;//Here
            }

        }

        if(j != 0) ecrireBloc(fichier, i, &bufferTovcData);

        //Normally the good bloc is read when we called the search function
        indexJ++;

        while (indexI < getEnteteTof(indexFile, 1)) {
            if (indexJ >= TOF_BUFFER_SIZE) {
                indexJ = 0;
                indexI++;
                if (indexI >= getEnteteTof(indexFile, 1)) break;
                lireBlocTof(indexFile, indexI, &bufferTofClass);
            }
            bufferTofClass.tab[indexJ].j += totalStudentSize;
            while (bufferTofClass.tab[indexJ].j >= TOVC_BUFFER_SIZE) {
                bufferTofClass.tab[indexJ].i++;
                bufferTofClass.tab[indexJ].j -= TOVC_BUFFER_SIZE;
            }
            indexJ++;
        }


        setEntete(fichier, 1, i+1);
//    if (*j >= buffer->positionLibre) buffer->positionLibre = *j; ==> j will be auto set inside ecrire chaine
        setEntete(fichier, 2, j);

        ecrireBloc(fichier, i, &bufferTovcData);
        setEntete(fichier, 3, getEntete(fichier, 3) + totalStudentSize);
    }
}

void updateStudentInfo(FichierTovc *fichierTovc, Student student, int numberOfArguments, ...) {
    FichierTof *indexFile = ouvrirFichierTof(CLASS_INDEX_FILE_PATH, 'A');
    //this "..." syntax is used so to receive an argument of dynamic type (field number & value)

/*

Format of the function for each case:

    1- update student studentID: updateStudentInfo(fichierTovc, student, numberOfArguments, id)
    2- update class studentID: updateStudentInfo(fichierTovc, student, numberOfArguments, newClass)
    3- update names (fullname): updateStudentInfo(fichierTovc, student, numberOfArguments, firstNameSizeInt, lastNameSizeInt, fullname)
    4- update gender: updateStudentInfo(fichierTovc, student, numberOfArguments, gender)
    5- update mark: updateStudentInfo(fichierTovc, student, numberOfArguments, subjectNumber, mark)
 */

    // initialize argument list
    va_list list;
    va_start(list, numberOfArguments);
    int fieldNumber = va_arg(list, int);

    //declaring necessary variables
    int *i, *j, tempI, tempJ, offset, level;
    bool found, isDeleted;
    char firstNameSize[FIRSTNAME_LENGTH+1];
    char lastNameSize[LASTNAME_LENGTH+1];
    char fullName[MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE + 1];
    char studentID[STUDENT_ID_SIZE + 1];
    char markString[MARK_LENGTH + 1];

    //search for the student first
    searchStudent(fichierTovc, NULL, student, i, j, NULL, 0, &found);
    if (!found) {
        printf("student doesn't exist!\n");
        return;
    }

    switch (fieldNumber) {
        case 1:
            printf("updating student id\n");

            int id = va_arg(list, int);
            offset = FIRSTNAME_LENGTH + LASTNAME_LENGTH + CLASS_ID_SIZE;
            skip(fichierTovc, offset, i, j); //skip to studentID field in the file

            intToString(studentID, id, STUDENT_ID_SIZE); //convert id to string

            ecrireChaine(fichierTovc, &bufferTovcData, studentID, STUDENT_ID_SIZE, i, j);
//            if ((*j) < TOVC_BUFFER_SIZE) ecrireBloc(fichierTovc, *i, &bufferTovcData);
            if( (*j) != 0) ecrireBloc(fichierTovc, *i, &bufferTovcData);
            break;

        case 2:
            printf("updating student class\n");
            //the approach is to logically delete the older version of the student and insert a new one

            int newClass = va_arg(list, int);

            if(student.class == newClass){
                printf("Student is already in class %d\n", newClass);
                return;
            }

            //now the student will surely move to a new class:

            tempI = *i; tempJ = *j; //saving the starting positions of the student for later comparison

            //saving the first name and last name sizes because we may need them in a certain case
            lirechaine(fichierTovc, &bufferTovcData, firstNameSize, FIRSTNAME_LENGTH, i, j);
            lirechaine(fichierTovc, &bufferTovcData, lastNameSize, LASTNAME_LENGTH, i, j);

            //skip to "isDeleted"
            offset = CLASS_ID_SIZE + STUDENT_ID_SIZE;
            skip(fichierTovc, offset, i, j);

            //Now j points on the "isDeleted" character:
            bufferTovcData.tab[*j] = '0';
            ecrireBloc(fichierTovc, *i, &bufferTovcData);

            //checking if the student is the first one in his class:
//            searchClassIndex(indexFile, i, j, student.class, &found, &isDeleted);  fix parameters

            if(tempI == (*i) && tempJ == (*j)){
                //the student is the first in his class, we check if he's the last one

                //skip to the end of the student record
                level = student.class * 100;
                offset = IS_DELETED_SIZE + MARK_LENGTH * numberOfSubjectsPerLevel[level]
                         + stringToInt(firstNameSize, FIRSTNAME_LENGTH)
                         + stringToInt(lastNameSize, LASTNAME_LENGTH)
                         + GENDER_SIZE;
                skip(fichierTovc, offset, i, j);

                //now we reached the next student, checking if they belong to the same class:
                offset = FIRSTNAME_LENGTH + LASTNAME_LENGTH;
                skip(fichierTovc, offset, i, j);

                char classID[CLASS_ID_SIZE+1];
                lirechaine(fichierTovc, &bufferTovcData, classID, CLASS_ID_SIZE, i, j);

                if (student.class != stringToInt(classID, CLASS_ID_SIZE) ){
                    //next student is from a different class ==> delete the current class
                    removeClassFromIndex(student.class);
                }
            }

            int pos;
            searchClassIndexDichoSup(indexFile, newClass, pos, &found, &isDeleted);

            if(found && !isDeleted){
                if(pos != bufferTofClass.nb){
                    //if pos + 1 exists
                    bufferTofClass.tab[pos].i = bufferTofClass.tab[pos + 1].i;
                    bufferTofClass.tab[pos].j = bufferTofClass.tab[pos + 1].j;
                } else{
                    //the current class is the last one in the index
                    bufferTofClass.tab[pos].i = getEnteteTof(indexFile, 1) - 1;
                    bufferTofClass.tab[pos].j = bufferTofClass.nb;

                }
            } else if(found && isDeleted){
                bufferTofClass.tab[pos].isDeleted = false;
                if(pos != bufferTofClass.nb){
                    //if pos + 1 exists
                    bufferTofClass.tab[pos].i = bufferTofClass.tab[pos + 1].i;
                    bufferTofClass.tab[pos].j = bufferTofClass.tab[pos + 1].j;
                } else{
                    //the current class is the last one in the index
                    bufferTofClass.tab[pos].i = getEnteteTof(indexFile, 1) - 1; //last block
                    bufferTofClass.tab[pos].j = bufferTofClass.nb; //last position
                }
            } else if(!found){
                //the new class will take the starting positions of the class that comes after it
                //the search will already give the next class
                insertClassInIndex(indexFile, newClass, classesIndex[pos].i, classesIndex[pos].j);
            }

            //now we insert the student in the students file
            insertStudent(fichierTovc, indexFile, student);

            break;

        case 3:
            printf("updating student full name\n");

            int firstNameSizeInt = va_arg(list, int);
            int lastNameSizeInt = va_arg(list, int);
            char *fullname = va_arg(list, char*);
            printf("here is the fullname: %s\n", fullname);
            printf("and here is the length of the fullname: %llu", strlen(fullname));

            //the approach is to logically delete the current student and create a new one with the new name

            //skip to "Student studentID" field
            tempI = *i; tempJ = *j; //saving the starting positions of the current student
            offset = FIRSTNAME_LENGTH + LASTNAME_LENGTH + CLASS_ID_SIZE; //skipping to the student studentID;
            skip(fichierTovc, offset, i, j);

            //overwrite the student studentID with "0000" (means invalid studentID)
            strcpy(studentID, "0000");
            studentID[STUDENT_ID_SIZE] = '\0';
            ecrireChaine(fichierTovc, &bufferTovcData, studentID, STUDENT_ID_SIZE, i, j);

            //now j points to "isDeleted" ==> deleting the current student
            bufferTovcData.tab[*j] = '0';
            ecrireBloc(fichierTovc, *i, &bufferTovcData); //is it necessary?

            strcpy(student.fullName, fullname);
            student.firstNameSize = firstNameSizeInt; //get them from
            student.lastNameSize = lastNameSizeInt;
            insertStudent(fichierTovc, indexFile, student);

            break;

        case 4:
            printf("updating student gender\n");

            char gender = va_arg(list, int);
            offset = FIRSTNAME_LENGTH + LASTNAME_LENGTH + CLASS_ID_SIZE + STUDENT_ID_SIZE;
            skip(fichierTovc, offset, i, j); //skip to "isDeleted" field in the file

//            ecrireChaine(fichierTovc, &bufferTovcData, studentID, gender, i, j);
            bufferTovcData.tab[*j] = gender;
            ecrireBloc(fichierTovc, *i, &bufferTovcData);
            break;

        case 5:
            //here we can add an option for: a- change a single mark;  b- change all marks
            printf("updating student mark\n");
            double mark = (float) va_arg(list, double);
            int subjectNumber = va_arg(list, int); // subjectNumber starts from 1

            printf("here is the mark: %.2f\n", mark);

            offset = FIRSTNAME_LENGTH + LASTNAME_LENGTH + CLASS_ID_SIZE + STUDENT_ID_SIZE + IS_DELETED_SIZE
                     + (subjectNumber -1) * MARK_LENGTH;
            skip(fichierTovc, offset, i, j);

            int intMark = mark * 100;
            intToString(markString, intMark, MARK_LENGTH);

            //now we're pointing to the desired mark
            ecrireChaine(fichierTovc, &bufferTovcData, markString, MARK_LENGTH, i, j);
            if( (*j) != 0) ecrireBloc(fichierTovc, *i, &bufferTovcData);
            break;

        default:
            printf("invalid field number");
    }
    va_end(list);
}




void deleteStudent(FichierTovc *fichier, Student student) {
    int i = 0;
    int j = 0;
    bool found = false;
    searchStudent(fichier, NULL, student, &i, &j, NULL, 0, &found);

    if (found) {
        //we have to take the student level to calculate the length of his table of marks.
        char firstNameSizeString[FIRSTNAME_LENGTH + 1];
        char lastNameSizeString[LASTNAME_LENGTH + 1];

        lirechaine(fichier, &bufferTovcData, lastNameSizeString, LASTNAME_LENGTH, &i, &j);
        lirechaine(fichier, &bufferTovcData, firstNameSizeString, FIRSTNAME_LENGTH, &i, &j);

        int lastNameSize = stringToInt(lastNameSizeString, LASTNAME_LENGTH);
        int firstNameSize = stringToInt(firstNameSizeString, FIRSTNAME_LENGTH);

        int studentLevel;
        if (bufferTovcData.tab[j] == 'p') {
            studentLevel = 0;
        } else {
            studentLevel = stringToInt(&bufferTovcData.tab[j], 1);
        }
        skip(fichier, CLASS_ID_SIZE + STUDENT_ID_SIZE, &i, &j);

        bufferTovcData.tab[j] = '1';
        ecrireBloc(fichier, i, &bufferTovcData);

        skip(fichier,  IS_DELETED_SIZE +
                                    MARK_LENGTH * numberOfSubjectsPerLevel[studentLevel] + lastNameSize
                                    + firstNameSize + GENDER_SIZE, &i, &j);
        //Skip this record, since we deleted it.

        //We now have to update the number of chars deleted in the heaader

        int charsDeleted =  LASTNAME_LENGTH + FIRSTNAME_LENGTH + CLASS_ID_SIZE + STUDENT_ID_SIZE
                + IS_DELETED_SIZE + MARK_LENGTH * numberOfSubjectsPerLevel[studentLevel] + lastNameSize
                + firstNameSize + GENDER_SIZE;

        setEntete(fichier, 3, getEntete(fichier, 3) + charsDeleted);



    }
}