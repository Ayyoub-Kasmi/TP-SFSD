#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//custom libraries:
#include "settings.h"
#include "TofIndexFunctions.h"
#include "DataManipulation.h"
#include "student-library.h"
#include "ArchiveManipulation.h"

#define SIZE 10

//Global variables declaration:

StudentsIdArray studentsIdArray;
ClassIdArray roomIdArray;
StudentsNamesArray studentsNamesArray;
position classesIndex[FIRST_LOAD_OF_CLASSES]; //positions i and j in the school file for each level

struct subjectsArray {

};
int numberOfSubjectsPerLevel[6] = {4, 5, 5, 7, 7, 7}; //just an example, not real i
//we can also declare the names of subjects as a matrix of Levels-Subjects, if we need the names

int numberOfClassesPerLevel[6];

MoyenneNonDenseIndex moyenneNonDenseIndex;


//Marks buffer:
float tableOfMarks[MAX_NUMBER_OF_SUBJECTS];

//File buffer:
BufferTovc bufferTovcData;
BufferTovc bufferTovcNewYear;
BufferTof bufferTofClass;
BufferTofMoyenne bufferTofMoyenne;
BufferTovc bufferTovcArchive;

int currentYear;


int main() {

//    FichierTovc *currentYearFile;
//    FichierTovc *archiveFile;
//    FichierTofMoyenne *archiveIndexFile;
//    FichierTovc* nextYearFile = ouvrirFichierTovc("2023_STUDENTS.bin", 'N');
//    FichierTof* nextYearIndexFile = ouvrirFichierTof("2023_CLASS_INDEX.bin", 'N');
//    FichierTof *classIndexFile;
//    int i = 0;
//    int j = 0;
//    bool new = true;
//    if (new) {
//        currentYearFile = ouvrirFichierTovc(CURRENT_YEAR_FILE_PATH, 'N');
//        archiveFile = ouvrirFichierTovc(CURRENT_YEAR_ARCHIVE_FILE_PATH, 'N');
//        archiveIndexFile = ouvrirFichierMoyenne("archiveIndexFile.bin", 'N');
//        classIndexFile = ouvrirFichierTof(CLASS_INDEX_FILE_PATH, 'N');
//        createSchoolYear(currentYearFile, classIndexFile, &i, &j);
//        rewind(getFile(currentYearFile));
//        fwrite(&currentYearFile->entete, sizeof(EnteteTovc), 1, getFile(currentYearFile));
//
//    } else {
//        archiveFile = ouvrirFichierTovc(CURRENT_YEAR_ARCHIVE_FILE_PATH, 'A');
//        archiveIndexFile = ouvrirFichierMoyenne("archiveIndexFile.bin", 'A');
//        currentYearFile = ouvrirFichierTovc(CURRENT_YEAR_FILE_PATH, 'A');
//        classIndexFile = ouvrirFichierTof(CLASS_INDEX_FILE_PATH, 'A');
//        lireBlocTof(classIndexFile, 0, &bufferTofClass);
//        updateNumberOfClassesPerLevel(&bufferTofClass);
//    }
//
//
//    i = 0;
//    j = 0;
////    lireBlocTof(classIndexFile, 0, &bufferTofClass);
//
//    Student student;
//    student.firstNameSize = 6;
//    student.lastNameSize = 8;
//    student.id = 1111;
//    student.class = 160;
//    strcpy(student.fullName, "houarimohammed");
//    student.gender = 'M';
//    student.isDeleted = '0';
//    student.marks[0] = 10.00;
//    student.marks[1] = 7.5;
//    student.marks[2] = 9.25;
//    student.marks[3] = 5.5;
//    student.marks[4] = 8.0;
////    printStudentsFile(currentYearFile);
//    printf("\n\n=======================\n\n");
//
//    archive(currentYearFile, classIndexFile, archiveFile, archiveIndexFile, nextYearFile, nextYearIndexFile);printf("\n\n=======================\n\n");
//    printArchiveFile(archiveFile);
//    printMoyenneIndex(archiveIndexFile);
//
//
//
//
//    //system("mkdir archive");
//
//
////    printClassIndex(classIndexFile);
//
////    insertStudent(currentYearFile, classIndexFile, student);
//
//
//    printf("\n\n");
////    printStudentsFile(currentYearFile);
//    printf("\n\n");
//    i = 0;
//
////    printClassIndex(classIndexFile);
//
//    printf("\n\ni: %d\tj: %d\n\n", i, j);
//    i = 23; j = 47;
//
//    lireBloc(currentYearFile, i, &bufferTovcData);
//    for(int k = 0; k<47; k++){
//        printf("%c", bufferTovcData.tab[j]);
//        j++;
//    }
//    fermerFichier(currentYearFile);
//    fermerFichier(nextYearFile);
//    fermerFichierMoyenne(archiveIndexFile);
//    fermerFichierTof(nextYearIndexFile);
//    fermerFichierTof(classIndexFile);

    int choice;
    int numberOfArchives; //Add it to settings.h
    Student student;
    while(1){
        //system("cls");
        //printHeader();
        printf("#############################################\n\n");
        printf("\t\t\tSchool Management Software\n");
        printf("Use this menu to navigate in the application:\n\n");
        printf("1) Edit the main file\n");
        printf("2) Edit archive files\n");
        printf("3) Print infos\n");
        printf("0) Exit\n\n");

        printf("Enter a number: ");
        scanf("%d", &choice);
        if(choice == 0) break;
        switch(choice){
            case 1:     //Edit the main file
                while(1){
                    printf("1) Create a new file\n");
                    printf("2) Edit current file\n\n");
                    printf("0) Exit\n\n");
                    printf("Enter a number: ");
                    scanf("%d", &choice);
                    if(choice == 0) break;
                    switch(choice){

                        case 1:     //Create a new file
                            //system("cls");
                            while(1){
                                printf("1) Auto-generated data\n");
                                printf("2) Manual insertion\n\n");
                                printf("Enter a number: ");
                                scanf("%d", &choice);
                                if(choice == 0) break;
                                switch(choice){
                                    case 1: //Auto-generate data
                                        //  createSchoolYear()
                                        printf("\n\nFile has been successfully created\n\n");
                                        break;

                                    case 2: //Manual
                                        printf("Feature coming soon...\n");
                                        break;
                                }
                            }

                            break;

                        case 2:     //Edit current file
                            while(1){
                                printf("1) Print a student\n");
                                printf("2) Insert a student\n");
                                printf("3) Delete a student\n");
                                printf("4) Update a student's information\n");
                                printf("0) Exit\n\n");
                                printf("Enter a number: ");
                                scanf("%d", &choice);
                                if(choice == 0) break;
                                switch(choice){
                                    case 1:     //Print a student
                                        //reading student info
                                        //search
                                        //print
                                        break;
                                    case 2:     //Insert a student
                                        //Reading student info
                                        // insertStudent()
                                        break;
                                    case 3:     //Delete a student
                                        //Reading class and ID
                                        // deleteStudent()
                                        break;
                                    case 4:     //update student info
                                        printf("\n\nChoose what to update");
                                        printf("1) Student ID\n");
                                        printf("2) Class ID\n");
                                        printf("3) Name\n");
                                        printf("4) Gender\n");
                                        printf("5) Mark\n\n");
                                        printf("0) Exit\n\n");
                                        printf("Enter a number: ");
                                        scanf("%d", &choice);
                                        if(choice == 0) break;
                                        printf("Student to edit: ");
                                        printf("Student's class: ");
                                        scanf("%d", &student.class);
                                        printf("Student's ID: ");
                                        scanf("%d", &student.id);
                                        strcpy(student.fullName, "zzzzzz"); //to search to the end of selected class
                                        //maek sure to set the values of numberOfArguemtns

                                        switch(choice){
                                            case 1:;
                                                int id;
                                                printf("Enter the new ID: ");
                                                scanf("%d", &id);
                                                updateStudentInfo(fichierTovc, student, numberOfArguments, id);
                                                break;
                                            case 2:;
                                                int newClass;
                                                printf("Enter the new class: ");
                                                scanf("%d", &newClass);
                                                updateStudentInfo(fichierTovc, student, numberOfArguments, newClass);
                                                break;
                                            case 3:;
                                                char firstName[MAX_FIRST_NAME_SIZE +1];
                                                char lastName[MAX_LAST_NAME_SIZE +1];
                                                char fullname[MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE +1];
                                                printf("Enter student's family name: (lower case only)");
                                                scanf("%s", lastName);
                                                int lastNameSizeInt = (int) strlen(lastName);
                                                printf("Enter student's first name (lower case only): ");
                                                scanf("%s", firstName);
                                                int firstNameSizeInt = (int) strlen(firstName);
                                                updateStudentInfo(fichierTovc, student, numberOfArguments, firstNameSizeInt, lastNameSizeInt, fullname);
                                                break;
                                            case 4:;
                                                char gender;
                                                printf("Enter the gender ( 'm' or 'f') : ");
                                                scanf("%c", &gender);
                                                updateStudentInfo(fichierTovc, student, numberOfArguments, gender);
                                                break;
                                            case 5:;
                                                float mark;
                                                printf("Enter the student's mark: ");
                                                scanf("%f", &mark);

                                                updateStudentInfo(fichierTovc, student, numberOfArguments, subjectNumber, mark);
                                                break;
                                            default:
                                                printf("Wrong number! Try again\n");
                                        }
                                        break;
                                    default:
                                        printf("Wrong number! Try again\n");
                                }
                            }
                            break;

                        default:
                            printf("Wrong number! Try again\n");
                    }

                }
                break;
            case 2:     //Edit the archive file
                while(1){
                    printf("1) List students with an average > ... : \n");
                    printf("2) Transfer a student to the current school: \n");
                    printf("0) Exit\n\n");
                    printf("Enter a number: ");
                    scanf("%d", &choice);
                    if(choice == 0) break;

                    switch(choice){
                        case 1:     //List students with an average higher than ...
                            //Lister()
                            break;

                        case 2:;     //Transfer a student
                            char firstName[MAX_FIRST_NAME_SIZE +1];
                            char lastName[MAX_LAST_NAME_SIZE +1];
                            printf("Reading student's infos...\n");
                            printf("Enter student's class");
                            scanf("%d", &student.class);
                            printf("Enter student's ID");
                            scanf("%d", &student.id);
                            printf("Enter student's firstname (lower case only)");
                            scanf("%s", firstName); //then calculate length and assign it
                            printf("Enter student's class");
                            scanf("%s", lastName); //then calculate length and assign it
                            strcpy(student.fullName, lastName);
                            strcat(student.fullName, firstName);

                            int numberOfYears;
                            printf("Enter the number of years already studied: ");
                            scanf("%d", &numberOfYears);
                            if(numberOfYears > numberOfArchives) numberOfYears = numberOfArchives;

                            int archiveYear = currentYear -1;
                            float average;
                            char archiveYearString[5];
                            for(int i=0; i<numberOfYears; i++){ //Check if loop should be integrated inside the insert function
                                intToString(archiveYearString, archiveYear, 4);
                                printf("Enter the average (moyenne) of the student in the year %d : ", archiveYear);
                                scanf("%f", &average);
                                //Insert
                            }

                            break;
                        default:
                            printf("Wrong number! Try again\n");
                    }
                }
                break;
            case 3:     //Print infos
                break;
        }
    }

    printf("Thank you for using the application\n");
    return 0;
}

