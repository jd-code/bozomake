#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main (int nb, char ** argv)
{
	long count = 0, order = 0;
	int ordered = 0;
	char buf1 [4096],
	     buf2 [4096],
	     *p, *q, *r;
	p = buf1, q = buf2;
	*p = 0;

	{	int i;
		for (i=1 ; i<nb ; i++)
		{	if (*argv[i] == '-')
			switch (argv[i][1])
			{	case 'n':
				case 'N':
					ordered = 1;
					break;
			}
		}
	}

	while (fgets (q, 4096, stdin) != NULL)
	{	if (strcmp (q,p) != 0)
		{	
			if (count) 
			{	if (ordered)
				{	printf ("%7ld %7ld %s", order, count, p);
					order ++;
				}
				else
					printf ("%7ld %s", count, p);
			}
			r = p;
			p = q;
			q = r;
		
			count = 1;
		}
		else
			count ++;
	}
	if (count) 
	{	if (ordered)
		{	printf ("%7ld %7ld %s", order, count, p);
			order ++;
		}
		else
			printf ("%7ld %s", count, p);
	}

	return 0;
}
 
