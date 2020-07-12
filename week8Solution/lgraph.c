// lgraph.c
// linked-list implementation of graphs
// aug 09
// aug 10 
// awirth
//sep 08 udaya

#include <stdio.h>
#include <stdlib.h>

#include "misc.h"
#include "graph.h"
#include "smalloc.h"

#define MAX 1000
#define UNSET	(-1)
#define UNUSED	'?'
#define TREE	't'
#define BACK	'b'
#define CROSS	'c'
#define FORWARD 'f'

//#define DEBUG

#ifdef DEBUG
#define DEBUG_PRINT(x) fprintf x
#else
#define DEBUG_PRINT(x)  /*nothing*/
#endif

enum Color{red, black, none};	// colors for bipartite

typedef struct eedge{
	int v;			// destination
	int w;			// weight
	char type;		// type--tree/back (if directed: cross/forward)
	struct eedge *partner;	// for undirected graph: points to v->u
				// as we need both directions of edge
	struct eedge *next;	// next edge in adjacency list
} edge;

typedef struct linkgraph{
	edge *al[MAX];	// array of adjacency lists
	int n;		// number of vertices
	bool directed;	// whether directed
	int pre[MAX];	// stores pre-visit numbers
	int post[MAX];	// stores post-visit numbers
	int component[MAX]; // stores the connected component number
	int color[MAX];	// stores color for bipartite check
	bool bipartite;	// check if bipartite
} lgraph;

static int clock;	// counts number of DFS pre & post visits
static int compnum;	// counts number of components seen
static enum Color color;	// which color are we up to: bipartite

void
previsit(lgraph *G, int v);

void
postvisit(lgraph *G, int v);

void
explore(lgraph *G, int v);

void
print_dfs_results(lgraph *G);

void
initialize_search(lgraph *G);

// returns a graph that is the reverse of this graph
void *
reverse(void *gp)
{
	int u;
	lgraph *G = (lgraph *) gp;
	lgraph *H = (lgraph *) make_empty(); // reverse graph

	edge *now;
	edge *new;

	H->n = G->n;		// same number of nodes and directionality
	H->directed = G->directed;

	// just a double loop
	// over each vertex
	for(u=G->n-1; u>=0; u--){
		// then each edge
		for(now = G->al[u]->next; now!=NULL; now=now->next){
			// or could call insert((void *) H,now->v,u,now->w);
			new = (edge *) smalloc(sizeof(*new));
			new->v = u;
			new->next = H->al[now->v];
			H->al[now->v] = new;
			// set same weight
			new->w = now->w;
		}
	}

	return (void *) H;
}

// make_empty, returns a graph structure, with no information set
void *
make_empty(void)
{
	lgraph *G;
	int u;
	
	G = (lgraph *) smalloc(sizeof(*G));
	// set up adjacency lists:
	for(u = 0; u < MAX; u++){
		// create dummy head node for each potential node
		G->al[u] = (edge *) smalloc(sizeof(*G->al[u]));
		G->al[u]->next = NULL;
	}

	return (void *) G;
}

// the fundamental recursive step in the DFS
// removed visited array

void
explore(lgraph *G, int u)
{
	int v;
	edge *now;

	// do previsit step
	previsit(G,u);

	// starting at node AFTER dummy head node....
	// follow each edge
	for(now = G->al[u]->next; now!=NULL; now=now->next){
		v = now->v;
		// if directed graph:
		if(G->directed){
			// is v finished?
			if(G->post[v] == UNSET){
				// have we been to v before?
				if(G->pre[v] == UNSET){
					// NEW node, keep exploring!
					now->type = TREE;
					explore(G,v);
				} else {
					now->type = BACK;
				}
			} else 	{	
				// v finished, so forward or cross edge"
				// started after u?
				if(G->pre[v] > G->pre[u]){
					now->type = FORWARD;
				} else {
					now->type = CROSS;
				}
			}
		} else {
			// in undirected graph, we might traverse same edge
			// as u->v and v->u: we want to avoid this....
			// so first check that edge type is UNUSUED....
			// [see below]
			if(now->type == UNUSED){
				// have we been to v before?
				if(G->pre[v] == UNSET){
					now->type = TREE;

					// [see above]
					// ..and set the partner edge type
					now->partner->type = TREE;

					// if NEW VERTEX: keep exploring!
					explore(G,v);
				} else {
					// check for bipartite
					if(color != G->color[v]){
						G->bipartite = FALSE;
					}
					now->type = BACK;
					// [see above]
					// ..and set the partner edge type
					now->partner->type = BACK;
				}
			}
		}
	}
	postvisit(G,u);
}

