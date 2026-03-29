/*
 * Created by Durand Dyer-Branch on 3/25/26.
*/
#include <sys/types.h>
#include  <unistd.h>
#include <stddef.h>



void *global_base = NULL; // signaling we haven't set up yet

// size is # of bytes before the payload starts
#define BLOCK_SIZE offsetof(block_header, data)

/*
 * 8-byte alignment helper
 */
static size_t align8(size_t size)
{
 return (size + 7) & ~(size_t)7;
}

/*
 * Purpose
 *   - simple malloc to allocate space when needed
 * Pre-Truth
 *   - need a heap storage
 * Post-Guarantee
 *   - allocated chunk if specified size
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
 return current_break;
}

/*
 *  Memory Chuck Metadata
 *
 *  Placed at the beginning of each chunk
 *  - size of the chunk
 *  - int flag of freeness; 0 or 1
 *  - ptr to next chunk
 *  - ptr to prev chunk
 *  - ownership verification pointer
 *  - payload start marker
 */
typedef struct block_header block_header; // linked-list type
struct block_header {
 size_t size; // block size in bytes
 int is_free; // free-state flag
 block_header *next; // link to next block
 block_header *prev; // link to previous block
 void *ptr; // test pointer
 char data[1]; // indicate end of meta-data
};

/* Finding a header
 * Arguments
 *   - a pointer to the payload of an allocated block
 * Behavior
 *   - given a payload pointer
 *   - compute backwards by bytes
 *   - return its header address
 */
block_header *find_header(void *p)
{
 char *temp; // create temp pointer
 temp = p; // give it a copy
 return (block_header *) ((char *) temp - BLOCK_SIZE); // compute back to the block header
}

/*
 * Valid address for free function
 * Arguments
 *   - a pointer to an allocated payload
 * Behavior
 *   - start at an initialized allocator
 *   - if the given pointer is between the start at the current heap break
 *   - compute the block header from p
 *   - confirm the headers stored payload matches p
 *   - return 1 if valid, otherwise 0
 */
int validate_address(void *p)
{
 // start at the beginning of the heap
 if (global_base) {
    if (p > global_base && p < sbrk(0)) {
     // return the pointer to a validated block
     return p == find_header(p) -> ptr;
    }
 }
 return 0; // failure
}

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

block_header *find_free_block(block_header **last, size_t size)
{
 block_header *current = global_base; // start at first block header

 // for each block check if it's free and if its size is at least the requested size
 while (current && !(current->is_free && current->size >= size)) { // if not, remember it as the previous block and move to next
  *last = current; // give last a copy of current
  current = current->next; // give current a copy of its linked chunk
 }
 return current; // if so then return the address
};

/*
 * Extending the heap memory
 *
 * If we cant find a suitable unused chunk
 * We move the break and initialize the block at the end of the linked list
 */


