# Ford–Johnson Algorithm (Merge-Insertion Sort)

The Ford–Johnson algorithm (L. R. Ford Jr. & S. M. Johnson, 1959), also called
**merge-insertion sort** (Knuth, *TAOCP* vol. 3, §5.3.1), is a comparison sort
designed with a single goal: **perform as few comparisons as possible** in the
worst case. It is not the fastest algorithm in wall-clock time — it is the one
that gets closest to the information-theoretic minimum number of comparisons
(`⌈log₂(n!)⌉`).

Use case: sorting where a comparison is *expensive* (network round-trip, human
judgement, cryptographic operation), while moving elements around is cheap.

---

## The Algorithm

Given `n` elements:

### 1. Pairing
Split the elements into `⌊n/2⌋` pairs. If `n` is odd, one element is left over
(the *straggler*). Compare the two elements of each pair — **1 comparison per
pair** — and note the *winner* (larger) and *loser* (smaller).

### 2. Recursion
Recursively sort the winners by the same procedure. The recursion bottoms out
at a single element. After this step the winners form a sorted sequence

```
a1 ≤ a2 ≤ a3 ≤ … ≤ ak        (main chain)
```

and each `aᵢ` drags along its loser `bᵢ` (the *pend* elements). The key
invariant that survives the recursion:

```
bᵢ ≤ aᵢ   for every i        (bᵢ lost the pairwise comparison to aᵢ)
```

### 3. Free insertion of b1
`b1 ≤ a1 ≤ everything else`, so `b1` goes to the front of the main chain with
**zero comparisons**:

```
b1  a1  a2  a3  …  ak
```

### 4. Insertion of the remaining pend elements
Each remaining `bᵢ` is inserted into the main chain by **binary search**, with
two crucial refinements — this is the heart of the algorithm:

**(a) Bounded search area.** Since `bᵢ ≤ aᵢ`, the search only needs to cover
the part of the chain *strictly before* `aᵢ` — never the whole chain.

**(b) Jacobsthal insertion order.** Elements are NOT inserted left-to-right
(`b2, b3, b4, …`) but in groups delimited by the Jacobsthal numbers
`J(k) = J(k-1) + 2·J(k-2)`, `J(0) = 0`, `J(1) = 1`:

| k    | 0 | 1 | 2 | 3 | 4 | 5  | 6  | 7  | 8  | 9   | …  |
|------|---|---|---|---|---|----|----|----|----|-----|----|
| J(k) | 0 | 1 | 1 | 3 | 5 | 11 | 21 | 43 | 85 | 171 | …  |

Group k covers pend indices `(J(k-1), J(k)]` and is inserted *in reverse*:

| group | cut-point J | pend elements | insertion order | max search area | cost each |
|-------|-------------|---------------|------------------|-----------------|-----------|
| 0 | 1 | b1 | b1 → front | — | 0 (free) |
| 1 | 3 | b2, b3 | b3, b2 | 3 | ≤ 2 cmp |
| 2 | 5 | b4, b5 | b5, b4 | 7 | ≤ 3 cmp |
| 3 | 11 | b6 … b11 | b11, b10, …, b6 | 15 | ≤ 4 cmp |
| 4 | 21 | b12 … b21 | b21, b20, …, b12 | 31 | ≤ 5 cmp |

(J(0)=0 and the repeated 1 delimit nothing — b1 is inserted for free anyway.
Note the search areas: always `2^t − 1`, the binary-search sweet spots.)

**Why this order?** Binary search into an area of `m` elements costs
`⌈log₂(m+1)⌉` comparisons in the worst case. That cost is flat between powers
of two: searching among 2 elements costs 2 comparisons — and searching among
**3** elements *also* costs 2. Areas of size `2^t − 1` (1, 3, 7, 15, …) are
the "sweet spots": maximum area for a given price.

Inserting a group in reverse keeps every insertion in that group at the sweet
spot. Example: before inserting `b3`, the area in front of `a3` holds 3
elements (`b1 a1 a2`) → 2 comparisons. After `b3` lands, the area in front of
`a2` grows to 3 elements as well → still 2 comparisons. Had we inserted `b2`
first (area of 2 → same 2 comparisons) and `b3` second, its area could have
grown to 4 → **3** comparisons. The Jacobsthal cut-points are
exactly where the worst-case area sizes hit `2^t − 1`.

The straggler (if any) is treated as the last pend element; having no partner,
its search area is the whole chain built so far.

### 5. Result
After all pend elements are inserted, the main chain is the sorted sequence.

---

## Worked Example

Input (n = 9): `8 3 9 1 5 2 7 4 6`

**Pairing** — 4 comparisons, straggler `6`:

