## Function: `find_header`

### 1. Purpose
Recover a chunks header from an allocated payload pointer

### 2. Role in allocator lifecycle
Which path is this part of?
- validation
- metadata/layout computation

### 3. Inputs
| Name | Kind | Meaning                             |
|------|------|-------------------------------------|
| arg1 |payload pointer| pointer to the desired memory chunk |

### 4. Reads
What state does this function inspect?
- block verification pointer compared to the payload starting address


### 5. Writes
What state does this function mutate?
- pointer arithmetic to track backwards from the payload to the block header

### 6. Must be true before
What assumptions/preconditions must already hold?
- the specified pointer must belong to an allocator owned payload

### 7. Core steps
1. acquire a block location by pointer
2. compute the header location using the fact that the header is placed right before the payload segment

### 8. Guarantees after
If this function succeeds, what must be true afterward?
- returns the corresponding payload header, if the pointer is an allocated chunk

### 9. Failure meaning
If this function returns `NULL`, `0`, `false`, or exits early, what does that mean?
- out of reach pointer
- moved backwards too many byte steps or not enough

### 10. Breaks if misused
What goes wrong if the assumptions are false?
- program failure
- invalid pointer as an argument

### 11. Behavior category
- Well-defined if:
    - we return the address of the block header
- Undefined behavior if:
    - ...
- Implementation-defined if relevant:
    - ...

### 12. Rule notes
```c
rule({
    "subtract byte-by-byte of an alocated chunk to reach the block header",
    "if the verification pointer == the start of payload, we likley have a valid pointer",
});
