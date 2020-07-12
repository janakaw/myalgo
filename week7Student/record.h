// record.h
// defines record type and declares the functions
// awirth
// aug 09

#define MAXKEY INT_MAX
#define MAXSTR 100

typedef struct rec {
	int key;
	char value[MAXSTR+1];
} record;

/*
void
record_string(char *s,record r);

void
set_value(char *dest, char *source);

record *
make_record(int key, char *value);
*/
