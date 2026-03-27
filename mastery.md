# Malloc Mastery Notes

## Allocator Model
- The Heap is managed as block headers each with a payload region
- Blocks are traversed through links or adjacency
- Free/used block state lives in the metadata header, not the payload
- Allocators uses free space or extends the heap
- Free returns a block to allocator control, no specifically the OS
- Splitting block reduces internal memory waste
- Merging block reduces external fragmentation
***
## Pointer Roles
- Header Pointer  &rarr; points allocator metadata
- Payload Pointer &rarr; points to user-usable bytes
- Byte-Pointer &rarr; used for byte-sized movement and copy
- List Link &rarr;  used to connect blocks for traversal
- Raw Address &rarr; untyped memory location
***
## Function Mastery Template
## Function: `[function_name]`

### 1. Purpose
What job does this function perform?

### 2. Role in allocator lifecycle
Which path is this part of?
- allocation path
- free path
- traversal
- validation
- heap growth
- split/coalesce
- metadata/layout computation
- payload copy

### 3. Inputs
| Name | Kind | Meaning |
|------|------|---------|
| arg1 | header pointer / payload pointer / size / etc. | ... |
| arg2 | ... | ... |

### 4. Reads
What state does this function inspect?
- ...
- ...
- ...

### 5. Writes
What state does this function mutate?
- ...
- ...
- ...

### 6. Must be true before
What assumptions/preconditions must already hold?
- ...
- ...
- ...

### 7. Core steps
1. ...
2. ...
3. ...
4. ...

### 8. Guarantees after
If this function succeeds, what must be true afterward?
- ...
- ...
- ...

### 9. Failure meaning
If this function returns `NULL`, `0`, `false`, or exits early, what does that mean?
- ...
- ...
- ...

### 10. Breaks if misused
What goes wrong if the assumptions are false?
- ...
- ...
- ...

### 11. Behavior category
- Well-defined if:
    - ...
- Undefined behavior if:
    - ...
- Implementation-defined if relevant:
    - ...

### 12. Rule notes
```c
rule({
    "...",
    "...",
    "..."
});