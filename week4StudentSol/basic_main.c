
/*
** COMP20003 Algorithms and Data Structures
** WOrkshop 4 Elementary Sorting Algorithms
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basicsort.h"

#define MAX_NUM_RECORDS 5000

/*
** Read a sequence of integers from stdin and place them
** in an array of Records.  Associate a number with each
** integer that records which number is read in.
*/
int read_records(Record records[]);


void usage(const char *prog_name);

int
main(int argc, char **argv)
{

    Record records[MAX_NUM_RECORDS];
    int number_of_records;
    void (*sorting_algorithm)(Record *, int);

    if (argc != 2)
    {
        usage(argv[0]);
    }

    if (strcmp("selection", argv[1]) == 0)
    {
        sorting_algorithm = &selection_sort;
    }
    else if (strcmp("bubble", argv[1]) == 0)
    {
        sorting_algorithm = &bubble_sort;
    }
    else if (strcmp("insertion", argv[1]) == 0)
    {
        sorting_algorithm = &insertion_sort;
    }
    else
    {
        fprintf(stderr, "%s: do not support sorting algorithm %s.\n",
            argv[0], argv[1]);
        exit(EXIT_FAILURE);
    }
    
    number_of_records = read_records(records);
    
    printf("Sorting %d records ...\n\n", number_of_records);
    (*sorting_algorithm)(records, number_of_records); 
    
    print_records(records, number_of_records);
    printf("\n");
    
    printf("Number of comparisons = %d\n", number_of_comparisons); 
    
    if (test_if_sorted(records, number_of_records))
    {
        printf("OK: Records sorted.\n");
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
    
    return 0;
}

int
read_records(Record records[])
{

    int record_number = 0;
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
        records[record_number].value = record_number;
        
        record_number++;
    }

    return record_number;
}
                


void
usage(const char *prog_name)
{
    fprintf(stderr, "Usage: %s <sort>\n", prog_name);
    fprintf(stderr, "\twhere sort is bubble,  ");
    fprintf(stderr, "selection or insertion.\n");
    exit(EXIT_FAILURE);
}

