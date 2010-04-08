#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct entry
{	char * ligne;
	long num;
	struct entry * next;
};

int compare_entry (const void *a, const void *b)
{	return (*(struct entry * const *)b)->num - (*(struct entry * const *)a)->num;
}

int main (int nb, char ** cmde)
{
	char buf [4096];
	
	int order = 1;

	struct entry 	*first, 
			*current,
			**tab,
			**last = &first;

	long  tot = 0,
		n = 0,
		i;

	for (i=1 ; i<nb ; i++) {
	    if (cmde[i][0] == '-') {
		switch (cmde[i][1]) {
		    case 'r':
			order = 0;
			break;
		    default:
			break;
		}
	    }
	}

	while (fgets (buf, 4096, stdin) != NULL)
	{
		if ( (*last = (struct entry *) malloc (sizeof (struct entry))) == NULL )
		{	fprintf (stderr, "un malloc a retourne NULL : j'abrege ! \n");
			return 1;
		}
		if ( ((*last)->ligne = (char *) malloc (strlen (buf)+1)) == NULL )
		{	fprintf (stderr, "un malloc a retourne NULL : j'abrege ! \n");
			return 1;
		}
		strcpy ((*last)->ligne, buf);
		(*last)->num = atol (buf);
		tot += (*last)->num;
		n++;
		last = &((*last)->next);
	}

	*last = NULL;

	if (order)
	{	tab = (struct entry **) malloc (n * sizeof (struct entry *));	
		if (tab == NULL)
		{	fprintf (stderr, "ca semble incroyable mais je n'ai pas assez de memoire pour trier...\n");
			order = 0;
		}
		i = 0;
	}

	if (order)
	{	if (tot != 0)
			printf ("        %3ld %% %7ld %s (%ld items)\n", (100 * tot)/tot, tot, "TOTAL", n);
		current = first;
		while (current != NULL)
		{	tab [i] = current;
			i ++;
			current = current-> next;
		}

		qsort (tab, n, sizeof (struct entry *), compare_entry);

		for (i=0 ; i<n ; i++)
			printf ("%7ld %3ld %% %s", i+1, (100 * tab[i]->num)/tot, tab[i]->ligne);
	}
	else
	{	if (tot != 0)
			printf ("        %3ld %% %7ld %s (%ld items)\n", (100 * tot)/tot, tot, "TOTAL", n);
		current = first;
		i = 1;
		while (current != NULL)
		{	printf ("%7ld %3ld %% %s", i, (100 * current->num)/tot, current->ligne);
			current = current-> next;
			i++;
		}	
	}

	return 0;
}

 
