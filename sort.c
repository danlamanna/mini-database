/**
 * Dan LaManna
 * dl954588
 * dlamanna@albany.edu
 **/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "constants.h"
#include "struct_def.h"
#include "prototypes.h"

/**
 * Returns the value of strcmp while casting a and b
 * properly. To be used as qsorts function pointer.
 **/
int compare_str(const void *a, const void *b) {
  return strcmp(*(char **)a, *(char **)b);
}

/**
 * Returns -1 if a < b, 1 if a > b, and 0 if equal.
 * To be used as qsorts function pointer.
 **/
int compare_int(const void *a, const void *b) {
  return (*(int*)a < *(int*)b) ? -1 : (*(int*)a == *(int*)b) ? 0 : 1;
}
