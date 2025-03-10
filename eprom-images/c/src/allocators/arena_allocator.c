#include "arena_allocator.h"
#include "page_allocator.h"

#define FIRST_ARENA		(arena_t*)0x0208
#define PAGE_SIZE		0x0100
#define MAX_ALLOCATION_SIZE	0x00fc

arena_t* arena_init()
{
	arena_t* arena = NULL;

	for (arena = FIRST_ARENA; arena < (arena_t*)0x0300; ++arena)
	{
		if (*arena == (struct arena_meta_t*)0xFFFF)
		{
			*arena = NULL;
			return arena;
		}
	}

	return NULL;
}

void* arena_alloc(arena_t* arena, const uint8_t size)
{
	struct arena_meta_t* am = *arena;

	if (size > MAX_ALLOCATION_SIZE) return NULL;

	for (;;)
	{
		if (PAGE_SIZE - am->offset >= size)
		{
			am->offset += size;
			return (void*)((uint8_t*)am + am->offset - size);
		}
		if (am->next == NULL)
			break;
		am = am->next;
	}

	// no viable page found -> add a new page to the arena
	am->next = page_alloc(PAGE_SIZE);
	if (am->next == NULL) // page allocation failed
		return NULL;

	am = am->next;
	am->next = NULL;
	am->offset = 3 + size;

	return (void*)((uint8_t*)am + am->offset - size);
}

void arena_deinit(arena_t* arena)
{
	struct arena_meta_t* am = *arena;
	struct arena_meta_t* _am;

	while (am != NULL)
	{
		_am = am;
		am = am->next;
		page_free(_am);
	}

	*arena = (struct arena_meta_t*)0xFFFF;
}
