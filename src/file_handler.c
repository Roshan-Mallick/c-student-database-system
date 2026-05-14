#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "../include/file_handler.h"
#include "../include/memory_manager.h"
#include "../include/utils.h"

/* Database folder and main database file */
const char *DB_DIR    = "database";
const char *MASTER_DB = "database/students.db";

/* Total number of student records */
int global_record_count = 0;

/* Create database folder and load record count */
void initDatabase() {

    struct stat st = {0};

    /* Create folder if it does not exist */
    if (stat(DB_DIR, &st) == -1) {
        mkdir(DB_DIR, 0755);
        printf("[+] Created folder: %s/\n", DB_DIR);
    } else {
        printf("[✓] Database folder ready: %s/\n", DB_DIR);
    }

    /* Count existing student records */
    FILE *fp = fopen(MASTER_DB, "rb");

    if (fp) {
        Student temp;

        while (fread(&temp, sizeof(Student), 1, fp) == 1) {
            global_record_count++;
        }

        fclose(fp);

        printf("[✓] %d existing record(s) loaded.\n",
               global_record_count);

    } else {
        printf("[i] No existing records. Fresh database.\n");
    }
}

/* Save one student record */
void saveStudent(const Student *s) {

    FILE *fp = fopen(MASTER_DB, "ab");

    if (!fp) {
        fprintf(stderr,
                "[ERROR] saveStudent: cannot open %s\n",
                MASTER_DB);
        return;
    }

    fwrite(s, sizeof(Student), 1, fp);

    fclose(fp);

    global_record_count++;
}

/* Load all students from database */
Student** loadAllStudents(int *count) {

    *count = 0;

    FILE *fp = fopen(MASTER_DB, "rb");

    if (!fp) {
        return NULL;
    }

    int capacity = 4;

    Student **arr = allocStudentArray(capacity);

    Student temp;

    while (fread(&temp, sizeof(Student), 1, fp) == 1) {

        /* Increase array size if full */
        if (*count >= capacity) {
            capacity *= 2;
            arr = growStudentArray(arr, capacity);
        }

        /* Allocate memory for one student */
        arr[*count] = allocStudent();

        /* Copy student data */
        *(arr[*count]) = temp;

        (*count)++;
    }

    fclose(fp);

    return arr;
}

/* Rewrite full database file */
void rewriteDatabase(Student **arr, int count) {

    FILE *fp = fopen(MASTER_DB, "wb");

    if (!fp) {
        fprintf(stderr,
                "[ERROR] rewriteDatabase: cannot open %s\n",
                MASTER_DB);
        return;
    }

    for (int i = 0; i < count; i++) {
        fwrite(arr[i], sizeof(Student), 1, fp);
    }

    fclose(fp);

    global_record_count = count;
}

/* Save students of one batch into a separate file */
void filterByBatch(const char *batch) {

    int count = 0;

    Student **arr = loadAllStudents(&count);

    if (!arr || count == 0) {
        printf("[i] No records to filter.\n");
        return;
    }

    /* Create output file path */
    char filepath[100];

    snprintf(filepath,
             sizeof(filepath),
             "%s/batch_%s.db",
             DB_DIR,
             batch);

    FILE *fp = fopen(filepath, "wb");

    if (!fp) {
        fprintf(stderr,
                "[ERROR] filterByBatch: cannot create %s\n",
                filepath);

        freeStudentArray(arr, count);

        return;
    }

    int saved = 0;

    for (int i = 0; i < count; i++) {

        /* Match batch name */
        if (strcmp(arr[i]->batch, batch) == 0) {

            fwrite(arr[i], sizeof(Student), 1, fp);

            saved++;
        }
    }

    fclose(fp);

    freeStudentArray(arr, count);

    printf("[✓] Filter complete: %d student(s) from batch '%s'\n",
           saved,
           batch);

    printf("    Saved to → %s\n", filepath);
}

/* Split students by marks cutoff */
void filterByMarks(float cutoff) {

    int count = 0;

    Student **arr = loadAllStudents(&count);

    if (!arr || count == 0) {
        printf("[i] No records to filter.\n");
        return;
    }

    char high_path[100], low_path[100];

    snprintf(high_path,
             sizeof(high_path),
             "%s/high_marks.db",
             DB_DIR);

    snprintf(low_path,
             sizeof(low_path),
             "%s/low_marks.db",
             DB_DIR);

    FILE *fhigh = fopen(high_path, "wb");
    FILE *flow  = fopen(low_path,  "wb");

    /* Check file creation */
    if (!fhigh || !flow) {

        fprintf(stderr,
                "[ERROR] filterByMarks: cannot create filter files.\n");

        freeStudentArray(arr, count);

        return;
    }

    int high = 0, low = 0;

    for (int i = 0; i < count; i++) {

        if (arr[i]->marks >= cutoff) {

            fwrite(arr[i], sizeof(Student), 1, fhigh);

            high++;

        } else {

            fwrite(arr[i], sizeof(Student), 1, flow);

            low++;
        }
    }

    fclose(fhigh);
    fclose(flow);

    freeStudentArray(arr, count);

    printf("[✓] Filter complete (cutoff: %.2f)\n", cutoff);

    printf("    High marks (>= %.2f): %d student(s) → %s\n",
           cutoff,
           high,
           high_path);

    printf("    Low marks (< %.2f): %d student(s) → %s\n",
           cutoff,
           low,
           low_path);
}
