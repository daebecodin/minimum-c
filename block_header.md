# Block Header Mastery Notes

## Struct name
`[block_header]`

## 1. Purpose
What system job does this header perform?

Example prompts:
- The block header comprises
  - block size in bytes
  - free usage indicator
  - pointer to the next block header
  - pointer to the previous block header
  - a ptr to verify block ownership
  - a marker to the start of the block payload
- Why does a payload need metadata in front of it?
  - Allows for efficient memory retrieval or lookup without the need to fully access the memory
***

## 2. Mental model
Describe the block header as part of the allocator.
- A block header is allocator-owned metadata.
- It describes the payload region associated with one block.
- It stores the information needed to traverse, reuse, split, or free blocks.

---

## 3. Layout relationship
How does this struct relate to memory layout?

### Relationship to payload
- Header is located: `before` the payload
- Payload begins at: `chunk after metadata`
- Header describes: `block contents and state`

### Memory sketch
```text
[ block_header ][ payload bytes .............. ]
^              ^
header start    payload start