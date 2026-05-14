
#ifndef UTILS_H
#define UTILS_H

#include "database.h"

/* Utility functions used in the project */

void stripNewline(char *str);     // removes \n from fgets
void printDivider();  // prints ═══════ line

void printStudent(const Student *s); /* Print one student record */

void printTableHeader(); /* Print table header row for view/sort output    */

#endif /* UTILS_H */
