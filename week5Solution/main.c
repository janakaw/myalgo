/*
main.c

testing for merge sort

gocer, August 2011
 */

#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "merge.h"


int main(int argc, char **argv) {
	FILE *fp;
	int array[20], array2[20];
	int counter=0, val;
	fp = safe_fopen(argv[1], "r");
	while (fscanf(fp, "%d", &val) != EOF) {
		array[counter]=val;
		array2[counter]=val;
		counter++;
	}

	int i=0;
	printf("The original list is :\n ");
	while(i<counter){
		printf("%d ",array[i]);
		i++;
	}
	printf("\n");

	merge_sort_array(array,counter);
	merge_sort_list(array2,counter);

	i=0;
	printf("The list sorted using merge sort with array is :\n ");
	while(i<counter){
		printf("%d ",array[i]);
		i++;
	}

	printf("\n");

	i=0;
	printf("The list sorted using merge sort with linked list is :\n ");
	while(i<counter){
		printf("%d ",array2[i]);
		i++;
	}
	printf("\n");

	return 1;
}

