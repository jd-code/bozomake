/* 
 * $Id$
 * Bozomake Copyright (C) 2002,2003 Cristelle Barillon & Jean-Daniel Pauget
 * A whole set of building utilities
 *
 * bozomake@disjunkt.com  -  http://bozomake.disjunkt.com/
 * 
 * This file is part of Bozomake.
 * 
 * Loopsoids is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * Loopsoids is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with Loopsoids; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * 
 * you can also try the web at http://www.gnu.org/
 */
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MABIGLINE 4096
#define MAXNB 4096

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
