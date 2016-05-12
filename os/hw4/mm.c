#include "mm.h"

#define NALLOC 1024 /* minimum units to request */

typedef long Align; /* for alignment to long boundary */

/* block header */
union header
{ 
	struct
	{
		union header *ptr; /* next block if on free list */
		size_t size; /* size of this block */
	} s;

	Align x; /* force alignment of blocks, size of union is same as long */
};

typedef union header Header;

static Header base; /* empty list to get started */
static Header *freep = NULL; /* start of free list */

/* morecore: ask system for more memory */
static Header *morecore(size_t nu)
{
	char *cp, *sbrk(int);
	Header *up;
	
	if (nu < NALLOC)
		nu = NALLOC;
	
	cp = sbrk(nu * sizeof(Header));
	
	/* no space at all */
	if (cp == (char *) -1) 
		return NULL;
	
	/* make up equal to cp and set size */
	up = (Header *) cp;
	up->s.size = nu;
	
	/* put up into free list */
	myfree((void *)(up+1));
	
	return freep;
}

/* mymalloc: general-purpose storage allocator */
void *mymalloc(size_t size)
{
	/* p: current pointer of free list, prevp: prev pointer of free list */
	Header *p, *prevp;
	Header *morecore(size_t);
	
	size_t nunits; /* a number of Header we need to get */
	
	nunits = (size + sizeof(Header)-1) / sizeof(Header) + 1; /* round up with integer division */

	/* no free list yet */
	if ((prevp = freep) == NULL)
	{ 
		base.s.ptr = freep = prevp = &base;
		base.s.size = 0;
	}

	for (p = prevp->s.ptr ; ; prevp = p, p = p->s.ptr)
	{
		/* big enough */
		if(p->s.size >= nunits)
		{
			if (p->s.size == nunits) /* exactly */
			{
				prevp->s.ptr = p->s.ptr;
			}
			else /* allocate tail end */
			{
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
	
			freep = prevp; /*  */
			return (void *)(p+1);
		}

		/* wrapped around free list */
		if (p == freep)
		{
			if ((p = morecore(nunits)) == NULL) /* none left */
				return NULL;
		}
	}
}

/* free: put block ap in free list */
void myfree(void *ap)
{
	Header *bp, *p;

	bp = (Header *)ap - 1;

	/* point to block header */
	for (p = freep ; !(bp > p && bp < p->s.ptr) ; p = p->s.ptr)
	{
		/* freed block at start or end of arena */
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break; 
	}
	
	/* join to upper nbr */
	if (bp + bp->s.size == p->s.ptr)
	{ 
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	}
	else
	{
		bp->s.ptr = p->s.ptr;
	}
	
	/* join to lower nbr */
	if (p + p->s.size == bp)
	{
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	}
	else
	{
		p->s.ptr = bp;
	}
	
	freep = p;
}

void *myrealloc(void *ptr, size_t size)
{
	Header *bp;
	size_t nunits;

	if(ptr == NULL)
		return mymalloc(size);

	bp = (Header *)ptr - 1;
	nunits = (size + sizeof(Header) - 1) / sizeof(Header) + 1;

	if(bp->s.size >= nunits)
		return ptr;

	void *np = mymalloc(size);

	if(np == NULL)
		return NULL;

	//size_t tsize = sizeof(ptr);
	//printf("%d\n%d\n%d\n", (int)tsize, (int)(bp->s.size * sizeof(Header)), (int)sizeof(Header));

	memcpy(np, ptr, (bp->s.size - 1) * sizeof(Header));
	
	myfree(ptr);

	return np;
}

void *mycalloc(size_t nmemb, size_t size)
{
	size_t all = nmemb * size;
	void *np = mymalloc(all);
	if(np == NULL)
		return NULL;
	return np;
}

void trace_free_memory()
{
	Header *trace = freep->s.ptr;
	int counter = 1;
	int memory_size = (int)(freep->s.size);

	while(trace != freep)
	{
		counter++;
		memory_size += (int)(trace->s.size);
		/*if(trace == &base)
			printf("&base -> ");
		else
			printf("block -> ");*/
		trace = trace->s.ptr;
	}

	printf("free list has %d block of memory of size %d\n\n", counter, (int)(memory_size * sizeof(Header)));
}