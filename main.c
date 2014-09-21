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
 * These are both global, due to the fact that they were being passed
 * to almost every function.
 **/
relation **relations;
int num_relations;

/**
 * Reads in a configuration file and a query file.
 * Builds an in memory representation of each relation and their attributes.
 * It then reads the query file line by line and executes the
 * query, printing the results.
 **/
int main(int argc, char *argv[]) {
  FILE *query_file;
  char query[QUERY_FILE_LINE_LENGTH + 1] = {'\0'};

  if (argc != REQUIRED_ARGC) {
    fprintf(stderr, "Usage: p3 configfile queryfile\n");
    exit(1);
  }

  // Read the relations and attributes into memory
  _process_config_file(argv[CONFIG_FILE_ARGV]);

  // Open the query file
  if ((query_file = fopen(argv[QUERY_FILE_ARGV], "r")) == NULL) {
    fprintf(stderr, "Failed to open %s\n", argv[QUERY_FILE_ARGV]);
    exit(1);
  }

  // Process each query line by line
  while (fgets(query, QUERY_FILE_LINE_LENGTH, query_file) != NULL)
    _process_query(query);

  fclose(query_file);

  return 0;
}