//    //Custom student for test
//    Student student;
//    student.id = 1111;
//    student.class = 111;
//    strcpy(student.firstName ,"Houari");
//    printf("firstname: %s\n", student.firstName);
//    strcpy(student.lastName, "Mohammed");
//    student.gender = 'M';
//    student.isDeleted = '0';
//    student.marks[0] = 10.00;
//    student.marks[1] = 7.5;
//    student.marks[2] = 9.25;
//    student.marks[3] = 5.5;
//    student.marks[4] = 8.0;
//    writeStudent(fichier, &student,  &buffer, &i,&j);
//
//    student.id = 2222;
//    student.class = 222; //level is 4, number of subjects is 7
//    strcpy(student.firstName ,"Sediki");
//    printf("firstname: %s\n", student.firstName);
//    strcpy(student.lastName, "Raouf");
//    student.gender = 'M';
//    student.isDeleted = '0';
//    student.marks[0] = 11.11;
//    student.marks[1] = 22.22;
//    student.marks[2] = 33.33;
//    student.marks[3] = 44.44;
//    student.marks[4] = 55.55;
//    student.marks[5] = 66.66;
//    student.marks[6] = 77.77;
//    writeStudent(fichier, &student,  &buffer, &i,&j);
//

////    createSchoolYear(fichier, &buffer, &i, &j);
//    j = 0;
//    i = 0;
////    lirechaine(fichier, &buffer, testString,  buffer.positionLibre, &i, &j); //
//    lireBlocTof(fichier, i, &buffer);
//    buffer.positionLibre = 99;
//    lirechaine2(fichier, &buffer, testString,  buffer.positionLibre, &i, &j);
//    //after the end of each string there is '\0' so we have to eliminate it
//    printf("%s", testString);
//    fermerFichierTof(fichier);

