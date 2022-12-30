#ifndef TP1_SFSD_STUDENT_LIBRARY_H
#define TP1_SFSD_STUDENT_LIBRARY_H

#include "DataManipulation.h"
#include "TofIndexFunctions.h"
#include <math.h>
#include <stdarg.h>

//Global Variables
extern position classesIndex[FIRST_LOAD_OF_CLASSES];



//functions:

void
searchClassIndex(FichierTof *indexFile, int *i, int *j, int id, int *indexI, int *indexJ, bool *found, bool *isDeleted);

void
searchStudent(FichierTovc *fichier, FichierTof *indexFile, Student student, int *i, int *j, int *indexI, int *indexJ,
              bool *found);

void skip(FichierTovc *fichier, int steps, int *i, int *j);

void updateStudentInfo(FichierTovc *fichierTovc, Student student, int numberOfArguments, ...);

void deleteStudent(FichierTovc *fichier, Student student);

void insertStudent(FichierTovc *fichier, FichierTof *indexFile, Student student);

#endif //TP1_SFSD_STUDENT_LIBRARY_H
