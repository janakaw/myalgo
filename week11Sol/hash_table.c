/*
** comp20003 Algorithms and Data Structures
** Workshop Exercise Week 11: Dictionaries
*/

/*Name: Willix Halim
*/

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
/*
static void hash_table_dump(Hash_Table *ht);
*/

/* 
 * Generate hash index for a specified key(string) associated with 
 * the table size. This hash index determines the place in the table,
 * specified string key will be located at.
 */
static int hash_table_index(char *key, size_t ht_size);

/*
 * Find the closest next prime number from parameter number
 */
static int find_next_prime (int number);

/* 
 * Rehash function is the operation of resizing a hash table 
 * when the load factor exceeds 85 % in our case
 */
static void rehash_table (Hash_Table *ht, size_t newsize);

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
   
    /* For debugging purpose 
    hash_table_dump(ht);
    */
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

/*
 * Initialize the hash table of specified size
 *
 *  Parameters :
 *      size        - size of the hash table created / initialized
 *  
 *  Return :
 *      ht          - Initialized hash table entry
 */
static Hash_Table *
hash_table_init(size_t size)
{
    Hash_Table *ht;
    int i = 0;
    ht = safe_malloc (sizeof(Hash_Table));
    ht->table = safe_malloc (size * sizeof(TableEntry));
    ht->table_size = size;
    ht->num_items = 0;

    /* Initialize all the table entries's key and value to be null */
    for ( i = 0 ; i < size ; i++)
    {
        ht->table[i].key = NULL;
        ht->table[i].value = NULL;
    }

    return ht;
}

/*
 *  This function calculates the hash index used to determine the position
 *  the specified string key along with its value 
 *  will be located at in the table. The hash index is calculated using
 *  its ASCII value and also the size of the hash table
 * 
 *  Parameters :
 *      key     - string key of which position in the table will be calculated
 *                  using this function
 *      ht_size - The size of the hash_table
 *
 *
 *  Return :
 *      hashkey - the hash index calculated
 */
    
static int
hash_table_index(char *key, size_t ht_size)
{
    int i = 0;
    int hashkey=0;
    char *chompedkey = chomp(key);

    /* Loop to calculate the hash index by looking at all the ascii values
     * of all the characters of key
     */

    for (i = 0; chompedkey[i]!=NULL ; i++)
    {
       /* This algorithm of calculating hash index for key (strings) is
        * described in section 7.3 in the text book
        * 200 is the constant used as it is recommended that the constant
        * must be larger than ascii value. 
        */ 
       hashkey = ((200*hashkey) + (int)chompedkey[i]) % ht_size;
    }
    
    hashkey = hashkey;

    return hashkey;
}    

/*
 * Find the closest next prime number from parameter number
 *
 * Parameters :
 *      number      - the parameter 
 *
 * Return :
 *      number      - the closest next prime number 
 */

static int
find_next_prime (int number)
{
    int i = 2;

    while (i < number)
    {
      if (number % i == 0)   
      {
        i = 2;
        number++;  
      }
      else
        i++;  
    }
    return number;
}    

/*
 * This function inserts key and value into the hash table 
 * depending on the hashindex found by using hash_table_index function
 * If the table exceeds 85 percent load factor, then rehashing will be 
 * done, which basically allocates a new table with size doubled and has
 * to be prime number
 * 
 * Parameters
 *      ht      - The hash table
 *      key     - The string key inserted
 *      value   - The value associated with the key
 *
 * Return
 * None
 */
                   
static void
hash_table_insert(Hash_Table *ht, char *key, char *value)
{
    int hashkey;
    int newsize;

    /* If the load factor exceeds 85 percent then find the next prime
     * number closest to double of the size of the old table
     * and rehash
     */
    if ( ht->num_items >= (0.85*ht->table_size))
    {
      newsize = find_next_prime ((ht->table_size)*2);
      rehash_table (ht, newsize);
    }
   
    /* Calculate the hash index of the key*/
    hashkey = hash_table_index(chomp(key),ht->table_size);

    /* If the location has already value in it, then check the cell
     * following the one where the collision occurs. If the collision
     * occurs in that cell again, we check the next cell and so on
     * If we have already come to the end of the table then wrap around
     * to the front of the table 
     */ 
    while ( ht->table[hashkey].key != NULL )
    {
      hashkey++;
      if (hashkey >= ht->table_size)
          hashkey = 0;
    }

    /* Then copy the key and the value specified into the specified location
     * of the table using strdup
     */
    ht->num_items++; 
    ht->table[hashkey].key = safe_strdup(chomp(key));
    ht->table[hashkey].value = safe_strdup(chomp(value));
}

