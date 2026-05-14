#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include "../include/utils.h"

/* Remove newline from fgets() input */
void stripNewline(char *str) {
    str[strcspn(str, "\n")] = '\0';
}


/* Print full terminal width divider */
void printDivider() {

    struct winsize w;

    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    for (int i = 0; i < w.ws_col; i++) {
        printf("═");
    }

    printf("\n");
}

/* Print table column names */
void printTableHeader() {

    printDivider();

    printf("%-15s %-20s %-5s %-10s %-15s %-50s %-10s\n",
           "ID",
           "Name",
           "Age",
           "Marks",
           "Contact",
           "Email",
           "Batch");

    printDivider();
}

/* Print one student record */
void printStudent(const Student *s) {

    printf("%-15lld %-20s %-5d %-10.2f %-15s %-50s %-10s\n",
           s->id,
           s->name,
           s->age,
           s->marks,
           s->contact,
           s->email,
           s->batch);
}
