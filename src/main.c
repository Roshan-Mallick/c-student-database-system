#include <stdio.h>
#include <stdlib.h>

#include "../include/database.h"
#include "../include/file_handler.h"
#include "../include/utils.h"
#include "../include/export.h"

int main() {

    int choice;
    long long id;
    char batch[20];
    float cutoff;

    initDatabase();

    while (1) {

        printDivider();

        printf("STUDENT DATABASE SYSTEM\n");

        printDivider();

        printf("1. Add Student\n");
        printf("2. View All Students\n");
        printf("3. Search Student By ID\n");
        printf("4. Delete Student By ID\n");
        printf("5. Sort Students By ID\n");
        printf("6. Filter By Batch\n");
        printf("7. Filter By Marks\n");
        printf("8. Export To CSV\n");
        printf("9. Update Student By ID\n");
        printf("0. Exit\n");

        printDivider();

        printf("Enter choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                viewAllStudents();
                break;

            case 3:

                printf("Enter ID to search: ");
                scanf("%lld", &id);
                getchar();

                searchStudentById(id);
                break;

            case 4:

                printf("Enter ID to delete: ");
                scanf("%lld", &id);
                getchar();

                deleteStudentById(id);
                break;

            case 5:

                sortStudentsById();
                break;

            case 6:

                printf("Enter batch name: ");

                fgets(batch, sizeof(batch), stdin);
                stripNewline(batch);

                filterByBatch(batch);
                break;

            case 7:

                printf("Enter marks cutoff: ");
                scanf("%f", &cutoff);
                getchar();

                filterByMarks(cutoff);
                break;

            case 8:

                exportAllStudentsToCSV();
                break;

            case 9:

                    printf("Enter ID to update: ");
                    scanf("%lld", &id);
                    getchar();

                    updateStudentById(id);

                    break;

            case 0:

                printf("\nExiting program...\n");
                return 0;

            default:

                printf("\n[!] Invalid choice.\n");
        }

        printf("\n");
    }

    return 0;
}
