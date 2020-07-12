/*
** COMP20003 Algorithms and Data Structures
** WOrkshop 4 Elementary Sorting Algorithms
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "basicsort.h"




/* void
bubble_sort(Record records[], int num_records)
{
    fprintf(stderr, "bubble_sort(): NYI\n");
    exit(EXIT_FAILURE);
}

*/

void
bubble_sort(Record records[], int num_records)
{
    /*
    ** This code was adapted from that in provided in
    ** "Programming, Problem Solving and Abstraction with C"
    ** by Alistair Moffat.
    **
    ** Unlike the pseudocode provided in Section 3.1 of Levitin,
    ** this implementation performs better on almost sorted files.
    **
    */
    int didswaps = 1;
    int i;
   
    while (didswaps)
    {
        didswaps = 0;
        for (i = 0; i < num_records - 1; i++)
        {
            if (compare_records(&records[i], &records[i + 1]) > 0)
            {
                swap_records(&records[i], &records[i + 1]);
                didswaps = 1;
            }
        }

     }
}


/*
** Compares two records.  Returns an integer < 0 if
** a < b, ==0 if a == b and > 0 if a > b.  This function
** also increments the global variable 'number_of_comparisons'.
**
** NOTE: we pass pointers to the records rather than
** passing then by value.
*/
int compare_records(Record *a,  Record *b);

/*
** Swap the contents of the two records.
*/
void swap_records(Record *a, Record *b);

/*
** These global variables are used to record the number of
** comparisons and swaps.
*/


/*
** Test if the array of records is sorted.
** Returns true if the array is sorted, false otherwise.
*/
int test_if_sorted(Record records[], int num_records);

/*
** Test if the sort was stable.
** It does this by using the 'value' field in the structure.   
** Returns true if this is the case, false otherwise.
*/
int test_if_stable(Record records[], int num_records);
/*
** Print the array of records.
*/
void print_records(Record records[], int num_records);




void
selection_sort(Record records[], int num_records)
{
    fprintf(stderr, "selection_sort(): NYI\n");
    exit(EXIT_FAILURE);
}

void
insertion_sort(Record records[], int num_records)
{
    fprintf(stderr, "insertion_sort(): NYI\n");
    exit(EXIT_FAILURE);
}

int
compare_records(Record *a, Record *b)
{
   number_of_comparisons++; 
    return a->key - b->key;
}

void
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
int
test_if_sorted(Record records[], int num_records)
{

    int i = 0;

    for (i = 0; i < num_records - 1; i++)
    {
        if (records[i + 1].key < records[i].key)
        {
            return 0;
        }
    }

    return 1;
}

int
test_if_stable(Record records[], int num_records)
{
        int i;
        
        for (i = 1; i < num_records; i++)
        {
            if (records[i].key == records[i - 1].key)
            {
                if (records[i].value <= records[i-1].value)
                {
                    return 0;
                }
            }
        }

        return 1;
}

void
print_records(Record records[], int num_records)
{

    int i;

    printf("Key\tValue\n");
    for (i = 0; i < num_records; i++)
    {
        printf("%d\t%d\n", records[i].key, records[i].value);
    }
}

