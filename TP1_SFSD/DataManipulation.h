#ifndef TP1_SFSD_DATAMANIPULATION_H
#define TP1_SFSD_DATAMANIPULATION_H

#include <stdbool.h>
//definition of system constants
#define BUFFER_SIZE 250
#define STUDENT_ID_SIZE 4
#define CLASS_ID_SIZE 3
#define CLASS_NUMBER_SIZE 2
#define SCHOOL_LEVEL_SIZE 1
#define GENDER_SIZE 1
#define EFF_SIZE 1
#define LENGTH_SIZE 4  // MAY CHANGE
#define STUENDT_PER_CLASS 4
#define FIRST_LOAD_OF_STUDENTS 120
#define FIRST_LOAD_OF_CLASSES 30
#define FIRST_NAMES_FILE_PATH "firstNames.txt" //this is the alternative for the moment
#define LAST_NAMES_AND_GENDER_FILE_PATH "lastNamesAndGender.txt"
#define MAX_FIRST_NAME_SIZE 30
#define MAX_LAST_NAME_SIZE 30
#define MAX_NUMBER_OF_SUBJECTS 7
#define CURRENT_YEAR 2022

extern const int numberOfSubjectsPerLevel[6];

typedef struct {
    int tab[FIRST_LOAD_OF_STUDENTS];
    int nb; //number of elements within the array
} StudentsIdArray;

typedef struct {
    int tab[FIRST_LOAD_OF_CLASSES];
    int nb; //number of elements within the array
} ClassIdArray;

typedef struct {
    int id;
    int class;
    char *firstName;
    char *lastName;
    char gender;
    float marks[MAX_NUMBER_OF_SUBJECTS];
} Student;
//functions of part 1
// a-
int generateStudentID(int seed);
// c-
void getFirstName(char **firstName, int number);
void getlastNameAndGender(char **lastName, char *gender, int number);
// d-
void getMarks(float *tableOfMarks, int level);

int generate4positionInt(int seed);

void generateStudentId(StudentsIdArray *studentsIdArray);

void searchStudentId(StudentsIdArray *studentsIdArray, int id, int *i, bool *found);

void insertStudentId(StudentsIdArray *studentsIdArray, int id);

void insertStudentIdWithoutSearching(StudentsIdArray *studentsIdArray, int id, int i);

int generate2positionInt(int seed);

int generateTheLevel(int seed);

void generateClassId(ClassIdArray *roomIdArray);

void searchRoomNumber(ClassIdArray *roomIdArray, int roomNumber, bool *found);

void searchClassId(ClassIdArray *roomIdArray, int id, int *i, bool *found);

void insertRoomId(ClassIdArray *roomIdArray, int id);

void insertRoomIdWithoutSearching(ClassIdArray *roomIdArray, int id, int i);

void createSchoolYear();

#endif //TP1_SFSD_DATAMANIPULATION_H
