/**
 * Dan LaManna
 * dl954588
 * dlamanna@albany.edu
 **/

/**
 * Defines an attribute on a relation, including it's name,
 * type (S or I), length (in bytes), and offset (in the record).
 **/
typedef struct attribute {
  char *name;
  char data_type;
  int data_len;
  int offset;
} attribute;

/**
 * Defines a relation, including it's name, number of attributes,
 * individual tuple length, and an array of attribute pointers.
 **/
typedef struct relation {
  char *name;
  int num_attrs;
  int tuplen;
  attribute **attributes;
} relation;
