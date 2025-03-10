/************************************************/
/* Simple 65C02 arena allocator.                */
/* Author: Sebastian Dawid                      */
/* E-Mail: sdawid@techfak.uni-bielefeld.de      */
/************************************************/

#include <stddef.h>
#include <stdint.h>

// 3 bytes on the 65C02.
struct arena_meta_t
{
	struct arena_meta_t* next;
	uint8_t offset;
};

typedef struct arena_meta_t* arena_t;

// The `arena_init` function initializes a new
// arena allocator. A pointer to the new arena
// allocator is returned. All allocators are 
// stored on the first page of the "HEAP"
// segment.
arena_t* arena_init();

// This function allocates a block of size `size`
// in the passed arena. The allocation size may
// not surpass 253 bytes.
// Each page requested by the arena will store the
// address of the subsequent page and the offset on
// the current page in the first three bytes of
// the page.
void* arena_alloc(arena_t* arena, const uint8_t size);

// The `arena_deinit` function deinitializes the
// passed arena. This frees all memory allocated
// by the arena.
void arena_deinit(arena_t* arena);
