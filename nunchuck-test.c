#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "nunchuck.h"

static void printDouble(void *p)
{
    fprintf(stderr, "[printdoub] mem_addr:[%llx]  data:[%f]\n", (long long) p, *((double*)p));
}

static void die(const char *message)
{
    perror(message);
    exit(1); 
}

int main() 
{
    double a[] = { 1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0 };
    fprintf(stderr, "[test] start of array [%lld]\n", (long long) a);
    int n = sizeof(a) / sizeof(a[0]);

    int i;

    // initialize list
    nc_list_t list;
    fprintf(stderr, "[test] init\n");
    initList(&list);

    // test addFront()
    printf("testing addFront(): ");
    for (i = 0; i < n; i++) {
	if (nc_add(&list, a+i, NC_FORE) == NULL) 
	    die("addFront() failed");
    }

    fprintf(stderr, "[test] traverse\n");
    nc_traverse(&list, &printDouble, NC_FORE);
    printf("\n");

    return 0;
}
