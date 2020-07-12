// gtest.c
// testing the graph functions
// awirth
// aug 09
// aug 10
// apr 11

#include <stdio.h>
#include "misc.h"
#include "graph.h"

#define NARGS 1
#define MAXSTR 1000

int
read_input(int argc, char *argv[], void *gp);


int
main(int argc, char *argv[])
{
	void *gp,*gpr;
	gp = make_empty();


	read_input(argc,argv,gp);
	gpr = reverse(gp);
	dfs(gp);
	dfs(gpr);

}

// reads the input from stdin and stores in the (dynamically-allocated)
// array of records.
// Note that pointers to n and rs are passed in, as these are set in this
// function.

int
read_input(int argc, char *argv[], void *gp)
{
	char s[MAXSTR];
	int i,j,w;
	int n;

	if(argc != NARGS){
		fprintf(stderr,"There should be %d argument(s) to the %s"
			" program.\n", NARGS, argv[0]);
		return FALSE;
	}

	// determine size of graph
	fgets(s,MAXSTR-1,stdin);	// safer than gets()
	while(s[0] == '#'){
						// comment line
		fgets(s,MAXSTR-1,stdin);	// safer than gets()
	}
	sscanf(s,"%d",&n);
	set_size(gp,n);

	// determine whether graph is directed
	fgets(s,MAXSTR-1,stdin);	// safer than gets()
	while(s[0] == '#'){
						// comment line
		fgets(s,MAXSTR-1,stdin);	// safer than gets()
	}
	if(s[0] == 'u'){
		set_directed(gp,FALSE);
	} else {
		set_directed(gp,TRUE);
	}
	
	// read in graph itself
	while(fgets(s,MAXSTR-1,stdin) != NULL){	// read in each line
		if(s[0] == '#'){
			continue;		// comment line
		}
		sscanf(s,"%d %d %d",&i,&j,&w);	// scan node numbers and	
						// the weight of edge
		insert(gp,i,j,w);
	}
	return TRUE;
}
