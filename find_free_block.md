## Function: `find_free_block`

### 1. Purpose
Find  a suitable chuck of memory for our requested allocation

### 2. Role in allocator lifecycle
Which path is this part of?
- allocation path
- traversal

### 3. Inputs
| Name | Kind                            | Meaning                                              |
|------|---------------------------------|------------------------------------------------------|
| arg1 | last-known block header pointer | keep track of the block preceding the suitable block |
| arg2 | requested size                  | size of the allocated payload                        |

### 4. Reads
What state does this function inspect?
- allocator base / traversal start
- current block metadata header
- current block free status
- current block size
- link to the succeeding block
- link to the preceding block

### 5. Writes
What state does this function mutate?
- ...
- ...
- ...

### 6. Must be true before
What assumptions/preconditions must already hold?
- an initialized block-list base
- the current block pointer has a valid block header
- the size/free metadata of each block is true

### 7. Core steps
1. establish an initial connection to the allocator base/block-list
2. confirm the current block is free and can fit our requested payload
3. if current block cannot fit we traverse to the next block
4. return a suitable block when found

### 8. Guarantees after
If this function succeeds, what must be true afterward?
- we have found a suitable block to allocate the requested payload
- record of the block preceding the suitable block

### 9. Failure meaning
If this function returns `NULL`, `0`, `false`, or exits early, what does that mean?
- an invalid allocator/block-list
- no suitable block was found
- ...

### 10. Breaks if misused
What goes wrong if the assumptions are false?
- out of bounds pointer
- ...
- ...

### 11. Behavior category
- Well-defined if:
    - return an allocable chunk
- Undefined behavior if:
    - ...
- Implementation-defined if relevant:
    - ...

### 12. Rule notes
```c
rule({
    "must have an initialzed heap to begin traversal",
    "a block must have a preceding block to record where we left off",
    "a suitable block is free and at least the size of the requested payload size"
});
