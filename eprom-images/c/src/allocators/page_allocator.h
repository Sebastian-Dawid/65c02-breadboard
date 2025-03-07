/*******************************************/
/* Simple 65C02 page allocator.            */
/* Author: Sebastian Dawida                */
/* E-Mail: sdawid@techfak.uni-bielefeld.de */
/*******************************************/

#include <stddef.h>
#include <stdint.h>

// The `page_allocator` function creates the singleton instance of the page allocator.
// It initializes the page table and sets the address of the next page that will be allocated.
void int_page_allocator();

// The `page_alloc` function returns the address of the first available page.
// If no page is available or the allocator has not been initialized it will return `NULL`.
// @param[in] size The size of the requested allocation.
void* page_alloc(const size_t size);

// The `page_free` function signals that the page at the given address should be released.
// @param[in] address The starting address of the allocation to release.
void page_free(const uint16_t* address);
