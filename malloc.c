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