block_header *extend_heap(block_header *last, size_t size)
{
 block_header *block = sbrk(0); // requesting space
 void *block_request = sbrk(size + BLOCK_SIZE); // requested size + header

 // if sbrk fails
 if (block_request == (void*)-1) {
  return NULL;
 }
 if (last) {
  last -> next = block; // link the current end to the block at the end of the heap
 }
 // initialize the block
 block -> size = size; // requested space
 block -> next = NULL; // place at end
 block -> is_free = 0; // the block is no longer free
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

/*
 * Malloc
 * base starts at NULL meaning empty list
 *
 * If the base is NULL, this is the allocators first attempted block creation:
 *   - extend the heap
 *   - make the base point to the first block
 * If it's not NULL:
 *   - search the list for a suitable block
 *   - if found then
 *     - split the block only if its remainder is big enough,
 *     - for a new header and aligned new payload
 *     - mark it as used
 *   - if no suitable chunk is found:
 *     - extend the heap and append a new block to the list
 */
void *base = NULL;
void *malloc(size_t size)
{
 block_header *request, *last_block;
 size_t size_aligned = align8(size);

 if (base) {

  // start searching from the head of the block list
  last_block = base;

  // look for a free block of sufficient size for the request
  request = find_free_block(&last_block, size_aligned);

  // if a block is found
   if (request) {
    // split if the found block has leftover space to form a new block
    if ((request -> size - size_aligned) >= BLOCK_SIZE + 8) {
     split_free_block(request, size_aligned); //split
    }
    request -> is_free = 0; // no longer free
   } else {
    // if no fitting block is found, grow the heap
    request = extend_heap(last_block, size_aligned);
    if (!(request)) { // if extension fails
        return NULL;
    }
   }
 } else {
   // empty list -> first block allocation
   request = extend_heap(NULL, size_aligned);
   if (!request) {
     return NULL;
   }
    // base points to the first block
    base = request;
 }
   return request -> data;
}

/*
 * Calloc
 * Arguments
 *   - byte_count: number of elements
 *   - size: size  of each element in bytes
 * Behavior
 *   - allocate byte_count * size
 *   - initializes every allocated byte to 0
 *   - returns NULL if allocation fails
 */
void *calloc(size_t byte_count, size_t size)
{
 void *new = malloc(byte_count * size); // allocate total byte_count * size
 size_t i;

 if (new) {
  unsigned char *p = new; // byte-wise view of allocated memory
  // loop through addresses
  size_t count = byte_count * size;
  for (i = 0; i < count ; i ++) {
   p[i] = 0; // initialize each byte to 0
  }
 }
 return new; // return head of allocated block
}

/*
 * Fusion
 * Arguments
 *    - block: free block to be merged with neighbors
 * Behavior
 *    - check if the next block exists and is free
 *    - merge the next free block into the current block
 *    - relink the merged block to the successor of the old next block
 */
block_header *merge_blocks(block_header *block)
{
 // if the next block exist and is free, merge it into current block
 if (block -> next && block -> next -> is_free) {
  block -> size += BLOCK_SIZE + block -> next -> size; // grow current block by header + next payload
  block -> next = block -> next -> next; // unlink the absorbed block

  // if the successor exist, reconnect it's previous to the absorbed block
  if (block -> next) {
   block -> next -> prev = block;
  }
 }
 return block;
}

/*
 * Free
 * Arguments
 *   - pointer to an allocated payload
 * Behavior
 *   - check if the given pointer is valid
 *   - get the block header address
 *    - mark the block as free
 *   - if the previous block exist and is free, merge with it
 *   - if the resulting block is the last block then we remove from the heap
 *   - if the resulting block is the only block then we rest base to NULL
 */
void free(void *p) {
 // find the block
 block_header *b;

 // validate the pointer
 if (validate_address(p)) {
  b = find_header(p);
  b -> is_free = 1; // mark it as free

  // if the block's predecessor exists and is marked free
  if (b -> prev && b -> prev -> is_free) {
   // merge with prev
   b = merge_blocks(b -> prev);

   // merge with next
   if (b -> next) {
    merge_blocks(b);
   } else {
    // resulting block after merge
    if (b -> prev) {
     b -> prev -> next = NULL; // this block is the last block in the list so we remove it
    } else {
     // reset base to null
     global_base = NULL; // no blocks remain
    }
    brk(b); // move the program break to the start this of block
   }
  }
 }
}

/* Copy Block
 * Arguments
 *   - source: source block header
 *   - destination: destination block header
 * Behavior
 *   - store typed pointers to the blocks payloads
 *   - iterate through the block is byte-sized units
 *   - copy data from source payload to the destination payload
 *   - stop when either block's payload limit is reached
 */
void copy_block(block_header *source, block_header *destination) {
 // pointers to payload region of each block
 unsigned char *sdata, *ddata;
 size_t step;

 // pointers for allocated block payloads
 sdata = source -> ptr;
 ddata = destination -> ptr;

 // copy up to the source's byte capacity if destination's is larger
 // copy up to the destination's byte capacity if the source's is larger
 size_t limit = source -> size < destination -> size ? source -> size : destination -> size;
 for (step = 0; step < limit; ++step) {
       ddata[step] = sdata[step];
 }
}







