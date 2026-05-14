#include <stdio.h>
#include <stdlib.h>
#include "../include/memory_manager.h"

/* Allocate memory for one Student */
Student* allocStudent() {
    Student *s = (Student *)malloc(sizeof(Student));

    /* Stop program if memory allocation fails */
    if (!s) {
        fprintf(stderr, "[ERROR] allocStudent: malloc failed.\n");
        exit(EXIT_FAILURE);
    }

    return s;
}

/* Create an array of Student pointers */
Student** allocStudentArray(int capacity) {
    Student **arr = (Student **)calloc(capacity, sizeof(Student *));

    /* Check if memory allocation failed */
    if (!arr) {
        fprintf(stderr, "[ERROR] allocStudentArray: calloc failed.\n");
        exit(EXIT_FAILURE);
    }

    return arr;
}

/* Increase size of Student pointer array */
Student** growStudentArray(Student **arr, int newCap) {
    Student **bigger =
        (Student **)realloc(arr, newCap * sizeof(Student *));

    /* Check if realloc failed */
    if (!bigger) {
        fprintf(stderr, "[ERROR] growStudentArray: realloc failed.\n");
        exit(EXIT_FAILURE);
    }

    return bigger;
}

/* Free all students and the array itself */
void freeStudentArray(Student **arr, int count) {

    /* Free each Student */
    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }

    /* Free the main array */
    free(arr);
}
