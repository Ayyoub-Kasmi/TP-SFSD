#ifndef TP1_SFSD_FILEMANIPULATIONFUNCTIONS_H
#define TP1_SFSD_FILEMANIPULATIONFUNCTIONS_H

//const char firstNamesFilePath[] = "./firstNames.txt";   <======= it doesn't work (says Error: multiple definition
                                                        /* of firstNamesFilePath) but I don't know why*/

//definition of system constants
#define firstNamesFilePath "firstNames.txt" //this is the alternative for the moment
#define lastNamesAndGenderFilePath "lastNamesAndGender.txt"
#define MaxFirstNameSize 30
#define MaxLastNameSize 30
#define MaxNumberOfSubjects 7
extern const int numberOfSubjectsPerLevel[6];

//functions of part 1
// a-
int generateStudentID(int seed);
// c-
void getFirstName(char **firstName, int number);
void getlastNameAndGender(char **lastName, char **gender, int number);
// d-
void getMarks(float *tableOfMarks, int level);



#endif //TP1_SFSD_FILEMANIPULATIONFUNCTIONS_H
