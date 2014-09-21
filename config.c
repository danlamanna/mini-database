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

// Access to global relation variables
extern relation **relations;
extern int num_relations;

/**
 * Takes the name of a configuration file, processes it line by line.
 * For each relation mentioned in the configuration file, it allocates
 * space for a relation struct and reads that relations schema file.
 * It parses the schema file and allocates an attribute struct for each attribute,
 * with the details of its name, type, and length.
 **/
void _process_config_file(char *config_filename) {
  FILE *config_file, *tmp_schema_file;
  attribute **attributes;
  char attr_type;
  char config_line[REL_NAME_LEN + 1 + 1]; // 15 + \n + \0
  int attr_len, i = 0, j = 0, tuplen = 0;
  char attr_name[REL_NAME_LEN + 1];

  // Ensure config file can be opened
  if ((config_file = fopen(config_filename, "r")) == NULL) {
    fprintf(stderr, "Failed to open %s for reading.\n", config_filename);
    exit(1);
  }

  // Read in the number of relations, and allocate a pointer for each
  // These read into global variables relations, num_relations
  fscanf(config_file, "%d", &num_relations);
  relations = (relation **) malloc(sizeof(relation *) * num_relations);

  // Read each line of the config file (after the num relations line), which is in the format:
  // <relation name 1>
  // ...
  // <relation name n>
  while (fscanf(config_file, "%s", config_line) == 1) {
    tuplen = j = 0;
    relations[i] = malloc(sizeof(relation));
    relations[i]->name = strdup(config_line);

    // Get the file pointer for the specified relation
    tmp_schema_file = get_schema_file(relations[i]);

    // Read in the number of attributes in this relation to it's struct, and allocate
    // a pointer that number of attributes.
    fscanf(tmp_schema_file, "%d", &relations[i]->num_attrs);
    attributes = (attribute **) malloc(sizeof(attribute *) * relations[i]->num_attrs);

    // Read each line of the schema file (after the num attrs line), which is in the format:
    // <attr 1 name> <S|I> <n>
    // Where n signifies the number of bytes, and S or I indicates whether it is a string or int
    while (fscanf(tmp_schema_file, "%s %c %d", attr_name, &attr_type, &attr_len) == SCHEMA_SEGMENT_LEN) {
      // Setup the attribute, with it's name, type, and length
      attributes[j]            = malloc(sizeof(attribute));
      attributes[j]->name      = strdup(attr_name);
      attributes[j]->data_type = attr_type;
      attributes[j]->data_len  = attr_len;
      attributes[j]->offset    = tuplen;

      tuplen += attr_len;

      j++;
    }

    // Set the tuplen of a relation
    relations[i]->tuplen = tuplen;

    // Assign these attributes to their relation
    relations[i]->attributes = attributes;

    fclose(tmp_schema_file);

    i++;
  }

  fclose(config_file);
}
