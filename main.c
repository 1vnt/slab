#include <stdint.h>
#include <stdio.h>
#include "slab.h"
#include <assert.h>
#include <string.h>
#include <unistd.h>

struct foo {
	int one;
	int two;
	int three;
	uint64_t four;
};

struct large {
	char buf[512];
};

int main()
{
	kmem_init();

	kmem_cache_t *cp = kmem_cache_create("small_test", sizeof(struct foo),
					     0, NULL, NULL, NULL, 0);
	struct foo *obj[250];
	for (int i = 0; i < 250; i++) {
		obj[i] = kmem_cache_alloc(cp, 0);
		memset(obj[i], 0xA1, sizeof(struct foo));
	}

	for (int i = 0; i < 250; i++) {
		kmem_cache_free(cp, obj[i]);
	}

	assert(kmem_cache_destroy(cp) == 0);

	kmem_cache_t *lcp = kmem_cache_create(
		"large_test", sizeof(struct large), 0, NULL, NULL, NULL, 0);
	struct large *lobj[20];
	for (int i = 0; i < 20; i++) {
		struct large *lp = kmem_cache_alloc(lcp, 0);
		assert(lp != NULL);
		memset(lp, (i << 4) | i, sizeof(struct large));
		lobj[i] = lp;
	}
	for (int i = 0; i < 20; i++) {
		kmem_cache_free(lcp, lobj[i]);
	}

	assert(kmem_cache_destroy(lcp) == 0);

	kmem_cleanup();

	return 0;
}
