/*
** 433-253 Algorithms and Data Structures
** Laboratory Exercise Week 4: Advanced Sorting Algorithms
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_NUM_RECORDS 5000000 

/*
** The records to be sorted.  The 'key' is the part read in from stdin.
** It is the part that governs the sorting process.  The 'value' field is
** assigned by the read_records() function.  We use it to test for stability.
*/
typedef struct {
    int key;
    int value;
} Record;

/*
** These four functions implement the four sorting algorithms.
*/
static void libsort(Record records[], size_t num_records);
static void basic_quicksort(Record records[],  size_t num_records);
static void basic_mergesort(Record records[], size_t num_records);

/*
** Compares two records.  Returns an integer < 0 if
** a < b, ==0 if a == b and > 0 if a > b.  This function
** also increments the global variable 'number_of_comparisons'.
**
** NOTE: we pass pointers to the records rather than passing then by value.
*/
static int compare_records(Record *a,  Record *b);

/*
** This version is for use with the standard library's qsort function.
*/
static int compare_records_for_qsort(const void *a, const void *b);

/*
** Swap the contents of the two records.
*/
static void swap_records(Record *a, Record *b);

/*
** Test if the array of records is sorted.
** Returns true if the array is sorted, false otherwise.
*/
static int test_if_sorted(Record records[], size_t num_records);

/*
** Test if the sort was stable.
** It does this by using the 'value' field in the structure.   
** Returns true if this is the case or false otherwise.
*/
static int test_if_stable(Record records[], size_t num_records);

/*
** Read a sequence of integers from stdin and place them in an array of
** Records.  Associate a number with each integer that records which
** number is read in.
*/
static size_t read_records(Record records[]);

/*
** Print the array of records.
*/
static void print_records(Record records[], size_t num_records);

/*
** Print out a usage message to stderr and aborts execution.
*/
static void usage(const char *prog_name);

static void *safe_malloc(size_t size);

int
main(int argc, char **argv)
{

    Record *records = NULL;
    size_t number_of_records;
    void (*sorting_algorithm)(Record *, size_t);

    /*
    ** We allocate the array on the heap rather than the stack because
    ** we not be able to fit really large arrays on the stack.
    */
    records = safe_malloc(sizeof(Record) * MAX_NUM_RECORDS);	
    
    if (argc != 2)
    {
        usage(argv[0]);
    }

    if (strcmp("quicksort", argv[1]) == 0)
    {
        sorting_algorithm = &basic_quicksort;
    }
    else if (strcmp("mergesort", argv[1]) == 0)
    {
        sorting_algorithm = &basic_mergesort;
    }
    else if (strcmp("libsort", argv[1]) == 0)
    {
	sorting_algorithm = &libsort;
    }
    else
    {
        fprintf(stderr, "%s: do not support sorting algorithm %s.\n",
            argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }
    
    number_of_records = read_records(records);
   
    (*sorting_algorithm)(records, number_of_records); 
    
/* For debugging only ... */ 
/* 
    print_records(records, number_of_records);
    printf("\n");
*/    

    if (test_if_sorted(records, number_of_records))
    {
        printf("OK: Records sorted in.");
        if (test_if_stable(records, number_of_records))
        {
            printf("Sort run was stable.\n");
        }
        else
        {
            printf("Sort run was not stable.\n");
        }
    }
    else
    {
        printf("ERROR: Records not sorted.\n");
    }

    free(records); 
    return 0;
}

static void
libsort(Record records[], size_t num_records)
{
	qsort(records, num_records, sizeof(Record),
		compare_records_for_qsort);
}
			
static void
basic_quicksort(Record records[], size_t num_records)
{
	fprintf(stderr, "basic_quicksort(): NYI\n");
	exit(EXIT_FAILURE);
}    

static void
basic_mergesort(Record records[], size_t num_records)
{
	fprintf(stderr, "basic_mergesort(): NYI\n");
	exit(EXIT_FAILURE);
}    

static int
compare_records(Record *a, Record *b)
{
    return a->key - b->key;
}

static int
compare_records_for_qsort(const void *a, const void *b)
{
	return ((const Record *)a)->key - ((const Record *)b)->key;
}

static void
swap_records(Record *a, Record *b)
{
    
    Record tmp;

    tmp = *a;
    *a  = *b;
    *b  = tmp;
}

/*
** Returns true if the array of records is sorted (in ascending
** numerical order) and false otherwise.
*/
static int
test_if_sorted(Record records[], size_t num_records)
{

    size_t i;

    for (i = 0; i < num_records - 1; i++)
    {
        if (records[i + 1].key < records[i].key)
        {
            return 0;
        }
    }

    return 1;
}

static int
test_if_stable(Record records[], size_t num_records)
{
        size_t i;
        
        for (i = 1; i < num_records; i++)
        {
            if (records[i].key == records[i - 1].key)
            {
                if (records[i].value <= records[i - 1].value)
                {
                    return 0;
                }
            }
        }

        return 1;
}

static size_t 
read_records(Record records[])
{

    size_t record_number = 0;
    int key;
    
    while (scanf("%d", &key) == 1)
    {
        
        if (record_number >= MAX_NUM_RECORDS)
        {
            fprintf(stderr, "WARNING: truncating input at %d records.\n",
                MAX_NUM_RECORDS);
            break;
        }

        records[record_number].key = key;
        records[record_number].value = (int) record_number;
        record_number++;
    }

    return record_number;
}
                
static void
print_records(Record records[], size_t num_records)
{

    size_t i;

    printf("Key\tValue\n");
    for (i = 0; i < num_records; i++)
    {
        printf("%d\t%d\n", records[i].key, records[i].value);
    }
}

static void
usage(const char *prog_name)
{
    fprintf(stderr,
	"Usage: %s <sort>\n"
    	"\twhere sort is quicksort, mergesort, "
    	"or libsort.\n", prog_name);
    exit(EXIT_FAILURE);
}

static void *
safe_malloc(size_t size)
{
	void *mem = NULL;

	if ((mem = malloc(size)) == NULL)
	{
		fprintf(stderr, "Unable to allocate memory.\n");
		exit(EXIT_FAILURE);
	}
	return mem;
}	
