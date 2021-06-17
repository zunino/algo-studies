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

func fib(n int) int64 {
    if n < 2 {
        return int64(n)
    }
    return fib(n-2) + fib(n-1)
}

func fib_memoized(n int, memo map[int]int64) int64 {
    memoized, ok := memo[n]
    if ok {
        return memoized
    }
    if n < 2 {
        return int64(n)
    }
    f := fib_memoized(n-2, memo) + fib_memoized(n-1, memo)
    memo[n] = f
    return f
}

func main() {
    // for i := 0; i < 42; i++ {
    //     fmt.Printf("fib(%d) = %d\n", i, fib(i))
    // }

    memo := make(map[int]int64)
    for i := 0; i < 42; i++ {
        fmt.Printf("fib(%d) = %d\n", i, fib_memoized(i, memo))
    }
}
