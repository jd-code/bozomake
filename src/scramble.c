#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MABIGLINE 4096
#define MAXNB 1024

char *lig[MAXNB];
int o[MAXNB];

int
main (void)
{
  char buf[MABIGLINE];
  int i, n, raison = 1;

  srand ((unsigned int) time (NULL));

  while (raison == 1)
    {
      raison = 0;
      n = 0;

      while ((n < MAXNB) && (fgets (buf, MABIGLINE, stdin) != NULL))
	{
	  if ((lig[n] = (char *) malloc (strlen (buf) + 1)) != NULL)
	    {
	      strcpy (lig[n], buf);
	      n++;
	    }
	  else
	    {
	      raison = 1;
	      break;
	    }
	}

      for (i = 0; i < n; i++)
	o[i] = i;

      for (i = 0; i < n; i++)
	{
	  int temp, s;

	  s = (int) ((double) (n - 1) * rand () / (RAND_MAX + 1.0));
	  temp = o[i];
	  o[i] = o[s];
	  o[s] = temp;
	}
      for (i = 0; i < n; i++)
	{
	  fputs (lig[o[i]], stdout);
	  free (lig[o[i]]);
	}
    }
  return 0;
}
