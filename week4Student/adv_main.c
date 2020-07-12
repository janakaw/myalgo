/*
** COMP20003 Algorithms and Data Structures
** WOrkshop 4 Elementary Sorting Algorithms
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basicsort.h"

#define MAX_NUM_RECORDS 5000000 

/*
** These four functions implement the four sorting algorithms.
*/
void libsort(Record records[], size_t num_records);
void basic_quicksort(Record records[],  size_t num_records);
void basic_mergesort(Record records[], size_t num_records);

int compare_records_for_qsort(const void *a, const void *b);

size_t read_records(Record records[]);


/*
** Print out a usage message to stderr and aborts execution.
*/

void usage(const char *prog_name);

void *safe_malloc(size_t size);

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
    print_records(records, number_of_records);
    printf("\n");

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

void
libsort(Record records[], size_t num_records)
{
	qsort(records, num_records, sizeof(Record),
		compare_records_for_qsort);
}
			
void
basic_quicksort(Record records[], size_t num_records)
{
	fprintf(stderr, "basic_quicksort(): NYI\n");
	exit(EXIT_FAILURE);
}    

void
basic_mergesort(Record records[], size_t num_records)
{
	fprintf(stderr, "basic_mergesort(): NYI\n");
	exit(EXIT_FAILURE);
}    


int
compare_records_for_qsort(const void *a, const void *b)
{
	return ((const Record *)a)->key - ((const Record *)b)->key;
}



size_t 
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
                
void
usage(const char *prog_name)
{
    fprintf(stderr,
	"Usage: %s <sort>\n"
    	"\twhere sort is quicksort, mergesort, "
    	"or libsort.\n", prog_name);
    exit(EXIT_FAILURE);
}

void *
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
