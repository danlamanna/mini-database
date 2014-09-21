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
 * Counts the number of records in a relation (binary) file.
 * Seeks to the end of the file, and divides the length of the
 * file by the length of a single record.
 **/
int cmd_count(relation *relation) {
  FILE *data_file = get_data_file(relation);
  int count = 0;

  // Seek to end of the file
  fseek(data_file, 0L, SEEK_END);

  // Calculate the length of the file, over the length of a single tuple
  count = ftell(data_file) / relation->tuplen;

  fclose(data_file);

  // Return number of tuples
  return count;
}
