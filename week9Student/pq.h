// basic priority queue header
// awirth
// sep 09

void *
make_empty_pq(void);

void
insert_pq(void *ds, int i, int p);

int
delete_min_pq(void *ds, int *i, int *p);

int
decrease_priority_pq(void *ds, int i, int p);
