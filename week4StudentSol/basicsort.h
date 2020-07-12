/*
** COMP20003 Algorithms and Data Structures
** Workshop Week4 Exercise: Elementary Sorting Algorithms
*/
/*
** The records we will be sorting.  The 'key' is the part
** read in from stdin.  It is the part that governs the
** sorting process.  The 'value' field is assigned by
** the read_records() function.  We use it to test for
** stability.
*/
typedef struct {
    int key;
    int value;
} Record;

/* This is for making some experiments with the sorting function */
int number_of_comparisons;



/*
** These four functions implement the four sorting algorithms.
** Only bubble_sort() is currently implemented.
*/
void bubble_sort(Record records[],    int num_records);
void selection_sort(Record records[], int num_records);
void insertion_sort(Record records[], int num_records);

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
/* int number_of_comparisons = 0; */

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

/*
** Print out a usage message to stderr and aborts execution.
*/
void usage(const char *prog_name);

