/**
 * Dan LaManna
 * dl954588
 * dlamanna@albany.edu
 **/

// config.c
void _process_config_file(char *config_filename);

// parser.c
void _process_query(char *query);

// sort.c
int compare_str(const void *a, const void *b);
int compare_int(const void *a, const void *b);

// select.c
void cmd_select(relation *relation, attribute *attribute, char *relop, char *value);
void _select_int(FILE *data_file, relation *relation, attribute *attribute, char *relop, int value);
void _select_str(FILE *data_file, relation *relation, attribute *attribute, char *relop, char *value);

// project.c
void cmd_project(relation *relation, attribute *attribute);
void _project_int(FILE *data_file, relation *relation, attribute *attribute);
void _project_str(FILE *data_file, relation *relation, attribute *attribute);

// count.c
int cmd_count(relation *relation);

// utils.c
FILE *get_data_file(relation *relation);
FILE *get_schema_file(relation *relation);
relation *get_relation(char *relation);
attribute *get_attribute(relation *relation, char *attribute);
void remove_quotes(char *s);

// output.c
void print_record(FILE *data_file, int offset, relation *relation);
