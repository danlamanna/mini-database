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
 * Processes an individual query.
 * Tokenizes each line into its parts, accounting for the differences between
 * which commands need which arguments.
 * Checks if each relation (and possibly attribute) exist before processing.
 * Then runs the appropriate function for which command it is.
 **/
void _process_query(char *query) {
  relation *relation;
  attribute *attribute;

  char *command, *rel_name = NULL, *attr_name = NULL, *relop;
  char *value;

  // Get command
  command = strtok(query, QUERY_DELIM);

  // End the program if it's the quit command
  if (strcmp("quit", command) == 0)
    exit(0);

  // relation name is provided for all queries except quit
  rel_name = strtok(NULL, QUERY_DELIM);

  // get the attribute name if it's needed for this command
  if ((strcmp("infattr", command) == 0) ||
      (strcmp("project", command) == 0) ||
      (strcmp("select", command) == 0)) {
    attr_name = strtok(NULL, QUERY_DELIM);
  }

  // Check that the relation name exists, and if the command uses the attribute name,
  // the attribute exists on that relation.
  if ((relation = get_relation(rel_name)) == NULL) {
    printf("Error: Invalid relation -- %s\n\n", rel_name); fflush(stdout);
    return;
  } else if (attr_name != NULL && ((attribute = get_attribute(relation, attr_name)) == NULL)) {
    printf("Error: Invalid attribute -- %s\n\n", attr_name); fflush(stdout);
    return;
  }

  // Run through each command, calling the appropriate functions with the right arguments
  if (strcmp("infattr", command) == 0) {
    printf("Attribute type  :  %c\n", attribute->data_type); fflush(stdout);
    printf("Attribute length:  %d\n", attribute->data_len); fflush(stdout);
  } else if (strcmp("nattr", command) == 0) {
    printf("%d\n", relation->num_attrs); fflush(stdout);
  } else if (strcmp("tuplen", command) == 0) {
    printf("%d\n", relation->tuplen); fflush(stdout);
  } else if (strcmp("count", command) == 0) {
    printf("%d\n", cmd_count(relation)); fflush(stdout);
  } else if (strcmp("project", command) == 0) {
    cmd_project(relation, attribute); fflush(stdout);
  } else if (strcmp("select", command) == 0) {
    // Need to parse the relop
    relop = strtok(NULL, QUERY_DELIM);
    // Grab value as string
    value = strtok(NULL, QUERY_DELIM);

    cmd_select(relation, attribute, relop, value);
  }

  printf("\n");
}
