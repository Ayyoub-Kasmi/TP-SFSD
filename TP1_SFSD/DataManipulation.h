#ifndef TP1_SFSD_DATAMANIPULATION_H
#define TP1_SFSD_DATAMANIPULATION_H

#include <stdbool.h>
#include "tovcFunctions.h"
//definition of system constants
#define BUFFER_SIZE 250
#define STUDENT_ID_SIZE 4
#define CLASS_ID_SIZE 3
#define CLASS_NUMBER_SIZE 2
#define SCHOOL_LEVEL_SIZE 1
#define GENDER_SIZE 1
#define EFF_SIZE 1
#define LASTNAME_LENGTH_SIZE 2  // MAY CHANGE
#define FIRSTNAME_LENGTH_SIZE 2
#define STUDENT_PER_CLASS 4
#define FIRST_LOAD_OF_STUDENTS 120
#define FIRST_LOAD_OF_CLASSES 30
#define LAST_NAMES_FILE_PATH "LastNames.txt" //this is the alternative for the moment
#define FIRST_NAMES_AND_GENDER_FILE_PATH "FirstNamesAndGenders.txt"
#define FIRST_NAME_FILE_SIZE 614
#define MAX_FIRST_NAME_SIZE 30
#define MAX_LAST_NAME_SIZE 30
#define MAX_NUMBER_OF_SUBJECTS 7
#define CURRENT_YEAR 2022
#define MARK_WHOLE_PART_LENGTH 2
#define DECIMAL_WHOLE_PART_LENGTH 2

typedef struct {
    int id;//the id
    int i;//number of the bloc
    int j; //position in the bloc
} StudentsIdIndexElement;

typedef struct {
    int id;//the id
    int i;//number of the bloc
    int j; //position in the bloc
} ClassIdIndexElement;

typedef struct {
    StudentsIdIndexElement tab[FIRST_LOAD_OF_STUDENTS];
    int nb; //number of elements within the array
} StudentsIdArray;

typedef struct {
    ClassIdIndexElement tab[FIRST_LOAD_OF_CLASSES];
    int nb; //number of elements within the array
} ClassIdArray;

typedef struct {
    char fullName[MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE + GENDER_SIZE];
    int firstNameSize;
    int lastNameSize;
    char gender
} NameProperties;

typedef struct {
    NameProperties tab[FIRST_LOAD_OF_CLASSES];
    //an array to sort the names alphabetically before inserting them
    int nb; //number of elements within the lines
} StudentsNamesArray;

typedef struct {
    int id;
    int class;
    char fullName[MAX_FIRST_NAME_SIZE + MAX_LAST_NAME_SIZE + GENDER_SIZE];
    int firstNameSize;
    int lastNameSize;
    char gender;
    char isDeleted;
    float marks[MAX_NUMBER_OF_SUBJECTS];
} Student;

//Global variables:
extern const int numberOfSubjectsPerLevel[6];
extern Buffer buffer;


//functions of part 1
// a-
int generateStudentID(int seed);
// c-
void getLastName(char *lastName, int number);

void getFirstNameAndGender(char *firstName, char *gender, int number);
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

void checkRoomNumber(ClassIdArray *ClassIdArray, int roomNumber, bool *found);

void checkClassID(ClassIdArray *classIdArray, int classID, bool *found);

void searchClassId(ClassIdArray *roomIdArray, int id, int *i, bool *found);

void insertClassId(ClassIdArray *roomIdArray, int id);

void insertRoomIdWithoutSearching(ClassIdArray *roomIdArray, int id, int i);

void createSchoolYear(FichierTof *fichier, Buffer *buffer, int* i, int* j);

void writeStudent(FichierTof *fichier, Student *student, Buffer *buffer, int *i, int *j);

void generateStudentName(StudentsNamesArray *studentsNamesArray);

void searchStudentName(StudentsNamesArray *studentsNamesArray, char *fullName, int* i, bool *found);

void insertStudentName(StudentsNamesArray *studentsNamesArray, char *fullName, char gender,int firstNameSize,
                       int lastNameSize);

void insertStudentNameWithoutSearching(StudentsNamesArray *studentsNamesArray, char *fullName, char gender, int firstNameSize,
                                       int lastNameSize, int i);
#endif //TP1_SFSD_DATAMANIPULATION_H
