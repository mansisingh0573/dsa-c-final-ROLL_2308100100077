## C1 Defect Report

| No  | Line | Defence | Consequence |
| --- | ---- | ------- | ----------- |

| 1 | 4 | `prev` isn't initialized to `NULL` before using it. | It puts junk/garbage memory into `curr->next` on the first iteration (or crashes if the list is empty) |

|2 | 6 | The loop checks `curr->next != NULL` instead of `curr != NULL`. |Crashes with a Seg Fault if `head` is `NULL`, and stops early so it forgets to flip the last node in the list. |

|3 | 12 | It returns `head` at the end. | t returns the old head (which is now the last node) instead of `prev`, losing the whole reversed list. |

Corrected function:SectionC/C1_reverse.c  
Complexity: Time O(n), Space O(1)

## C2 Optimisation Report

1. Current Time Complexity & Performance

- Current Time Complexity: O(n²)
- Why it fails at scale: For n = 1,000,000, the nested loops run around n²/2 = 500,000,000,000 inner iterations. On a regular computer, executing that many operations takes several minutes (approx. 8–10 mins), causing the program to time out.

2.  Complexity of New Implementation

- Time Complexity: O(n) — Both `left` and `right` pointers only move forward through the array at most n times.
- Space Complexity: O(1) — Uses only a few scalar variables (`left`, `right`, `sum`, `best`).

3. Validity Condition

- Condition: All elements in the input array `a` must be non-negative (strictly positive or zero).
- Why it works: Adding positive numbers strictly increases the window sum and removing numbers decreases it. This monotonic behavior ensures that the `left` pointer never needs to step backward to find the optimal subarray.
