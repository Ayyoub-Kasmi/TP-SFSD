#ifndef TP1_SFSD_STUDENT_LIBRARY_H
#define TP1_SFSD_STUDENT_LIBRARY_H

#include "DataManipulation.h"
#include <math.h>
#include <stdarg.h>

//Global Variables
extern position classesIndex[NUMBER_OF_LEVELS];



//functions:
void searchStudent(FichierTovc* fichier, Student student, int* i, int* j, bool* found);
void updateStudentInfo(FichierTovc* fichier, int numberOfArguments, ...);
#endif //TP1_SFSD_STUDENT_LIBRARY_H
