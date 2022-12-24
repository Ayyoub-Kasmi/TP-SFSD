#ifndef TP1_SFSD_SETTINGS_H
#define TP1_SFSD_SETTINGS_H

#include <stdio.h>
#include <string.h>

#define SUBJECTS_FILE_PATH "subjects.txt"
#define MAX_SUBJECTS 10
#define MAX_LEVELS 6
#define MAX_SUBJECT_NAME_LENGTH 30

typedef struct {
    char name[MAX_SUBJECT_NAME_LENGTH];
    int subjectNumber;
}Subject;

typedef struct {
    Subject tab[MAX_LEVELS][MAX_SUBJECTS];
    int totalLevels;
}SubjectsArray;

extern int numberOfSubjectsPerLevel[6];

void loadSubjects();

#endif //TP1_SFSD_SETTINGS_H
