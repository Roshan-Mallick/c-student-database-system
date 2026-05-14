#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "database.h"

/* Database folder and main database file */
extern const char *DB_DIR;
extern const char *MASTER_DB;

/* Initialize database folder and record count */
void initDatabase();

/* Save one student record */
void saveStudent(const Student *s);

/* Load all students from database */
Student** loadAllStudents(int *count);

/* Rewrite database with updated records */
void rewriteDatabase(Student **arr, int count);

/* Filter students by batch */
void filterByBatch(const char *batch);

/* Filter students by marks */
void filterByMarks(float cutoff);

#endif /* FILE_HANDLER_H */
