# huffman-c

A compact, **single-file C implementation of Huffman lossless compression**, engineered around a bit-packed flat array representation of the Huffman tree — no dynamic memory allocation, no external dependencies.

---

## Table of Contents

- [How It Works](#how-it-works)
- [Data Structure Design](#data-structure-design)
- [Algorithm Phases](#algorithm-phases)
- [Configuration](#configuration)
- [Sample Output](#sample-output)
- [Building](#building)
- [Customizing Input](#customizing-input)

---

## How It Works

Standard Huffman implementations typically build the tree using heap-allocated nodes with `left`/`right` pointers. This implementation takes a different approach: the entire tree — both leaf nodes and internal nodes — lives in a single contiguous `uint32_t` array (`tree_array`), with all node metadata bit-packed into each 32-bit element.

This eliminates pointer chasing, keeps the full tree in cache, and avoids any heap allocation.

---

## Data Structure Design

### Node Encoding (`uint32_t`)

Every entry in `tree_array` encodes a complete node in 32 bits:

```
 31       17  16   15              0
┌──────────────┬───┬───────────────┐
│  data (15b)  │ T │  freq (16b)   │
└──────────────┴───┴───────────────┘
```

| Field | Bits | Leaf Node | Internal Node |
|---|---|---|---|
| `freq` | `[15:0]` | Frequency count of this byte | Sum of children's frequencies |
| `T` (type flag) | `[16]` | `0` — this is a leaf | `1` — this is an internal node |
| `data` | `[31:17]` | The byte value (0–255) | Index of the **left child** in `tree_array` |

The right child of an internal node is always at `left_child_index + 1`, so no explicit right-child pointer is needed.

### Supporting Arrays

| Array | Size | Purpose |
|---|---|---|
| `tree_array[2*256-1]` | 511 entries | Flat storage for all tree nodes (leaves + internal) |
| `tree_index_array[256]` | 256 entries | Maps each byte value → its current index in `tree_array` |
| `id_array[256]` | 256 entries | Maps each byte value → its Huffman code (as an integer) |
| `store_array[DATA_SIZE]` | configurable | Packed output buffer for compressed bits |

---

## Algorithm Phases

### Phase 1 — Frequency Counting (`init_tree_array`)

Scans the input buffer once. For each byte:
- If unseen, a new leaf node is created in `tree_array` with the byte value packed into bits `[31:17]` and frequency initialized to 0.
- `tree_index_array[byte]` is updated to point to its slot.
- The leaf's `freq` field is incremented (a plain `++` on the full `uint32_t` works because `freq` occupies the low 16 bits, safely away from the type/data fields).

Result: the first `n` slots of `tree_array` hold one leaf per unique byte, unsorted.

### Phase 2 — Tree Construction (`create_tree_nodes`)

A modified **selection sort** builds the tree in-place, inserting new internal nodes into the same array as it runs:

```
for i = 0 to tree_array_idx:
    selection-sort tree_array[i..end] ascending by freq
    if i is odd:
        create parent for tree_array[i-1] and tree_array[i]
        append parent to tree_array  (increments tree_array_idx)
```

Because a new parent is appended every two steps, the sort naturally encounters it in subsequent iterations, maintaining the invariant that the two globally smallest unprocessed nodes are always paired next. The root ends up at `tree_array[tree_array_idx - 1]`.

**Complexity:** O((N · (N−1)) / 2), where N = 2n − 1 and n is the number of unique symbols.

### Phase 3 — Code Assignment (`traverse`)

A recursive post-order traversal starting from the root:
- At each internal node, recurse right first (appending bit `1`), then left (appending bit `0`).
- At each leaf, the accumulated integer `id` (built by `id = (id << 1) | bit` at each level) is stored in `id_array[byte_value]`.
- The leading `1` bit acts as a sentinel so codes of different lengths remain distinguishable (e.g. code `100` is stored as `1100`, not `100`).

### Phase 4 — Compression

For each byte in the input:
1. Look up its Huffman code in `id_array`.
2. Determine code length by finding the highest set bit.
3. Write each code bit, MSB-first, into `store_array` via a global bit cursor `i_bit`.

Output is packed at bit granularity — 8 code bits fill one byte of `store_array`.

### Phase 5 — Decompression

Traverses `tree_array` from the root, consuming one bit at a time from `store_array`:
- At an internal node: step to left child on bit `0`, right child (left + 1) on bit `1`.
- At a leaf: emit the stored byte value, reset position to root.

After decompression, the output is verified byte-for-byte against the original input. A `MATCH INCORRECT!` message and exit code `1` are produced on any mismatch.

---

## Configuration

All tuneable parameters are `#define` macros at the top of `main.c`:

```c
// Display leaf nodes as characters (remove for raw integer / binary data)
#define PRINT_AS_CHAR

// Length of the input data array
#define DATA_SIZE (12)
```

| Macro | Default | Effect |
|---|---|---|
| `PRINT_AS_CHAR` | defined | Leaf nodes print as `%c` (ASCII character) |
| *(undefined)* | — | Leaf nodes print as `%i` (raw byte integer) |
| `DATA_SIZE` | `12` | Size of the input byte array |
| `FREQ_BIT` | `0xFFFF` | 16-bit mask for the frequency field; supports up to 65,535 occurrences per unique symbol |

---

## Sample Output

Input: `"ABCDEFGGGABS"` (12 bytes, 8 unique symbols)

```
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
huffman tree: array view

huffman tree array size: 15
huffman tree leaf count: 8

0: (S) : 1
1: (F) : 1
2: (E) : 1
3: (D) : 1
4: (C) : 1
5: 2 - 3 : 2          <- internal node, children at indices 2 and 3
6: 0 - 1 : 2
7: (B) : 2
8: (A) : 2
9: 4 - 5 : 3
10: (G) : 3
11: 6 - 7 : 4
12: 8 - 9 : 5
13: 10 - 11 : 7
14: 12 - 13 : 12      <- root
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
huffman tree: tree view

                        | B - 2 [1111]
                4 [111]
                                | F - 1 [11101]
                        2 [1110]
                                | S - 1 [11100]
        7 [11]
                | G - 3 [110]
12 [1]
                                | D - 1 [10111]
                        2 [1011]
                                | E - 1 [10110]
                3 [101]
                        | C - 1 [1010]
        5 [10]
                | A - 2 [100]
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
huffman code

(A) - 100
(B) - 1111
(C) - 1010
(D) - 10111
(E) - 10110
(F) - 11101
(G) - 110
(S) - 11100
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
compressed data

00111010011101101101101010001111
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
uncompressed data

010000010100001001000011010001000100010101000110010001110100011101000111010000010100001001010011
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
data_size = 12
comp_size = 4
compression ratio = 66.67%
---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ---- ----
```

**12 bytes → 4 bytes at 66.67% compression**, with full round-trip verification.

---

## Building

No dependencies beyond a C compiler and CMake.

```bash
git clone https://github.com/laperex/huffman-c.git
cd huffman-c
git checkout wrk

cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build

./build/main
```

Or compile directly without CMake:

```bash
gcc -O2 -o huffman src/main.c
./huffman
```

---

## Customizing Input

The input data and size are set in `main.c`:

```c
#define DATA_SIZE (12)

uint8_t data[DATA_SIZE] = "ABCDEFGGGABS";
```

To compress a different sequence, update both. For non-printable or binary data, undefine `PRINT_AS_CHAR` so nodes display as integers:

```c
// #define PRINT_AS_CHAR    <- comment out for binary data

#define DATA_SIZE (8)
uint8_t data[DATA_SIZE] = { 0x01, 0x02, 0x01, 0x03, 0x01, 0x02, 0x04, 0x01 };
```

> **Note:** `FREQ_BIT` caps frequency counts at 65,535 per symbol. For inputs where any single byte appears more than 65,535 times, increase the frequency field width and update `FREQ_BIT` accordingly.
