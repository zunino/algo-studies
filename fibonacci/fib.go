/**
 * Non-recursive Fibonacci implementation.
 *
 * Inspired by an MIT video on Dynamic Programming, where Fibonacci is
 * implemented with a memoized recursive algorithm, I decided to write
 * a non-recursive implementation.
 *
 * Posted a question to StackOverflow on 17 June 2021.
 * https://stackoverflow.com/questions/68023637/
 *
 * Andre Zunino <neyzunino@gmail.com>
 * Created 13 June 2021
 * Modified 17 June 2021
 */

package main

import (
    "fmt"
)

func fib(n int) int64 {
    var f1 int64 = 1
    var f2 int64 = 0
    for i := 0; i < n; i++ {
        f1, f2 = f2, f1+f2
    }
    return f2
}

func main() {
    for i := 0; i < 10; i++ {
        fmt.Printf("fib(%d) = %d\n", i, fib(i))
    }
}
