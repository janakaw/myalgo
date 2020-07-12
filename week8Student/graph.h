// graph.h
// header file for graphs

// awirth
// aug 09

void
dfs(void *gp);

//void
//scc(void *gp);

void *
make_empty(void);

void
set_size(void *gp, int n);

void
set_directed(void *gp, bool directed);

void
insert(void *gp, int u, int v, int w);

void *
reverse(void *gp);

//int
//hascycle(void *gp, int i, int j);

int
cycle_between(void *gp, int u, int v);
