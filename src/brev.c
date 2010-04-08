/*
 *  $Id$
 * 
 *  brev perfoms a left to righ conversion of a text file.
 *  it is intended to supply the 'rev' functionnality when it is missing,
 *  though it doesn't support multi-bytes chars nor locales, and probably more.
 *
 *  jd - 27-04-2004 jdrev@disjunkt.com
 *
 */


#include <stdio.h>
#include <stdlib.h>

typedef struct STFlushBuf {
    int first;
    int last;
    struct STFlushBuf * previous;
    char buf[1024];
} FlushBuf;

void flushit (FlushBuf * fb)
{
    int k;
    FlushBuf * previous;
    if (fb == NULL) {
	fprintf (stderr, "WARNING: flushit got a null FlushBuf\n");
	return;
    }
    // JDJDJDJD the following is uggly, a left to right conversion
    // of the buffer should be performed, then a BLOCK write, instead of this crap
    for (k=fb->last ; k>=fb->first ; k--)
	printf ("%c", fb->buf[k]);
    // end of crap
    previous = fb->previous;
    free (fb);
    if (previous != NULL)
	flushit (previous);
}

void brev (FILE * f,FlushBuf * previous)
{
    FlushBuf * cur;
    char *buf, *p;
    int nbread, i, j;

    cur = (FlushBuf *) malloc (sizeof (FlushBuf));
    if (cur == NULL) {
	fprintf (stderr, "brev: ERROR: could not allocate 1024 bytes\n");
	return;
    }

    buf = &cur->buf[0];
    
    nbread = fread (buf, 1, 1024, f);
    i=0;
    p=&buf[0];
    while (i<nbread) {
	j=i;
	while ((i<nbread) && (*p!=10) && (*p!=13)) i++, p++;
	if (i == nbread) {
	    cur->first=j;
	    cur->last=i-1;
	    cur->previous = previous;
	    brev (f, cur);
	} else {
	    int k;
    // JDJDJDJD the following is uggly, a left to right conversion
    // of the buffer should be performed, then a BLOCK write, instead of this crap
	    for (k=i-1 ; k>=j ; k--)
		printf ("%c", buf[k]);
    // end of crap
	    if (previous != NULL) {
		flushit (previous);
		previous = NULL;
	    }
	    printf ("%c", *p);
	    i++, p++;
	    if (i == nbread) {
		free (cur);
		brev (f, NULL);
	    }
	}
    }
}

int main (int nb, char ** cmde)
{
    int i;

    if (nb == 1)
	brev (stdin, NULL);
    else for (i=1 ; i<nb ; i++) {
	FILE *f = fopen (cmde[i], "r");
	if (f != NULL) {
	    brev (f, NULL);
	    fclose (f);
	} else {
	    fprintf (stderr, "could not open %s for reading\n", cmde[i]);
	}
    }
    return 0;
}
