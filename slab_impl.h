#pragma once

#include <sys/queue.h>
#include <stdlib.h>

typedef struct kmem_cache kmem_cache_t;
typedef struct kmem_slab kmem_slab_t;

typedef struct kmem_bufctl {
	SLIST_ENTRY(kmem_bufctl) entry;
} kmem_bufctl_t;

typedef struct kmem_large_bufctl {
	kmem_bufctl_t bufctl;
	kmem_slab_t *slab;
	void *base;
} kmem_large_bufctl_t;

typedef struct kmem_slab {
	SLIST_HEAD(freelist, kmem_bufctl) freelist;
	LIST_ENTRY(kmem_slab) entry;
	size_t refcnt;
	kmem_cache_t *parent_cache;
	void *base;
} kmem_slab_t;

#define KMEM_NAME_MAX 64

typedef struct kmem_cache {
	char name[KMEM_NAME_MAX + 1];
	size_t slabcap;
	size_t align;
	size_t chunksize;
	size_t bufsize;
	size_t slabsize;

	int (*constructor)(void *, void *);
	void (*destructor)(void *, void *);
	void *ctx;

	SLIST_HEAD(buflist, kmem_bufctl) buflist;
	LIST_HEAD(slablist, kmem_slab) slablist;
	LIST_HEAD(full_slablist, kmem_slab) full_slablist;
} kmem_cache_t;
