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
 * Returns an open file pointer to a relations data (binary) file,
 * given the file exists. Otherwise it prints an error to stderr,
 * and then exits.
 **/
FILE *get_data_file(relation *relation) {
  char *fname = malloc(sizeof(char) * (strlen(relation->name) + DATA_FILE_EXT_LEN + 1));
  FILE *infile;

  sprintf(fname, "%s%s", relation->name, DATA_FILE_EXT);

  if ((infile = fopen(fname, "r")) == NULL) {
    fprintf(stderr, "Could not open file %s for reading.\n", fname);
    exit(1);
  }

  free(fname);

  return infile;
}

/**
 * Returns an open file pointer to a relations schema (text) file,
 * given the file exists. Otherwise it prints an error to stderr,
 * and then exits.
 **/
FILE *get_schema_file(relation *relation) {
  FILE *tmpfile;
  char tmp[DATA_FILE_LENGTH + 1];

  sprintf(tmp, "%s%s", relation->name, SCHEMA_FILE_EXT);

  if ((tmpfile = fopen(tmp, "r")) == NULL) {
    fprintf(stderr, "Could not open file %s for reading.\n", tmp);
    exit(1);
  }

  return tmpfile;
}

/**
 * Retrieves the relation by it's name.
 * Returns a NULL pointer if the relation specified
 * does not exist.
 **/
relation *get_relation(char *relation) {
  int i;

  for (i=0;i<num_relations;i++)
    if (strcmp(relation, relations[i]->name) == 0)
      return relations[i];

  return NULL;
}

/**
 * Retrieves the attribute that belongs to the given relation,
 * by the attributes name.
 * Returns a NULL pointer if the attribute specified
 * does not exist.
 **/
attribute *get_attribute(relation *relation, char *attribute) {
  int i;

  for (i=0;i<relation->num_attrs;i++)
    if (strcmp(attribute, relation->attributes[i]->name) == 0)
      return relation->attributes[i];

  return NULL;
}

/**
 * Removes quotes from a string.
 **/
void remove_quotes(char *s) {
  const char *quote = "\"";

  while((s = strstr(s, quote)))
    memmove(s, s + 1, 1 + strlen(s + 1));
}