// initializes variables for DFS
void
initialize_search(lgraph *G)
{
	clock = 0;
	compnum = 0;
	edge *now;
	int u;

	G->bipartite = TRUE;	// assume true unless otherwise found
	for(u=0;u<G->n;u++){
		// clear pre and postorder numbers and component numbers
		G->pre[u] = UNSET;
		G->post[u]= UNSET;
		G->component[u] = UNSET;
		G->color[u] = none;
		// make it clear that each edge is unexplored
		for(now=G->al[u]->next; now!=NULL; now=now->next){
			now->type = UNUSED;
		}
	}
}

// main dfs function:
void
dfs(void *gp)
{
	lgraph *G = (lgraph *) gp;
	
	int u;

	initialize_search(G);

	// for each node
	for(u=0;u < G->n;u++){
		// if not yet visited
		if(G->pre[u] == UNSET){
			// explore from there
			explore(G,u);
			// in undirected graph, increment component number
			if(!G->directed){
				compnum++;
			}
		}
	}
	print_dfs_results(G);
}

void
print_dfs_results(lgraph *G)
{
	int u;
	edge *now;

	if(!G->directed){
		if(G->bipartite){
			printf("Graph is bipartite\n");
		} else {
			printf("Graph is not bipartite\n");
		}
	}
	for(u=0;u<G->n;u++){
		printf("%8d: pre %8d post %8d",u,G->pre[u],G->post[u]);
		if(!G->directed){
 			printf(" undirected component %8d\n", G->component[u]);
		} else {
			printf("\n");
		}
	}
	for(u=0;u<G->n;u++){
		for(now=G->al[u]->next; now!=NULL; now=now->next){
				printf("%4d -> %4d type %c\n",
					u,now->v,now->type);
		}
	}
}

// sets the size parameter of the graph (maybe read from standard input
// originally).
void
set_size(void *gp, int n)
{
	lgraph *G = (lgraph *) gp;

	if(n > MAX){
		fprintf(stderr,"Graph cannot have %d nodes; maximum allowed is "			"%d.\n",n,MAX);
		exit(EXIT_FAILURE);
	}
	G->n = n;
}

// set whether directed graph
void
set_directed(void *gp, bool directed)
{
	lgraph *G = (lgraph *) gp;
	G->directed = directed;
}

// adds the edge (from the input) to the graph
void
insert(void *gp, int u, int v, int w)
{
	lgraph *G = (lgraph *) gp;
	edge *e1,*e2;

	if(u > G->n || v > G-> n){
		fprintf(stderr,"Cannot have edge %d -> %d when n is %d.\n",
			u,v,G->n);
		exit(EXIT_FAILURE);
	}

	// makes the node for the new edge
	e1 = (edge *) smalloc(sizeof(*e1));
	e1->v = v;
	e1->w = w;

	// adds the node to the START of the list; this is easy to do
	// but might mess up the order
	e1->next = G->al[u]->next;
	G->al[u]->next = e1;


	// if undirected graph, does the same in reverse
	if(!G->directed){
		e2 = (edge *) smalloc(sizeof(*e2));
		e2->v = u;
		e2->w = w;

		e2->next = G->al[v]->next;
		G->al[v]->next = e2;

		// set up partner relationships
		e2->partner = e1;
		e1->partner = e2;
	}
}

// carries out previsit steps
void
previsit(lgraph *G, int v)
{
	G->pre[v] = clock;
	if(!G->directed){
		G->component[v] = compnum; // only correct for Undirected graph
	}
	clock++;

	// bipartite code
	G->color[v] = color;
	if(color == red){
		color = black;
	} else {
		color = red;
	}
}

// carries out postvisit steps
void
postvisit(lgraph *G, int v)
{
	G->post[v] = clock;
	clock++;
}
