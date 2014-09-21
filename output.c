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
 * Pretty prints a record.
 * Given a pointer to an already opened file, and the offset of the
 * individual record to print, and the name of the relation, print_record
 * retrieves the information about a relations attributes, loops through them
 * and prints the values of each attribute, formatted by it's length.
 **/
void print_record(FILE *data_file, int offset, relation *relation) {
  int j, tmp_int;
  char *tmp_str = NULL;

  // Seek to the record to print
  fseek(data_file, (long) offset, SEEK_SET);

  // For each attribute in the relation, get value and output
  for (j=0;j<relation->num_attrs;j++) {
    if (relation->attributes[j]->data_type == ATTR_INT_TYPE) {
      // Read in an integer value
      fread((void *) &tmp_int, relation->attributes[j]->data_len, 1, data_file);

      // Output value
      printf("%d\t", tmp_int); fflush(stdout);
    } else if (relation->attributes[j]->data_type == ATTR_STR_TYPE) {
      // Allocate space for the string to read in
      tmp_str = malloc(sizeof(char) * relation->attributes[j]->data_len);

      // Read in the string
      fread((void *) tmp_str, relation->attributes[j]->data_len, 1, data_file);

      // Print string (formatted to the length of the attribute)
      printf("%-*s\t", relation->attributes[j]->data_len, tmp_str); fflush(stdout);

      free(tmp_str);
    }

    // Print ending newline
    if (j == (relation->num_attrs - 1))
      printf("\n");
  }
}
