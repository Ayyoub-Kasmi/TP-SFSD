#include "settings.h"
#include <stdlib.h>

void loadSubjects(){
    FILE *subjectsFile;
    subjectsFile = fopen(SUBJECTS_FILE_PATH, "r");

    char subjectName[MAX_SUBJECT_NAME_LENGTH];
    int i=0, count =0;
    Subject subject;
    SubjectsArray subjectsArray;

    while(!feof(subjectsFile)){
        fscanf(subjectsFile, "%[^\n]\n", subjectName);
        printf("Here is the string: %s\n", subjectName);
        if(strcmp(subjectName, "#") != 0){
            //add subject to array
            strcpy(subject.name, subjectName);
            subject.subjectNumber = count+1;
            subjectsArray.tab[i][count] = subject;
            count++;
        } else {
            //count the number of subjects
            numberOfSubjectsPerLevel[i] = count;
            count = 0;
            i++;
        }
    }
    subjectsArray.totalLevels = i+1;
}

void loadGlobalVariables(){
    FILE* globalVariablesFile = fopen(GLOBAL_VARIABLES_FILE_PATH,"r");

    if(globalVariablesFile == NULL){
        printf("globalVariables.txt is missing\n");
        return;
    }
    char stringBufffer[100];

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &STUDENT_ID_SIZE);

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &CLASS_ID_SIZE);

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &FIRST_LOAD_OF_CLASSES);

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &FIRST_LOAD_OF_STUDENTS);

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &MAX_STUDENT_PER_CLASS);

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &MAX_STUDENTS_PER_YEAR);

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &MAX_FIRST_NAME_LENGTH);

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &MAX_LAST_NAME_LENGTH);

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &MAX_NUMBER_OF_SUBJECTS);

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &MARK_LENGTH);

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &MARK_WHOLE_PART_LENGTH);

    fscanf(globalVariablesFile, "%[^\n]\n", stringBufffer);
    fscanf(globalVariablesFile, "%d\n", &MARK_DECIMAL_PART_LENGTH);
}

void loadSettings(){
    //load subjects
    //load global variables (check DataManipulation.h to see all necessary global variables)
}