```
(8,3) (9,1) (5,2) (7,4)        winners: 8 9 5 7    straggler: 6
```

**Recursion** on `8 9 5 7` (same procedure, shown compressed):
pairs `(8,9)(5,7)` → 2 cmp; recurse on `9 7` → 1 cmp; unwinding the
recursion and inserting losers costs 2 more cmp. Result: winners sorted
`5 7 8 9`, **5 comparisons** total in this step.

**Unwind at the top level.** Attach the losers back:

```
main chain:   a1=5  a2=7  a3=8  a4=9
pend:         b1=2  b2=4  b3=3  b4=1     + straggler 6 (as b5)
```

**Insert b1 = 2** — free, no comparisons:

```
2  5  7  8  9
```

**Jacobsthal order:** `b3, b2, b5, b4` (groups `{3,2}` then `{5,4}`).

| step | element | search area (before partner) | size | cmp | chain after |
|------|---------|------------------------------|------|-----|-------------|
| 1 | b3 = 3 | `2 5 7` (before a3=8)  | 3 | ≤2 | `2 3 5 7 8 9` |
| 2 | b2 = 4 | `2 3 5` (before a2=7)  | 3 | ≤2 | `2 3 4 5 7 8 9` |
| 3 | b5 = 6 | whole chain (straggler) | 7 | ≤3 | `2 3 4 5 6 7 8 9` |
| 4 | b4 = 1 | `2 3 4 5 6 7 8` (before a4=9) | 7 | ≤3 | `1 2 3 4 5 6 7 8 9` |

Note step 2: because `b3` went in *first*, the area before `a2` grew from 2 to
3 elements — same price (2 comparisons), more coverage. That is the whole
point of the reverse-group order.

**Total: 4 + 5 + 0 + 2 + 2 + 3 + 3 = 19 comparisons** — exactly the
worst-case bound `F(9) = 19`.

---

## Distinctive Features

- **Optimizes comparisons, not time.** Data movement (`insert` into the middle
  of a container) is O(n) per insertion; total time complexity is O(n²) moves
  in the worst case for array-backed containers, while comparisons stay
  O(n log n) with the smallest known constant.
- **Two-phase structure**: a merge-like pairing/recursion phase + an
  insertion phase — hence "merge-insertion sort".
- **Comparison-optimal for small n**: for n ≤ 22 (and many larger n) no
  comparison sort can do better in the worst case. E.g. for n = 21:
  `⌈log₂(21!)⌉ = 66 = F(21)` — Ford–Johnson meets the theoretical floor
  exactly.
- **Every comparison is between element values** — there are no "bookkeeping"
  comparisons; pairing links and positions are tracked structurally.

## Worst-Case Comparison Count

```
F(n) = F(n-1) + ⌈log₂(3n/4)⌉,   F(1) = 0
```

| n | 3 | 5 | 9 | 13 | 21 | 22 | 100 | 1000 | 3000 | 30000 |
|---|---|---|---|----|----|----|-----|------|------|-------|
| F(n) | 3 | 7 | 19 | 34 | 66 | 71 | 534 | 8641 | 30546 | 406318 |

---

## Critical Checkpoints (how to verify an implementation)

1. **Correctness**: output is sorted for any input — including duplicates,
   already-sorted, reverse-sorted, 1 element, 2 elements, odd and even sizes.

2. **Comparison count ≤ F(n).** Instrument every value comparison with a
   counter and check against the table above. The classic eval test:
   **21 random numbers must never exceed 66 comparisons.** Exceeding the bound
   proves the implementation deviates from Ford–Johnson. Typical culprits:
   - pend elements inserted left-to-right instead of Jacobsthal order;
   - binary search over the *whole* chain instead of the area bounded by the
     partner's position;
   - pairs not re-linked correctly through recursion levels (partner
     information lost), forcing wider searches;
   - extra comparisons hidden in `std::sort`/`std::max` calls.

   Stress test:
   ```sh
   for i in $(seq 1000); do
       ./PmergeMe $(shuf -i 1-1000 -n 21 | tr '\n' ' ')
   done | grep -o 'CMP count = [0-9]*' | sort -t= -k2 -n | tail -1   # must be ≤ 66
   ```

3. **Jacobsthal order is actually used**: trace the insertion sequence for
   n ≥ 10; it must be `b1, b3, b2, b5, b4, b11, …, b6, …`, not sequential.

4. **Search area is bounded**: when inserting `bᵢ`, the upper bound of the
   binary search must be `aᵢ`'s current position, not the end of the chain.

5. **The recursion sorts pairs by their larger element**, and each level keeps
   the winner→loser link so that step 4 can find the partner.
