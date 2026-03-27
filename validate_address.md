## Function: `validate_address`

### 1. Purpose
Validate that a block is in allocated space to later be freed

### 2. Role in allocator lifecycle
Which path is this part of?
- validation
- metadata/layout computation

### 3. Inputs
| Name | Kind             | Meaning                     |
|------|------------------|-----------------------------|
| arg1 | payload pointer  | adress to an allocated byte |

### 4. Reads
What state does this function inspect?
- address of heap head
- address of heap break
- address of an allocated pointer

### 5. Writes
What state does this function mutate?
- heap not mutated
- metadata not mutated

### 6. Must be true before
What assumptions/preconditions must already hold?
- the pointer must follow allocator-managed payload memory
- a payload must have a valid corresponding header within the allocator-managed heap region

### 7. Core steps
1. establish allocator-managed heap bounds
2. confirm out payload byte lies within these bounds 
3. retrieve the corresponding header using the allocator's layout relationship
4. return the header if the pointer satisfies allocator assumptions

### 8. Guarantees after
If this function succeeds, what must be true afterward?
- we have successfully validated an allocated pointer
- retrieved the block header of the verified pointer

### 9. Failure meaning
If this function returns `NULL`, `0`, `false`, or exits early, what does that mean?
- we do not yet have an allocated heap to begin with
- the specified pointer is not allocated in our heap
- incorrect pointer arithmetic

### 10. Breaks if misused
What goes wrong if the assumptions are false?
- program failure
- searching of a block header outside our heap

### 11. Behavior category
- Well-defined if:
    - validated block header returned
- Undefined behavior if:
    - ...
- Implementation-defined if relevant:
    - ...

### 12. Rule notes
```c
rule({
    "out heap must be initialized to begin with",
    "a pointer must be allocated within the heap in order to be validated",
    "..."
});
