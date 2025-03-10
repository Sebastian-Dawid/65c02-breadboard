/************************************************/
/* Simple 65C02 page allocator.                 */
/* Author: Sebastian Dawid                      */
/* E-Mail: sdawid@techfak.uni-bielefeld.de      */
/*                                              */
/* This is serves as the underlying allocator   */
/* for the arena allocator implemented in       */
/* `arena_allocator.[h|c]`. The singleton       */
/* instance of this allocator will always take  */
/* up the first 8 bytes of page 0x0200. This    */
/* will be used to store all allocators that    */
/* access the "HEAP" segment of the 16K RAM.    */
/* This will allow a total of 124 arena         */
/* allocators to be initialized at the same     */
/* time.                                        */
/* The heap will consist of 46 pages including  */
/* page 0x0200. This means the effective        */
/* number of pages available on the heap is 45. */
/************************************************/

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
void page_free(const void* address);