//    //Custom student for test
//    student.id = 3333;
//    student.class = 333;
//    strcpy(student.firstName ,"Houari");
//    printf("firstname: %s\n", student.firstName);
//    strcpy(student.lastName, "Mohammed");
//    student.gender = 'M';
//    student.isDeleted = '0';
//    student.marks[0] = 10.00;
//    student.marks[1] = 7.5;
//    student.marks[2] = 9.25;
//    student.marks[3] = 5.5;
//    student.marks[4] = 8.0;
//    writeStudent(fichier, &student,  &buffer, &i,&j);
//
//    student.id = 4444;
//    student.class = 444; //level is 4, number of subjects is 7
//    strcpy(student.firstName ,"Sediki");
//    printf("firstname: %s\n", student.firstName);
//    strcpy(student.lastName, "Raouf");
//    student.gender = 'M';
//    student.isDeleted = '0';
//    student.marks[0] = 11.11;
//    student.marks[1] = 22.22;
//    student.marks[2] = 33.33;
//    student.marks[3] = 44.44;
//    student.marks[4] = 55.55;
//    student.marks[5] = 66.66;
//    student.marks[6] = 77.77;
//    writeStudent(fichier, &student,  &buffer, &i,&j);

//    ClassIdArray classIdArray;
//    classIdArray.nb = 0;
//    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {
//        generateClassId(&classIdArray);
//    }
//    printf("array.nb: %d\n", classIdArray.nb);
//
//    for (int k = 0; k < FIRST_LOAD_OF_CLASSES; ++k) {
//        printf("class: %d, array.nb: %d\n", classIdArray.tab[k] ,classIdArray.nb);
//    }

