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

//

void loadSettings(){
    //load subjects
    //load global variables (check DataManipulation.h to see all necessary global variables)
}