/* 
 * This function is basically implementing rehashing algorithm
 * 1. create a new table and allocate memory for it of size newsize
 *      new size will be prime number as it provides better distribution
 * 2. traverse the old table and insert each entry into the new table.
 *      this insertion will then involve computing a new hash index for the
 *      entry
 * 3. Having done all the insertion and traversing, the old table will then
 *      be freed
 *
 * Parameters :
 *      ht     - The hash table required to be resized / rehashed
 *      newsize- The new size for the hashtable (prime number in this case)   
 *      
 * Return :
 * None/void
 */

static void
rehash_table (Hash_Table *ht, size_t newsize)
{
  TableEntry *newtable = NULL;
  int hashkey;
  int i = 0;

  /* Initialize the new table entry of size newsize */
  newtable = safe_malloc (newsize * sizeof(TableEntry));

  /* Inserting each entry of the old table traversed into the new table
   */
  for (i=0; i < ht->table_size ; i++)
  {
    if (ht->table[i].key!=NULL)
    {
       /* Calculate the hash index of the key*/
       hashkey = hash_table_index (ht->table[i].key, newsize);

    /* If the location has already value in it, then check the cell
     * following the one where the collision occurs. If the collision
     * occurs in that cell again, we check the next cell and so on
     * If we have already come to the end of the table then wrap around
     * to the front of the table 
     */ 
       while (newtable[hashkey].key != NULL )
       {
         hashkey++;
         if (hashkey >= newsize)
           hashkey = 0;
       }

       /* No strdup required. Instead, just point the newtable to 
        * already address allocated keys and values on the old table
        * This is because using strdup will then involve copying
        * old table's keys and values 
        * into new table then freeing the old table's keys
        * and values which will be such a nuisance as the keys and 
        * values copied will just be the same.
        */
       newtable[hashkey].key = ht->table[i].key;
       newtable[hashkey].value = ht->table[i].value;
    }
  }

  ht->table_size = newsize;

  /* Free the old table and update it with the new table */
  free(ht->table);
  ht->table = newtable;
}  

/*
 * This function searches the hash table for a key specified by again
 * calculating the hash index of the specified key using the same
 * algorithm as insertion. then look for the index calculated.
 * If the key in that position is not the same, then collision must have 
 * happened. Hence, check the cell following the one where the collision
 * and so on. 
 * The search will stop when it either successfully looks for the specified
 * key or fails as it meets a null node.
 *
 * Parameters
 *      ht      - hash table
 *      key     - key being searched for
 *
 * Return
 *      the value of the specified key if there's a match and NULL 
 *      if there is no specified key in the table entry
 */
static char *
hash_table_lookup(Hash_Table *ht, char *key)
{
    /* Calculate the hash index of the key*/
    int hashkey = hash_table_index(key,ht->table_size);
    /* To keep track how many lookups required */
    number_of_lookups = 0;

    while ( ht->table[hashkey].key != NULL )
    {
        number_of_lookups++;
        if ( (strcmp (key, ht->table[hashkey].key)) == 0)
            return ht->table[hashkey].value;

        hashkey++;

     /* If we have already come to the end of the table then wrap around
      * to the front of the table 
      */
       if(hashkey >= ht->table_size)
            hashkey = 0;
    }
    return NULL;
}

/* For debugging purpose
static void
hash_table_dump(Hash_Table *ht)
{
    int i = 0;
    for ( i = 0; i < ht->table_size ; i++)
    {
        if (ht->table[i].key != NULL)
            printf ("%d %s %s\n" , i, ht->table[i].key , ht->table[i].value);
    } 
}
*/

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
