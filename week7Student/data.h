// basic data structure header
// awirth
// jul 09

void *
make_empty(void);

typedef int bool;

bool
insert(void *ds,record r);

bool
destroy(void *ds, int key);


record *
find(void *ds, int key);

#define TRUE (0==0)
#define FALSE (0==1)
