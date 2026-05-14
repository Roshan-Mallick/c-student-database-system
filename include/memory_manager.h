#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

#include "database.h"

/* Memory allocation functions */

/* Allocate memory for one Student */
Student* allocStudent();

/* Create an array of Student pointers */
Student** allocStudentArray(int capacity);

/* Increase size of Student pointer array */
Student** growStudentArray(Student **arr, int newCap);

/* Free all students and the array */
void freeStudentArray(Student **arr, int count);

#endif /* MEMORY_MANAGER_H */
