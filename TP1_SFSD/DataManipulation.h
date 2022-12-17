#ifndef TP1_SFSD_DATAMANIPULATION_H
#define TP1_SFSD_DATAMANIPULATION_H

#include <stdbool.h>
#include "tovcFunctions.h"

//definition of system constants
#define CURRENT_YEAR_FILE_PATH  "2022_STUDENTS"
#define STUDENT_ID_SIZE 4
#define CLASS_ID_SIZE 3
#define ROOM_SIZE 2
#define CLASS_NUMBER_SIZE 2
#define SCHOOL_LEVEL_SIZE 1
#define IS_DELETED_SIZE 1
#define LASTNAME_LENGTH 2  // MAY CHANGE
#define FIRSTNAME_LENGTH 2
#define GENDER_SIZE 1
#define STUDENT_PER_CLASS 4
#define NUMBER_OF_LEVELS 6
#define FIRST_LOAD_OF_STUDENTS 120
#define FIRST_LOAD_OF_CLASSES 30
#define LAST_NAMES_FILE_PATH "LastNames.txt" //this is the alternative for the moment
#define FIRST_NAMES_AND_GENDER_FILE_PATH "FirstNamesAndGenders.txt"
#define FIRST_NAME_FILE_SIZE 614
#define MAX_FIRST_NAME_SIZE 30
#define MAX_LAST_NAME_SIZE 30
#define MAX_NUMBER_OF_SUBJECTS 7
#define CURRENT_YEAR 2022
#define MARK_LENGTH 4
#define MARK_WHOLE_PART_LENGTH 2
#define MARK_DECIMAL_PART_LENGTH 2


typedef struct {
    int i;
    int j;
} position;

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
    char gender;
} NameProperties;

typedef struct {
    NameProperties tab[FIRST_LOAD_OF_STUDENTS];
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
extern BufferTovc bufferTovc;
extern position classesIndex[NUMBER_OF_LEVELS];
extern int tempStudentID;
extern int tempStudentClass;

//functions of part 1
// a-
int generateStudentID(int seed);
int stringToInt(char* string, int length);
void intToString(char *string, int number, int length);
// c-
void getLastName(FILE* lastNamesFile, char *lastName, int *seed);

void getFirstNameAndGender(FILE *firstNamesAndGendersFile, char *firstName, char *gender, int *seed);
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

void createSchoolYear(FichierTovc *fichier, int *i, int *j);

void writeStudent(FichierTovc *fichier, Student *student, int *i, int *j);

void generateStudentName(FILE* lastNamesFile, FILE* firstNamesAndGendersFile, StudentsNamesArray *studentsNamesArray);

void searchStudentName(StudentsNamesArray *studentsNamesArray, char *fullName, int* i, bool *found);

void insertStudentName(StudentsNamesArray *studentsNamesArray, char *fullName, char gender,int firstNameSize,
                       int lastNameSize);

void insertStudentNameWithoutSearching(StudentsNamesArray *studentsNamesArray, char *fullName, char gender, int firstNameSize,
                                       int lastNameSize, int i);

#endif //TP1_SFSD_DATAMANIPULATION_H
