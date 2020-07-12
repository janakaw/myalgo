/*
** COMP20003  Algorithms and Data Structures
** Sorting Algorithms
** 
** file: data_gen.c
** author: juliensf
** 
** Usage: data_gen <num> [limit]
**
** Generates 'num' pseudorandom numbers and writes them to stdout,
** one per line.  If the argument 'limit' is supplied then all the
** numbers are generated mod limit.
**
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

static void usage(const char *);

int main(int argc, char **argv) {

	int i;
	int num_to_generate;
	int limit = INT_MAX;	
	
	if (argc != 2 && argc != 3)
	{
		usage(argv[0]);
	}
	
	if (sscanf(argv[1], "%d", &num_to_generate) != 1)
	{
		usage(argv[0]);
	}

	if (argc == 3)
	{
		if (sscanf(argv[2], "%d", &limit) != 1)
		{
			usage(argv[0]);
		}
	}		
	
	srand((unsigned int)time(NULL));	

	for (i = 0; i < num_to_generate; i++)
	{
		printf("%d\n", rand() % limit);
	}	

	return 0;
}

static void
usage(const char *prog_name)
{
	fprintf(stderr, "Usage: %s <num> [limit]\n", prog_name);
	exit(EXIT_FAILURE);
}
