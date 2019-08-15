/**
 * FizzBuzz
 *
 * Motivated by a Tom Scott's video on the subject.
 * https://youtu.be/QPZ0pIK_wsc
 *
 * Andre Zunino <neyzunino@gmail.com>
 * 15 August 2019
 */

package main

import (
    "fmt"
    "strings"
    "strconv"
)

func FizzBuzz(limit int) {
    var buffer strings.Builder
    buffer.Grow(8)
    for i := 1; i <= limit; i++ {
        if i % 3 == 0 {
            buffer.WriteString("Fizz")
        }
        if i % 5 == 0 {
            buffer.WriteString("Buzz")
        }
        if buffer.Len() == 0 {
            buffer.WriteString(strconv.Itoa(i))
        }
        fmt.Println(buffer.String())
        buffer.Reset()
    }
}

func main() {
    FizzBuzz(50)
}
