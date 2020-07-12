#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define INITIAL_TABLE_SIZE 11 
#define MAX_STRING_SIZE 10000

typedef struct {
	char *key;
	char *value;
} TableEntry;

typedef struct {
	int table_size;
	int num_items;
	TableEntry *table;
} Hash_Table;

/*
** Return a pointer to a newly created hash table.
*/
static Hash_Table *hash_table_init(size_t size);

/*
** Insert the specified key-value pair into the hash table.  
** Note that trailing newlines are stripped from both 'key' and 'value'.
** Copies of both strings are made for the hash table, so you are free to delete
** the originals after insertion.
*/
static void hash_table_insert(Hash_Table *ht, char *key, char *value);

/*
** Return a pointer to the value associated with the specified key.
** Note that before lookup any trailing newlines are stripped from 'key'.
** Before returning this function sets the global variable 'number_of_lookups'
** to the number of lookups that were required in searching for 'key' in
** the hash table.
*/
static char *hash_table_lookup(Hash_Table *ht, char *key);

/*
** Dump the contents of the hash table to stdout.
** This is for debugging purposes.
*/
static void hash_table_dump(Hash_Table *ht);

/*
** Read key-value pairs from the specified stream (file) into
** an association list.  The expected input format is:
**
**	Key1
**	Value1
**	Key2
**
**	...
**
**	KeyN
** 	ValueN
**
** That is each key-value pair must occur on subsequent lines of 
** of the input.  Both keys and values are terminated by a newline
** character and may contain other whitespace characters.
**
** Aborts execution if the input is not in this format.
** Lines whose number of characters exceeds MAX_STRING_SIZE - 1,
** are truncated.
*/
static void read_records(FILE *fp, Hash_Table *ht);

/*
** Strip newlines from the end of a string.  Returns a 
** pointer to the string (this is useful if you want to use
** it in an expression).
**
** NOTE: this destructively updates the string so don't use
** it on strings that are stored in read-only memory.
*/
static char *chomp(char *str);

/*
** A safe string duplication function.  Aborts if memory
** cannot be allocated for the duplicate.
*/
static char *safe_strdup(const char *str);

/*
** Call malloc and abort if the specified amount of memory
** cannot be allocated.
*/
static void *safe_malloc(size_t size);

/*
** number_of_lookups is used when gathering statistics
** on the number of lookups performed when searching the dictionary.
*/
static int number_of_lookups;

int main(int argc, char **argv)
{
	FILE *data_file = NULL;
	Hash_Table *ht   = NULL;
	char *value     = NULL;
	char key[MAX_STRING_SIZE];
	
	if (argc != 2)
	{
		fprintf(stderr, "Usage: assoc_list <data_file>\n");
		exit(EXIT_FAILURE);
	}
	
	if ((data_file = fopen(argv[1], "r")) == NULL)
	{
		fprintf(stderr, "Unable to open file %s: %s\n",
			argv[1], strerror(errno));
		exit(EXIT_FAILURE);
	}
	
	ht = hash_table_init(INITIAL_TABLE_SIZE);
	
	read_records(data_file, ht);

	while (fgets(key, MAX_STRING_SIZE, stdin) != NULL)
	{
		value = hash_table_lookup(ht, chomp(key));

		printf("Searching for key = %s, ", key);
		if (value == NULL)
		{
			printf("failed (%d lookups required)\n",
				number_of_lookups);
		}
		else
		{
			printf("succeeded - value = %s (%d lookups required)\n",
				value, number_of_lookups);
		}
	}		

	if (!feof(stdin))
	{
		fprintf(stderr, "Error while reading from stdin.\n");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}

static Hash_Table *
hash_table_init(size_t size)
{
	fprintf(stderr, "hash_table_init() - NYI\n");
	exit(EXIT_FAILURE);
}

static void
hash_table_insert(Hash_Table *ht, char *key, char *value)
{
	fprintf(stderr, "hash_table_insert() - NYI\n");
	exit(EXIT_FAILURE);
}

static char *
hash_table_lookup(Hash_Table *ht, char *key)
{
	fprintf(stderr, "hash_table_lookup() - NYI\n");
	exit(EXIT_FAILURE);
}

static void
hash_table_dump(Hash_Table *ht)
{
	fprintf(stderr, "hash_table_dump() - NYI\n");
	exit(EXIT_FAILURE);
}

static void
read_records(FILE *fp, Hash_Table *ht)
{
	char key_buffer[MAX_STRING_SIZE];
	char value_buffer[MAX_STRING_SIZE];
	
	while (fgets(key_buffer, MAX_STRING_SIZE, fp) != NULL)
	{
		if (fgets(value_buffer, MAX_STRING_SIZE, fp) == NULL)
		{
			fprintf(stderr, "Badly formed input file");
			exit(EXIT_FAILURE);
		}
		hash_table_insert(ht, key_buffer, value_buffer);
	}
}	

static char *
chomp(char *str)
{
	size_t i;

	assert(str != NULL);
	
	for (i = strlen(str) - 1; str[i] == '\n'; i--)
	{
		str[i] = '\0';	
	}

	return str;
}

static char *
safe_strdup(const char *str)
{
	char *copy = NULL;

	assert(str != NULL);
	
	copy = safe_malloc((strlen(str) + 1) * sizeof(char));
	
	(void)strcpy(copy, str);

	return copy;	
}

static void *
safe_malloc(size_t size)
{
	void *mem;

	if ((mem = malloc(size)) == NULL)
	{
		fprintf(stderr, "Cannot allocate memory.\n");
		exit(EXIT_FAILURE);
	}
	
	return mem;
}
