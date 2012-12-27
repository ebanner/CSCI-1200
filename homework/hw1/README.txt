1. O(n)
    - the for-loop takes (1/2)*n instructions, so it's O(n).

2. O(n^2)
    - the for loop takes this sequence of steps:
        -- n, n-1, n-2, n-3, n-4, ..., n-(n-1)
    - so it takes approximately (1/2)*n^2. that's O(n^2).

3. O(n)
    - the problem is made simpler by making our way down to the base case of 0,
      starting at n, 1 at a time. that's O(n).

4. O(n^(3/2))
    - we're doing sqrt(n)*n instruction, so it's O(n^(3/2))
