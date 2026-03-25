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
typedef struct block_header *block_header; // linked-list type
struct block_header {
 size_t size;
 block_header *next;
 int free_flag;
};
