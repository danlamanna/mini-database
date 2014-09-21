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
 * Does preliminary checks, determines whether it should pass the work to _select_str or _select_int.
 * This function is only called from functions that already ensure the relation and attribute
 * exist, thus that is /assumed/ in this function.
 **/
void cmd_select(relation *relation, attribute *attribute, char *relop, char *value) {
  int int_value = atoi(value);
  FILE *data_file = get_data_file(relation);

  // Check if its a string or an integer, and call the appropriate function
  if (value[0] == '"' && value[strlen(value)-1] == '"') {
    // String Mode
    remove_quotes(value);

    if (attribute->data_type == ATTR_INT_TYPE) {
      printf("Error: Wrong type of value for attribute %s\n", attribute->name); fflush(stdout);
      return;
    } else if (strcmp(relop, "==") != 0 &&
               strcmp(relop, "!=") != 0) {
      printf("Error: Relational operator %s not supported with type string\n", relop); fflush(stdout);
      return;
    }

    _select_str(data_file, relation, attribute, relop, value);
  } else {
    // Integer Mode
    if (attribute->data_type == ATTR_STR_TYPE) {
      printf("Error: Wrong type of value for attribute %s\n", attribute->name); fflush(stdout);
      return;
    }

    _select_int(data_file, relation, attribute, relop, int_value);
  }

  fclose(data_file);
}

/**
 * Given an open file pointer, the relation it's for, the length of a single record, the attribute
 * the select is occurring on, the offset of that attribute in an individual record, and the relational
 * operator to compare value with.
 * Seeks through record by record, reading the integer valued attribute into tmp, then checking if it
 * matches the value given a relational operator, if so, it prints the record using print_record.
 **/
void _select_int(FILE *data_file, relation *relation, attribute *attribute, char *relop, int value) {
  int i = 0, tmp, found = 0;

  // Seek through each record, to the specified attribute
  while ((fseek(data_file, (i * relation->tuplen) + attribute->offset, SEEK_SET) == 0) &&
         (fread((void *) &tmp, attribute->data_len, 1, data_file) == 1)) {
    // If it satisfies relops condition, print the record for this attribute
    if ((strcmp("==", relop) == 0 && tmp == value) ||
        (strcmp("!=", relop) == 0 && tmp != value) ||
        (strcmp("<=", relop) == 0 && tmp <= value) ||
        (strcmp(">=", relop) == 0 && tmp >= value) ||
        (strcmp("<", relop) == 0 && tmp < value)   ||
        (strcmp(">", relop) == 0 && tmp > value)) {
      found = 1;
      print_record(data_file, (i * relation->tuplen), relation);
    }

    i++;
  }

  if (found == 0)
    printf("No tuples satisfy the specified condition.\n"); fflush(stdout);
}

/**
 * Given an open file pointer, the relation it's for, the length of a single record, the attribute
 * the select is occurring on, the offset of that attribute in an individual record, and the relational
 * operator to compare value with.
 * Seeks through record by record, reading the string valued attribute into tmp, then checking if it
 * matches the value given a relational operator, if so, it prints the record using print_record.
 **/
void _select_str(FILE *data_file, relation *relation, attribute *attribute, char *relop, char *value) {
  int i = 0, found = 0;

  // Allocate space for the temporary value
  char *tmp = malloc(sizeof(char) * attribute->data_len);

  // Seek through each record, to the specified attribute
  while ((fseek(data_file, (i * relation->tuplen) + attribute->offset, SEEK_SET) == 0) &&
         (fread((void *) tmp, attribute->data_len, 1, data_file) == 1)) {
    // If it satisfies the relops condition, print the record for this attribute
    if (((strcmp("==", relop) == 0) && (strcmp(tmp, value) == 0)) ||
        ((strcmp("!=", relop) == 0) && (strcmp(tmp, value) != 0))) {
      found = 1;
      print_record(data_file, (i * relation->tuplen), relation);
    }

    i++;
  }

  if (found == 0)
    printf("No tuples satisfy the specified condition.\n"); fflush(stdout);
}
