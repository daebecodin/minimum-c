/*
 * Created by Durand Dyer-Branch on 3/25/26.
*/
#include <sys/types.h>
#include  <unistd.h>

/*
 *  Simple malloc to allocate space when needed
 *  unable to use free() and realloc()
 */
void *no_free_malloc(size_t size)
{
 /* returns void* to the current location of break */
 void *current_break = sbrk(0);

 /* size of requested allocation */
 void *size_request = sbrk(size);

 /* if sbrk() fails, return NULL */
 if (size_request == (void*)-1) {
  return NULL;
 }
}

/*
 *  Memory Chuck Metadata
 *
 *  Placed at the beginning of each chunk
 *  - ptr to next chunk
 *  - size of the chunk
 *  - int flag of freeness; 0 or 1
 *
 *  12 byte struct
 */
typedef struct block_header block_header; // linked-list type
struct block_header {
 size_t size; // block size in bytes
 block_header *next; // linked-list link to next block
 int is_free; // free-state flag
};

/*
 * First Fit Malloc
 *
 * Traverses through the list of memory chunks until we find a free block w/enough space for the requested allocation
 *
 * - begin at the base address of our heap
 * - test of the current chunk fits our needs; if so we return its starting address
 * - if not , we continue to the next chunk until we find a fitting chunk
 * - we keep note of the last visited chunk so malloc can extend the end of the heap if no fitting chunk is found
 *
 * - The function return a fitting chunk, or NULL if none were found
 */

void *global_base = NULL; // signaling we haven't set up yet
block_header *find_free_block(block_header **last, size_t size)
{
 block_header *current = global_base; // start at first block header

 // for each block check if it's free and if its size is at least the requested size
 while (current && !(current->is_free && current->size >= size)) { // if not, remember it as the previous block and move to next
  *last = current;
  current = current->next;
 }
 return current; // if so the return the address
};



