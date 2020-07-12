// basic priority queue header
// awirth
// sep 09

void *
make_empty_pq(void);

int
insert_pq(void *ds, int k, int p);

int
delete_min_pq(void *ds, int *k, int *p);

int
decrease_priority_pq(void *ds, int k, int p);

int
find_min_pq(void *ds, int *k, int *p);

int
delete_pq(void *ds, int k);
