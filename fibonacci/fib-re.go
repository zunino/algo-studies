/**
 * Recursive Fibonacci implementation (non-memoized vs memoized).
 *
 * F0 = 0
 * F1 = 1
 * Fn = Fn-2 + Fn-1
 *
 * Dynamic Programming (MIT OpenCourseWare)
 * https://youtu.be/OQ5jsbhAv_M
 *
 * Andre Zunino <neyzunino@gmail.com>
 * 16 June 2021
 */

package main

import (
    "fmt"
)

func fibMemoized(n int, memo map[int]int64) int64 {
    memoized, ok := memo[n]
    if ok {
        return memoized
    }
    if n < 2 {
        return int64(n)
    }
    f := fibMemoized(n-2, memo) + fibMemoized(n-1, memo)
    memo[n] = f
    return f
}

func main() {
    for i := 0; i < 10; i++ {
        memo := make(map[int]int64)
        fmt.Printf("fib(%d) = %d\n", i, fibMemoized(i, memo))
    }
}
