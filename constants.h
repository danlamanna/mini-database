/**
 * Dan LaManna
 * dl954588
 * dlamanna@albany.edu
 **/

// Argc/Argv
#define REQUIRED_ARGC 3
#define CONFIG_FILE_ARGV 1
#define QUERY_FILE_ARGV  2

// Delimiter between segments of a query
#define QUERY_DELIM " \t\n"

// File extensions
#define DATA_FILE_EXT ".dat"
#define SCHEMA_FILE_EXT ".sch"

// Attribute Types
#define ATTR_STR_TYPE 'S'
#define ATTR_INT_TYPE 'I'

// Extension length
#define DATA_FILE_EXT_LEN 4

// Length of a data filename
#define DATA_FILE_LENGTH 19 // 15 + .dat

// Number of segments in a schema line
#define SCHEMA_SEGMENT_LEN 3

// Maximum length of a relation name
#define REL_NAME_LEN 15

// Maximum length of a query file line
#define QUERY_FILE_LINE_LENGTH 100
