// qtest.c

// awirth
// aug 09
// modified by phjlee

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "smalloc.h"
#include "pq.h"
#include "dump.h"

#define STRMAX 100

int
main(int argc, char *argv[])
{
	char s[STRMAX+1];
	char c;
  int k, p;
  void *ds;

  ds = make_empty_pq();
	
  printf("To insert             : 1 key priority\n");
  printf("To delete min         : 2\n");
  printf("To decrease prioirity : 3 key prioirity\n");
  printf("To find min           : 4\n");
  printf("To delete             : 5 key\n");

	while(fgets(s,STRMAX,stdin) != NULL){
		switch(s[0]){
			case '1':
        sscanf(s, "%c %d %d", &c, &k, &p);
        insert_pq(ds, k, p);
        dump_heap(ds);
				break;
      case '2':  
        delete_min_pq(ds, &k, &p);
        printf("Key: %d, Prioirity: %d deleted\n", k, p);
        dump_heap(ds);
				break;
      case '3':
        sscanf(s, "%c %d %d", &c, &k, &p);
        decrease_priority_pq(ds, k, p);
        dump_heap(ds);
        break;
      case '4':
        find_min_pq(ds, &k, &p);
        printf("Key: %d, Prioirity: %d found\n", k, p);
        break;
      case '5':  
        sscanf(s, "%c %d", &c, &k);
        delete_pq(ds, k);
        dump_heap(ds);
        break;
			default:
				printf("Didn't understand line: %s\n",s);
				break;
		}
	}
}
