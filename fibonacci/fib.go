/**
 * Non-recursive Fibonacci implementation.
 *
 * Inspired by an MIT video on Dynamic Programming, where Fibonacci is
 * implemented with a memoized recursive algorithm, I decided to write
 * a non-recursive implementation.
 *
 * Andre Zunino <neyzunino@gmail.com>
 * 13 June 2021
 */

package main

import (
    "fmt"
)

func fib(n int) int {
    f1 := 1
    f2 := 0
    for i := 0; i < n; i++ {
        tmp := f2
        f2 = f1 + f2
        f1 = tmp
    }
    return f2
}

func main() {
    for i := 0; i < 10; i++ {
        fmt.Printf("fib(%d) = %d\n", i, fib(i))
    }
}
