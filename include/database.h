#ifndef DATABASE_H
#define DATABASE_H

/* Student structure */
typedef struct {
    long long id;
    char name[50];
    int age;
    float marks;
    char contact[15];
    char email[100];
    char batch[20];
} Student;

/* Student database functions */
void addStudent();
void viewAllStudents();
void searchStudentById(long long id);
void deleteStudentById(long long id);
void updateStudentById(long long id);
void sortStudentsById();

/* Student filter functions */
void filterByBatch(const char *batch);
void filterByMarks(float cutoff);

#endif
