#include <stdio.h>
#include <stdlib.h>

int main (int nb, char ** argv)
{
    long order = 1;
    int ordered = 1;
    char buf1 [4096],
	 buf2 [4096],
	 *p, *q;
    p = buf1, q = buf2;
    *p = 0;

    {	int i;
	for (i=1 ; i<nb ; i++)
	{   if (*argv[i] == '-')
	    switch (argv[i][1])
	    {	case '0':
		    order = 0;
		    break;
		default:
		    break;
	    }
	}
    }

    while (fgets (q, 4096, stdin) != NULL)
    {	
	if (ordered)
	{   printf ("%7ld %s", order, q);
	    order ++;
	}
	else
	    printf ("%7ld %s", order, p);
    }

    return 0;
}
 
