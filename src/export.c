#include <stdio.h>

#include "../include/export.h"
#include "../include/file_handler.h"
#include "../include/memory_manager.h"

void exportAllStudentsToCSV() {

    int count = 0;

    Student **arr = loadAllStudents(&count);

    if (!arr || count == 0) {

        printf("\n[!] No student records found.\n");
        return;
    }

    FILE *fp;

    fp = fopen("exported/students.csv", "w");

    if (fp == NULL) {

        printf("\n[!] CSV file could not be created.\n");

        freeStudentArray(arr, count);

        return;
    }

    /* CSV Header */
    fprintf(fp, "ID,Name,Age,Marks,Contact,Email,Batch\n");

    /* Write all students */
    for (int i = 0; i < count; i++) {

        fprintf(fp,
            "%lld,%s,%d,%.2f,%s,%s,%s\n",

            arr[i]->id,
            arr[i]->name,
            arr[i]->age,
            arr[i]->marks,
            arr[i]->contact,
            arr[i]->email,
            arr[i]->batch
        );
    }

    fclose(fp);

    freeStudentArray(arr, count);

    printf("\n[✓] Students exported successfully.\n");
}
