## Function: `[no_free_malloc]`

### 1. Purpose
Allocate memory on the heap

### 2. Role in allocator lifecycle
Which path is this part of?
- allocation path


### 3. Inputs
| Name | Kind        | Meaning                   |
|------|-------------|---------------------------|
| arg1 | size_t size | number of allocated bytes |


### 4. Reads
What state does this function inspect?
- Allocator break line

### 5. Writes
What state does this function mutate?
- Position of the allocator's break line

### 6. Must be true before
What assumptions/preconditions must already hold?
- An active heap
- Where we allocate must be part of our heap

### 7. Core steps
1. Specify size 
2. Record a pointer to the heap's break
3. Attempt heap growth
4. Old break is allocation base
5. Pointer to the new break has a new location or return NULL if allocation faire

### 8. Guarantees after
If this function succeeds, what must be true afterward?
- An allocated chunk of specified size
- The break's position in the heap is deeper in the heap

### 9. Failure meaning
If this function returns `NULL`, `0`, `false`, or exits early, what does that mean?
- Not enough heap space to allocate in
- No break was found

### 10. Breaks if misused
What goes wrong if the assumptions are false?
- Misposition of the break
- Wrong amount of allocated memory

### 11. Behavior category
- Well-defined if:
    - Space is allocated
    - sbrk() returns null
- Undefined behavior if:
    - ...
- Implementation-defined if relevant:
    - narrowing size_t to an int when passing in allocation size to sbrk()

### 12. Rule notes
```c
rule({
    "sbrk(0) does nor create space; it points to the current break",
    "sprk(size) shifts the break by the size to be allocated",
    "either return the new break position or NULL on failure"
});