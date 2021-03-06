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
#define _LARGEFILE64_SOURCE

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define BSIZE 1024

#ifdef USELSEEK64

#define BIGOFF_T off64_t
#define BIGLSEEK lseek64
	/* JDJDJDJD one should check this one is bound to lseek64 ??? */
#define BIGO_LARGEFILE O_LARGEFILE

#else	/* ios misses lseek64 or equivalent ??? */

#define BIGOFF_T off_t
#define BIGLSEEK lseek
#define BIGO_LARGEFILE 0

#endif	/* USELSEEK64 */

typedef struct STFlushLBuf {
    struct STFlushLBuf * next,
		       * prev;
    char buf[BSIZE];
    int cur;
    int nbeol;
} FlushLBuf;

int nmalloc = 0;
int nfree = 0;
long long nblignes = -1;

void freeallbuf (FlushLBuf *b) {
    FlushLBuf *next;
    while (b != NULL) {
	next = b->next;
	free (b);
	b = next;
	nfree ++;
    }
}

void flush_from_end (FlushLBuf *b);

void flush (FlushLBuf *b, int p) {
    while (b != NULL) {
	FlushLBuf *temp = b->next;
	int size = b->cur - p;
	int size_out = 0;

	while (size > 0) {
	    ssize_t l = write (1, b->buf+p+size_out, size);
	    if (l != -1) {
		size_out += l;
		size -= l;
	    } else {
		fprintf (stderr, "could not output %d byte ??\n", size);
		return;
	    }
	}
	if (p==0) {
	    free (b);
	    nfree ++;
	}
	    
	b = temp;
	p = 0;
    }
}

void buftailrev (int fd) {
    size_t nbread = 0;
    long long toteol = 0;
    FlushLBuf *first = NULL,
	      *prev = NULL,
	      *b = NULL;

    do {
	int i;

	b = (FlushLBuf *) malloc (sizeof(FlushLBuf));
	if (b == NULL) {
	    fprintf (stderr, "could not allocate about %d bytes ??\n", (int)sizeof(FlushLBuf));
	    freeallbuf (first);
	    return;
	}
	nmalloc ++;
	b->nbeol = 0;
	b->next = NULL;
	if (first == NULL)
	    first = b;
	if (prev != NULL) {
	    prev->next = b;
	}
	b->prev = prev;

	nbread = read (fd, b->buf, BSIZE);
	b->cur = nbread;

	for (i=0 ; i<nbread ; i++)
	    if ((b->buf[i] == 10) || (b->buf[i] == 13))
		b->nbeol ++;
	
	toteol += b->nbeol;

	if (nblignes > 0) {
	    while ((first != NULL) && (toteol - first->nbeol > nblignes)) {
		FlushLBuf *temp = first;
		toteol -= first->nbeol;
		first = first->next;
		free (temp);
		nfree ++;
	    }
	}

	prev = b;
    } while (nbread > 0);

    flush_from_end (b);

    // freeallbuf (first);
}

void tailrev (int fd) {
    int i;
    long long lignesflushed = 0;
    FlushLBuf *next = NULL;
    BIGOFF_T o = BIGLSEEK (fd, 0, SEEK_END);
    if (o == (BIGOFF_T)-1) {
	fprintf (stderr, "could not seek to end of file ??\n");
	return;
    }
    while (o > 0) {
	int l;
	BIGOFF_T size_to_read;

	FlushLBuf *b = (FlushLBuf *) malloc (sizeof(FlushLBuf));
	if (b == NULL) {
	    fprintf (stderr, "could not allocate about %d bytes ??\n", (int)sizeof(FlushLBuf));
	    freeallbuf (next);
	    return;
	}
	nmalloc ++;
	b->next = next;
	if (o < BSIZE)
	    size_to_read = o;
	else
	    size_to_read = BSIZE;
	b->cur = size_to_read;

	o = BIGLSEEK (fd, -size_to_read, SEEK_CUR);
	if (o == (BIGOFF_T)-1) {
	    fprintf (stderr, "could not seek back %d bytes in file ??\n", (int)size_to_read);
	    freeallbuf (b);
	    return;
	}

	l = read (fd, (void *)(b->buf), size_to_read);
	if (l != size_to_read) {
	    fprintf (stderr, "could not read %d bytes in file ??\n", (int)size_to_read);
	    freeallbuf (b);
	    return;
	}

	o = BIGLSEEK (fd, -size_to_read, SEEK_CUR);
	if (o == (BIGOFF_T)-1) {
	    fprintf (stderr, "could not seek back %d bytes in file ??\n", (int)size_to_read);
	    freeallbuf (b);
	    return;
	}

	next = b;
	for (i=size_to_read-1 ; i>=0 ; i--) {
	    if ((b->buf[i] == 10) || (b->buf[i] == 13)) {
		if (nblignes > 0) {
		    if (lignesflushed <= nblignes) {
			lignesflushed ++;
			flush (b, i+1);
		    } else {
			freeallbuf (b);
			return;
		    }
		} else
		    flush (b, i+1);
		b->next = NULL;
		b->cur = i+1;
	    }
	}

	if (o == 0) flush (b, 0);
    }
}

void flush_from_end (FlushLBuf *b)
{
    int i;
    long long lignesflushed = 0;

    while (b != NULL) {
	for (i=b->cur-1 ; i>=0 ; i--) {
	    if ((b->buf[i] == 10) || (b->buf[i] == 13)) {
		if (nblignes > 0) {
		    if (lignesflushed <= nblignes) {
			lignesflushed ++;
			flush (b, i+1);
		    } else {
			return;
		    }
		} else
		    flush (b, i+1);
		b->next = NULL;
		b->cur = i+1;
	    }
	}
	if (b->prev == NULL) flush (b, 0);
	b = b->prev;
    }
}


int main (int nb, char ** cmde) {
    int i;
    int stillarg = 1;
    int nbfiles = 0;

    for (i=1 ; i<nb ; i++) {
	if (stillarg) {
	    if (cmde[i][0] == '-') {
		if (strcmp ("--", cmde[i]) == 0) {
		    stillarg = 0;
		    continue;
		} else {
		    nblignes = atoll (cmde[1] + 1);
		    continue;
		}
	    }
	}

	nbfiles ++;
	int fd = open (cmde[i], BIGO_LARGEFILE);
	if (fd != -1) {
	    tailrev (fd);
	    close (fd);
	} else {
	    fprintf (stderr, "could not open %s for reading\n", cmde[i]);
	}
    }
    if (nbfiles == 0) {
	buftailrev (0);
    }

//    fprintf (stderr, "malloc = %d, free = %d\n", nmalloc, nfree);

    return 0;
}

