#include "page_allocator.h"
#include "65c02.h"

#define FIRST_PAGE		0x0200
#define PAGE_SIZE		0x0100
#define PAGE_COUNT		(0x0200 + 0x3e00)/PAGE_SIZE
#define MAX_ALLOCATION_SIZE	0x00ff

struct page_allocator_t
{
	uint32_t lower_pages;	// lower 32 pages
	uint32_t upper_pages;	// upper 32 pages
	void* next_page;	// next page that will be allocated
};
static struct page_allocator_t* this = NULL;

void init_page_allocator()
{
	if (this != NULL)
		return;
	this = (struct page_allocator_t*)FIRST_PAGE;
	this->next_page = (void*)(FIRST_PAGE + PAGE_SIZE);
	this->lower_pages = 0x00000007;	// the first three pages are always used.
	this->upper_pages = 0x00000000;
}

void* page_alloc(const size_t size)
{
	void* addr;
	uint8_t page_index;
	uint32_t* pages;
	uint8_t offset;

	if (this == NULL) return NULL;			// uninitialized allocator
	if (this->next_page == NULL) return NULL;	// out of memory
	if (size > MAX_ALLOCATION_SIZE) return NULL;	// allocation too large

	addr = this->next_page;
	page_index = (uint16_t)addr >> 8;

	if (page_index > 31)
		this->upper_pages |= (1 << (page_index - 32));
	else
		this->lower_pages |= (1 << page_index);

	/* look for next available pages */
	offset = 0;
	pages = &this->lower_pages;
	for (page_index = 3; page_index < 64; ++page_index)
	{
		if (page_index == 32)
		{
			pages += 1;
			offset = 32;
		}
		if (*pages & (1 << page_index))
		{
			this->next_page = (void*)((uint16_t)(page_index + offset) << 8);
			goto ret;
		}
	}

	/* no available page found */
	this->next_page = NULL;

ret:
	return addr;
}

void page_free(const uint16_t* address)
{
	uint8_t page_index;
	uint8_t index;

	if (this == NULL) return;
	if (address == NULL) return;
	page_index = (uint16_t)address >> 8;

	/* zero out freed memory */
	index = 0;
	do
	{
		STA(address + index, 0);
		index++;
	} while (index);

	/* Unset bit for the freed page */
	if (page_index > 31)
		this->upper_pages &= ~(1 << (page_index - 32));
	else
		this->lower_pages &= ~(1 << page_index);

	/* Set the next page to this page if its address is smaller */
	if (this->next_page > address) this->next_page = (void*)address;
}
