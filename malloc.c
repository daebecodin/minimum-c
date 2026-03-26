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
 char data[1]; // indicate end of meta-data
};

/*
 * Finding a suitable chunk
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
 return current; // if so then return the address
};

/*
 * Extending the heap memory
 *
 * If we cant find a suitable unused chunk
 * We move the break and initialize the block at the end of the linked list
 */

// size of a header block
#define BLOCK_SIZE 12
block_header *place_block_end(block_header *last, size_t size)
{
 block_header *block = sbrk(0); // requesting space
 void *block_request = sbrk(size + BLOCK_SIZE);

 // if sbrk fails
 if (block_request == (void*)-1) {
  return NULL;
 }
 if (last) {
  last -> next = block; // place block next to the known last
 }
 block -> size = size; // requested space
 block -> next = NULL; // place at end
 block -> is_free = 0; // free status
 return block;
}

/*
 * Splitting a Block
 * - We have left over memory in a free chunk that's larger than needed
 * - the requested size for the nre chunk is takes from the free chunk
 * - we are left with a smaller free chunk after the operation
 */
void split_free_block(block_header *allocated_block, size_t size)
{
 // place address of first byte of free chunk header after the allocated chunk
 block_header *new_payload = (block_header*)(allocated_block -> data + size);

 new_payload -> size = allocated_block -> size - size - BLOCK_SIZE; // old payload - requested size - new block header
 new_payload -> next = allocated_block -> next; // new block links to the chunk that previously the allocated chunk
 new_payload -> is_free = 1; // marked free / available for allocation
 allocated_block -> size = size; // shrink the allocated chunk to the requested size
 allocated_block -> next = new_payload; // link the original block to the leftover free block
}




