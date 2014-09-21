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

extern relation **relations;
extern int num_relations;

/**
 * Calls either _project_int or _project_str based on the type of attribute.
 **/
void cmd_project(relation *relation, attribute *attribute) {
  FILE *data_file = get_data_file(relation);

  if (attribute->data_type == ATTR_INT_TYPE) {
    _project_int(data_file, relation, attribute);
  } else if (attribute->data_type == ATTR_STR_TYPE) {
    _project_str(data_file, relation, attribute);
  }
}

/**
 * Given an open file pointer, a relation, and an attribute, this projects all distinct
 * values of the specified attribute.
 * It seeks record by record to the specified attributes location and adds it an array of
 * values, then uses quicksort to ease the de-duplication.
 **/
void _project_int(FILE *data_file, relation *relation, attribute *attribute) {
  int tmp;
  int i=0, j=0, last;
  int values[cmd_count(relation)];


  // Loop through each record, adding the integer value to values
  while ((fseek(data_file, (i * relation->tuplen) + attribute->offset, SEEK_SET) == 0) &&
         (fread((void *) &tmp, attribute->data_len, 1, data_file) == 1)) {
    values[i] = tmp;
    i++;
  }

  // Sort all the integers using compare_int function
  qsort(values, i, sizeof(int), compare_int);

  // Loop through, print values (ignoring duplicates)
  for (j=0;j<i;j++) {
    if ((j == 0) || (last != values[j])) { // if it's the first iteration, or it's a unique integer
      printf("%d\n", values[j]); fflush(stdout);
      last = values[j];
    }
  }

  fclose(data_file);
}

/**
 * Given an open file pointer, a relation, and an attribute, this projects all distinct
 * values of the specified attribute.
 * It seeks record by record to the specified attributes location and adds it an array of
 * values, then uses quicksort to ease the issue of de-duplication.
 **/
void _project_str(FILE *data_file, relation *relation, attribute *attribute) {
  // No +1, handout states the data_len includes the \0
  char *tmp  = malloc(sizeof(char) * attribute->data_len);
  char *last = malloc(sizeof(char) * attribute->data_len);
  int i=0, j=0;
  char *values[cmd_count(relation)];

  // Loop through each record recording the value in values
  while ((fseek(data_file, (i * relation->tuplen) + attribute->offset, SEEK_SET) == 0) &&
         (fread((void *) tmp, attribute->data_len, 1, data_file) == 1)) {
    values[i] = strdup(tmp);
    i++;
  }

  // Sort all the strings using compare_str function
  qsort(values, i, sizeof(char *), compare_str);

  // Loop through, print values (ignoring duplicates)
  for (j=0;j<i;j++) {
    if (strcmp(last, values[j]) != 0) {
      printf("%s\n", values[j]); fflush(stdout);
      last = values[j];
    }
  }

  free(tmp);
  free(last);
  fclose(data_file);
}
