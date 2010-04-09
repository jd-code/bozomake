/* 
 * $Id$
 * Bozomake Copyright (C) 1997,2002,2003 Cristelle Barillon & Jean-Daniel Pauget
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
 
