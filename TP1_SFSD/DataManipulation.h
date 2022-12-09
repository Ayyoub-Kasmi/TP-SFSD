#ifndef TP1_SFSD_DATAMANIPULATION_H
#define TP1_SFSD_DATAMANIPULATION_H

#include <stdbool.h>
#include "tovcFunctions.h"

//definition of system constants
#define FIRST_NAMES_FILE_PATH "firstNames.txt" //this is the alternative for the moment
#define LAST_NAMES_AND_GENDER_FILE_PATH "lastNamesAndGender.txt"
#define CURRENT_YEAR_FILE_PATH  "2022_STUDENTS"
#define STUDENT_ID_SIZE 4
#define CLASS_ID_SIZE 3
#define CLASS_NUMBER_SIZE 2
#define SCHOOL_LEVEL_SIZE 1
#define IS_DELETED_SIZE 1
#define SCHOOL_LEVEL_SIZE 1
#define LASTNAME_LENGTH 2  // MAY CHANGE
#define FIRSTNAME_LENGTH 2
#define GENDER_SIZE 1
#define EFF_SIZE 1
#define STUDENT_PER_CLASS 4
#define NUMBER_OF_LEVELS 6
#define FIRST_LOAD_OF_STUDENTS 120
#define FIRST_LOAD_OF_CLASSES 30
#define FIRST_NAME_FILE_SIZE 614
#define MAX_FIRST_NAME_SIZE 30
#define MAX_LAST_NAME_SIZE 30
#define MAX_NUMBER_OF_SUBJECTS 7
#define CURRENT_YEAR 2022
#define MARK_WHOLE_PART_LENGTH 2
#define DECIMAL_WHOLE_PART_LENGTH 2


typedef struct {
    int i;
    int j;
} position;

typedef struct {
    int tab[FIRST_LOAD_OF_STUDENTS];
    int nb; //number of elements within the array
} StudentsIdArray;

typedef struct {
    int tab[FIRST_LOAD_OF_CLASSES];
    int nb; //number of elements within the array
} ClassIdArray;

typedef struct {
    char tab[FIRST_LOAD_OF_CLASSES][MAX_LAST_NAME_SIZE + MAX_FIRST_NAME_SIZE + GENDER_SIZE];
    //a 2D array to sort the names alphabetically before inserting them
    int nb; //number of elements within the lines
} StudentsNamesArray;

typedef struct {
    int id;
    int class;
    char firstName[MAX_FIRST_NAME_SIZE];
    char lastName[MAX_LAST_NAME_SIZE];
    char gender;
    char isDeleted;
    float marks[MAX_NUMBER_OF_SUBJECTS];
} Student;

typedef struct {
    char firstName[MAX_FIRST_NAME_SIZE];
    char lastName[MAX_LAST_NAME_SIZE];
    char gender;
    int firstNameSize;
    int lastNameSize;
} NameProperties;

//Global variables:
extern const int numberOfSubjectsPerLevel[6];
extern Buffer buffer;
extern position classesIndex[NUMBER_OF_LEVELS];

//functions of part 1
// a-
int generateStudentID(int seed);
// c-
void getFirstName(char *firstName, int number);
void getlastNameAndGender(char *lastName, char *gender, int number);
// d-
void getMarks(float *tableOfMarks, int level);

int generate4positionInt(int seed);

void generateStudentId(StudentsIdArray *studentsIdArray);

void searchStudentId(StudentsIdArray *studentsIdArray, int id, int *i, bool *found);

void insertStudentId(StudentsIdArray *studentsIdArray, int id);

void insertStudentIdWithoutSearching(StudentsIdArray *studentsIdArray, int id, int i);

int generate2positionInt(int seed);

int generateTheLevel(int seed);

void generateClassId(ClassIdArray *classIdArray);

void checkRoomNumber(ClassIdArray *roomIdArray, int roomNumber, bool *found);

void checkClassID(ClassIdArray *classIdArray, int classID, bool *found);

void searchClassId(ClassIdArray *roomIdArray, int id, int *i, bool *found);

void insertClassId(ClassIdArray *roomIdArray, int id);

void insertRoomIdWithoutSearching(ClassIdArray *roomIdArray, int id, int i);

void createSchoolYear(Fichier *fichier, Buffer *buffer, int* i, int* j);

void writeStudent(Fichier *fichier, Student *student, Buffer *buffer, int *i, int *j);

void generateStudentName(StudentsNamesArray *studentsNamesArray);

void searchStudentName(StudentsNamesArray *studentsNamesArray, char *fullName, int* i, bool *found);

void insertStudentName(StudentsNamesArray *studentsNamesArray, char* fullName);

void insertStudentNameWithoutSearching(StudentsNamesArray *studentsNamesArray, char *fullName, int firstNameSize,
                                       int lastNameSize, int i);

#endif //TP1_SFSD_DATAMANIPULATION_H
