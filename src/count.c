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
 
