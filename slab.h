#pragma once

#include <stddef.h>

typedef struct kmem_cache kmem_cache_t;

void *kmem_cache_alloc(kmem_cache_t *cp, int kmflags);
void kmem_cache_free(kmem_cache_t *cp, void *obj);
int kmem_cache_destroy(kmem_cache_t *cp);
kmem_cache_t *kmem_cache_create(const char *name, size_t bufsize, size_t align,
				int (*constructor)(void *, void *),
				void (*destructor)(void *, void *), void *ctx,
				int kmflags);

void *vm_kalloc(size_t count, int flags);
void kmem_init();
void kmem_cleanup();
