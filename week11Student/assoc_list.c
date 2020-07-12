#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <errno.h>

#define MAX_STRING_SIZE 10000

typedef struct {
	struct assoc_list_node *head;
} AssocList;	

struct assoc_list_node {
	char *key;
	char *value;
	struct assoc_list_node *next;
};

/*
** Return a pointer to a newly created association list.
*/
static AssocList *assoc_list_init(void);

/*
** Insert the specified key-value pair into the association list.  
** Note that trailing newlines are stripped from both 'key' and 'value'.
** Copies of both strings are made for the list, so you are free to delete
** the originals after insertion.
*/
static void assoc_list_insert(AssocList *list, char *key, char *value);

/*
** Return a pointer to the value associated with the specified key.
** Note that before lookup any trailing newlines are stripped from 'key'.
** Before returning this function sets the global variable 'number_of_lookups'
** to the number of lookups that were required in searching for 'key' in
** the association list.
*/
static char *assoc_list_lookup(AssocList *list, char *key);

/*
** Dump the contents of the association list to stdout.
** This is for debugging purposes.
*/
static void assoc_list_dump(AssocList *list);

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
static void read_records(FILE *fp, AssocList *list);

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
	AssocList *list = NULL;
	char key[MAX_STRING_SIZE];
	char *value = NULL;

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
	
	list = assoc_list_init();
	
	read_records(data_file, list);

	while (fgets(key, MAX_STRING_SIZE, stdin) != NULL)
	{
		value = assoc_list_lookup(list, chomp(key));

		printf("Searching for key = \"%s\", ", key);
		if (value == NULL)
		{
			printf("failed (%d lookups required)\n",
				number_of_lookups);
		}
		else
		{
			printf("succeeded - value = \"%s\"", value);
		        printf(" (%d lookups required)\n", number_of_lookups);
		}
	}		

	if (!feof(stdin))
	{
		fprintf(stderr, "Error while reading from stdin.\n");
		exit(EXIT_FAILURE);
	}
	
	return 0;
}

static AssocList *
assoc_list_init(void)
{
	AssocList *list;

	list = safe_malloc(sizeof(AssocList));
	list->head = NULL;

	return list;
}

static void
assoc_list_insert(AssocList *list, char *key, char *value)
{

	struct assoc_list_node *new_node = NULL;

	assert(list  != NULL);
	assert(key   != NULL);
	assert(value != NULL);
	
	new_node = safe_malloc(sizeof(struct assoc_list_node));
	
	new_node->key   = safe_strdup(chomp(key));
	new_node->value = safe_strdup(chomp(value));
	new_node->next  = list->head;
	
	list->head = new_node;
}

static char *
assoc_list_lookup(AssocList *list, char *key)
{

	char *value = NULL;
	struct assoc_list_node *node = NULL;

	assert(list != NULL);
	assert(key  != NULL);

	/* Reset the global lookup counter. */
	number_of_lookups = 0;
	
	for (node = list->head; node != NULL; node = node->next)
	{
		number_of_lookups++;
		if (strcmp(key, node->key) == 0)
		{
			value = node->value;
			break;
		}			
	}

	return value;
}

static void
assoc_list_dump(AssocList *list)
{
	struct assoc_list_node *node = NULL;

	for (node = list->head; node != NULL; node = node->next)
	{
		printf("%s - %s\n", node->key, node->value);
	}
}

static void
read_records(FILE *fp, AssocList *list)
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
		assoc_list_insert(list, key_buffer, value_buffer);
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
	
	copy =safe_malloc((strlen(str) + 1) * sizeof(char));
	
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
