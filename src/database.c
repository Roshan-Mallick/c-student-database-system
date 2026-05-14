#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/database.h"
#include "../include/file_handler.h"
#include "../include/memory_manager.h"
#include "../include/utils.h"
#include "../include/export.h"

/* Add a new student */
void addStudent() {

    Student s;

    printDivider();
    printf("ADD NEW STUDENT\n");
    printDivider();

    printf("Enter ID: ");
    scanf("%lld", &s.id);
    getchar();

    int count = 0;

    Student **arr = loadAllStudents(&count);

    for (int i = 0; i < count; i++) {

        if (arr[i]->id == s.id) {

            printf("\n[!] Student ID already exists.\n");

            freeStudentArray(arr, count);

            return;
        }
    }

    freeStudentArray(arr, count);

    printf("Enter Name: ");
    fgets(s.name, sizeof(s.name), stdin);
    stripNewline(s.name);

    printf("Enter Age: ");

    if (scanf("%d", &s.age) != 1) {

        printf("\n[!] Invalid age input.\n");

        while (getchar() != '\n');

        return;
    }

    getchar();

    printf("Enter Marks: ");

    if (scanf("%f", &s.marks) != 1) {

        printf("\n[!] Invalid marks input.\n");

        while (getchar() != '\n');

        return;
    }

    getchar();

    printf("Enter Contact: ");
    fgets(s.contact, sizeof(s.contact), stdin);
    stripNewline(s.contact);

    printf("Enter Email: ");
    fgets(s.email, sizeof(s.email), stdin);
    stripNewline(s.email);

    printf("Enter Batch: ");
    fgets(s.batch, sizeof(s.batch), stdin);
    stripNewline(s.batch);

    saveStudent(&s);

    printf("\n[✓] Student added successfully.\n");
}

/* View all students */
void viewAllStudents() {

    int count = 0;

    Student **arr = loadAllStudents(&count);

    if (!arr || count == 0) {

        printf("\n[i] No student records found.\n");
        return;
    }

    printTableHeader();

    for (int i = 0; i < count; i++) {
        printStudent(arr[i]);
    }

    printDivider();

    freeStudentArray(arr, count);
}

/* Search student by ID */
void searchStudentById(long long id) {

    int count = 0;

    Student **arr = loadAllStudents(&count);

    if (!arr || count == 0) {

        printf("\n[i] No records found.\n");
        return;
    }

    int found = 0;

    for (int i = 0; i < count; i++) {

        if (arr[i]->id == id) {

            printDivider();
            printTableHeader();
            printStudent(arr[i]);
            printDivider();

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("\n[!] Student with ID %lld not found.\n", id);
    }

    freeStudentArray(arr, count);
}

/* Delete student by ID */
void deleteStudentById(long long id) {

    int count = 0;

    Student **arr = loadAllStudents(&count);

    if (!arr || count == 0) {

        printf("\n[i] No records found.\n");
        return;
    }

    int found = -1;

    for (int i = 0; i < count; i++) {

        if (arr[i]->id == id) {
            found = i;
            break;
        }
    }

    if (found == -1) {

        printf("\n[!] Student with ID %lld not found.\n", id);

        freeStudentArray(arr, count);

        return;
    }

    free(arr[found]);

    for (int i = found; i < count - 1; i++) {
        arr[i] = arr[i + 1];
    }

    count--;

    rewriteDatabase(arr, count);

    printf("\n[✓] Student deleted successfully.\n");

    for (int i = 0; i < count; i++) {
        free(arr[i]);
    }

    free(arr);
}

/* Sort students by ID */
void sortStudentsById() {

    int count = 0;

    Student **arr = loadAllStudents(&count);

    if (!arr || count == 0) {

        printf("\n[i] No records found.\n");
        return;
    }

    for (int i = 0; i < count - 1; i++) {

        for (int j = 0; j < count - i - 1; j++) {

            if (arr[j]->id > arr[j + 1]->id) {

                Student *temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }

    rewriteDatabase(arr, count);

    printf("\n[✓] Records sorted by ID.\n");

    printTableHeader();

    for (int i = 0; i < count; i++) {
        printStudent(arr[i]);
    }

    printDivider();

    freeStudentArray(arr, count);
}

/* Update student by ID */
void updateStudentById(long long id) {

    int count = 0;

    Student **arr = loadAllStudents(&count);

    if (!arr || count == 0) {

        printf("\n[!] No records found.\n");
        return;
    }

    Student *student = NULL;

    for (int i = 0; i < count; i++) {

        if (arr[i]->id == id) {
            student = arr[i];
            break;
        }
    }

    if (student == NULL) {

        printf("\n[!] Student not found.\n");

        freeStudentArray(arr, count);

        return;
    }

    int choice;

    while (1) {

        printDivider();

        printf("EDIT STUDENT MENU\n");

        printDivider();

        printf("1. Update Name\n");
        printf("2. Update Age\n");
        printf("3. Update Marks\n");
        printf("4. Update Contact\n");
        printf("5. Update Email\n");
        printf("6. Update Batch\n");
        printf("0. Save & Exit\n");

        printDivider();

        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch(choice) {

            case 1:

                printf("Enter New Name: ");

                fgets(student->name,
                       sizeof(student->name),
                       stdin);

                stripNewline(student->name);

                break;

            case 2:

                printf("Enter New Age: ");

                if (scanf("%d", &student->age) != 1) {

                    printf("\n[!] Invalid input.\n");

                    while (getchar() != '\n');

                    continue;
                }

                getchar();

                break;

            case 3:

                printf("Enter New Marks: ");

                if (scanf("%f", &student->marks) != 1) {

                    printf("\n[!] Invalid input.\n");

                    while (getchar() != '\n');

                    continue;
                }

                getchar();

                break;

            case 4:

                printf("Enter New Contact: ");

                fgets(student->contact,
                       sizeof(student->contact),
                       stdin);

                stripNewline(student->contact);

                break;

            case 5:

                printf("Enter New Email: ");

                fgets(student->email,
                       sizeof(student->email),
                       stdin);

                stripNewline(student->email);

                break;

            case 6:

                printf("Enter New Batch: ");

                fgets(student->batch,
                       sizeof(student->batch),
                       stdin);

                stripNewline(student->batch);

                break;

            case 0:

                rewriteDatabase(arr, count);

                printf("\n[✓] Student updated successfully.\n");

                freeStudentArray(arr, count);

                return;

            default:

                printf("\n[!] Invalid choice.\n");
        }
    }
}
