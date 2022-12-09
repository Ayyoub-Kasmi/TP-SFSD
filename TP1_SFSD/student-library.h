#ifndef TP1_SFSD_STUDENT_LIBRARY_H
#define TP1_SFSD_STUDENT_LIBRARY_H

#include "DataManipulation.h"
#include <math.h>
#include <stdarg.h>

//Global Variables
extern position classesIndex[NUMBER_OF_LEVELS];



//functions:
void searchStudent(Fichier* fichier, Student student, int* i, int* j, bool* found);
#endif //TP1_SFSD_STUDENT_LIBRARY_H
