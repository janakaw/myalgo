// main.c
// tests out the insert and find functions of a data structure
// awirth
// aug 09


#include <stdio.h>
#include <string.h>
#include "record.h"
#include "data.h"

#define MAX 1000
#define LENGTH 8

int
main(int argc, char * argv[])
{

	// some test data
	/*
		{{3,"three"},{78,"seventy-eight"},{5,"five"},
		{7, "seven"}, {32, "thirty-two"}, {56, "fifty-six"},
		{24, "twenty-four"}, {11, "eleven"}};
	*/

	char s[2*MAXSTR]; // should really make sure last position is zeroed.
	record rs[MAX];
	int i,n;
	void *ds;	// void *: because we don't care how implemented
	record *found;

	for(n=0;fgets(s,2*MAXSTR,stdin)!=NULL;n++){
		if(n==MAX){
			fprintf(stderr,"Too many entries now. Only %d allowed"
				"\n",MAX);
		}
		sscanf(s,"%d %s",&rs[n].key,rs[n].value);
	}

	ds = make_empty();

	// set up and insert the records
	for(i=0; i < n; i++){
		if(!insert(ds, rs[i])){
			printf("TVP says FULL!\n");
			return 1;
		}
	}
	if(!destroy(ds,32)){
		printf("32 isn't there. bad magic number\n");
	}
	// test deletion


	// see what we can find
	for(i=n-1; i > -1 ; i--){
		found = find(ds,rs[i].key);
		if(found == NULL){
			printf("Couldn't find %d\n", rs[i].key);
		} else {
                	printf("Found %20d %s\n",found->key,found->value);
		}
	}

}