//    int id = 0;
//    bool found;
//    ClassIdArray classIdArray;
//    classIdArray.nb = 6;
//    classIdArray.tab[0]=223  ;
//    classIdArray.tab[1]= 400 ;
//    classIdArray.tab[2]= 305 ;
//    classIdArray.tab[3]= 416 ;
//    classIdArray.tab[4]=  520;
//    classIdArray.tab[5]=  310;
//    checkRoomNumber(&classIdArray, 0, &found);
//    printf("found: %d\n", found);

//Custom student for test
//    Student student;
//    student.id = 1;
//    student.class = 115;
//    strcpy(student.firstName ,"Houari");
//    printf("firstname: %s\n", student.firstName);
//    strcpy(student.lastName, "Mohammed");
//    student.gender = 'M';
//    student.isDeleted = '0';
//    student.marks[0] = 10.00;
//    student.marks[1] = 7.5;
//    student.marks[2] = 9.25;
//    student.marks[3] = 5.5;
//    student.marks[4] = 8.0;

//    writeStudent(fichier, &student,  &buffer, &i,&j);
//    printf("i after writing: %d\nj after writing: %d\n", i, j);
//string buffers:
//     firstName = (char*)malloc(sizeof(char)*MAX_FIRST_NAME_SIZE);
//     lastName = (char*)malloc(sizeof(char)*MAX_LAST_NAME_SIZE);
//     gender = (char*)malloc(sizeof(char)*2);


//    //Generation of random IDs for 3 students
//    int seed = 0;
//    int id;
//    for (int i = 0; i < 3; ++i) {
//        id = generateStudentID(seed);
//        printf("ID[%d]: %d\n", i, id);
//        seed = id; //we will use the previous ID value as a seed
//    }

//
//    getFirstName(&firstName, 4);
//    getlastNameAndGender(&lastName, &gender, 3);
//    printf("\nhello world\n");
//
//    getMarks(tableOfMarks, 3);
//
//    studentsIdArray.nb = 0;
//    studentsIdArray.nb = 0;

//    for (int i = 0; i < 30; ++i) {
//        generateClassId(&roomIdArray);
//    }
//
//    for (int i = 0; i < 30; ++i) {
//        printf("%d\n", roomIdArray.tab[i]);
//    }//
//createSchoolYear();
//char buffer[30] = "Hello";
//    printf("%lu", strlen(buffer));
//
//    int i1 = 247;
//    char str[4];
//    sprintf(str, "%d", i1);
//    printf("\n%s %d", str, strlen(str));


//    int i1 = 247593;
//    char str[10];
//    sprintf(str, "%d", i1);
//    printf("\n%s", str);
//
//
//    char str1[10] = "213";
//    sscanf(str1, "%d", &i1);
//    printf("\n%d", i1);

//    char str[50];
//    lirechaine(fichier, &bufferTovc, str, 2, &i, &j);
//    lirechaine(fichier, &bufferTovc, str, 2, &i, &j);
//    lirechaine(fichier, &bufferTovc, str, 3, &i, &j); str[3] = '\0';
//    printf("this is the class id: %s\n", str);
//    lirechaine(fichier, &bufferTovc, str, 4, &i, &j); str[4] = '\0';
//    printf("this is the student id: %s\n", str);
//    skip(fichier, 1+4*4, &i, &j);
//    lirechaine(fichier, &bufferTovc, str, 5, &i, &j); str[5] = '\0';
//    printf("this is the first name: %s\n", str);
//    lirechaine(fichier, &bufferTovc, str, 6, &i, &j); str[6] = '\0';
//    printf("this is the last name: %s\n", str);