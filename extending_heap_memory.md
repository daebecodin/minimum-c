## Function: `extend_heap`

### 1. Purpose
In the event we cannot find a suitable block, we will extend the heap memory

### 2. Role in allocator lifecycle
Which path is this part of?
- allocation path
- heap growth

### 3. Inputs
| Name | Kind           | Meaning                                  |
|------|----------------|------------------------------------------|
| arg1 | header pointer | the final block header in the block list |
| arg2 | size           | size to be allocated                     |

### 4. Reads
What state does this function inspect?
- allocator break
- final block in allocator block-list
- size to allocate to the new payload
- allocation requirement for block header

### 5. Writes
What state does this function mutate?
- allocator-managed heap is extended to fit a new block
- new tail block header is initialized
- previous tail block is linked to new block
- new block is initialized and set to active use


### 6. Must be true before
What assumptions/preconditions must already hold?
- an initialized block-list
- a valid block-list break
- a valid block header of the final block

### 7. Core steps
1. establish current heap-growth starting point from allocator break
2. attempt to expand allocator-managed heap memory enough for new block
3. initialize the new blocks meta-data heater according to the allocators layout contract
4. append the new block to the end of the block-list and return it, or report failure if growth did not succeed

### 8. Guarantees after
If this function succeeds, what must be true afterward?
- our block-list is extended by the specified size
- a pointer to the new block header

### 9. Failure meaning
If this function returns `NULL`, `0`, `false`, or exits early, what does that mean?
- unable to create a new block of requires size 
- attempting to add/create in invalid memory

### 10. Breaks if misused
What goes wrong if the assumptions are false?
- attempting to create a new block fails
- retrieving a block-list break fails
- block header manipulations fail

### 11. Behavior category
- Well-defined if:
    - successfully allocated block
- Undefined behavior if:
    - ...
- Implementation-defined if relevant:
    - sbrk() fails

### 12. Rule notes
```c
rule({
    "block-list extention starts from the block-list break",
    "creating a block must follow the header / payload size contract",
    "shift pointers to new block and block-list end"
});
