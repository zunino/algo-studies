/**
 * FizzBuzz
 *
 * Who would've thunk? After all these years...
 *
 * Andre Zunino <neyzunino@gmail.com>
 * 7 April 2026
 */

package main

import "core:strings"
import "core:fmt"
import "core:testing"

fizzbuzz :: proc(n: int) -> string {
  sb := strings.builder_make_len_cap(0, len("fizzbuzz"))
  defer strings.builder_destroy(&sb)
  if n % 3 == 0 {
    strings.write_string(&sb, "fizz")
  }
  if n % 5 == 0 {
    strings.write_string(&sb, "buzz")
  }
  if strings.builder_len(sb) == 0 {
    strings.write_int(&sb, n)
  }
  return strings.clone(strings.to_string(sb))
}

main :: proc() {
  numbers := []int{2, 3, 5, 15, 19}
  for i in numbers {
    res := fizzbuzz(i)
    defer delete(res)
    fmt.printf("fizzbuzz(%d) => %s\n", i, res)
  }
}

@(test)
test_fizz :: proc(t: ^testing.T) {
  res := fizzbuzz(9)
  defer delete(res)
  testing.expect_value(t, res, "fizz")
}

@(test)
test_buzz :: proc(t: ^testing.T) {
  res := fizzbuzz(10)
  defer delete(res)
  testing.expect_value(t, res, "buzz")
}

@(test)
test_fizzbuzz :: proc(t: ^testing.T) {
  res := fizzbuzz(15)
  defer delete(res)
  testing.expect_value(t, res, "fizzbuzz")
}

@(test)
test_none :: proc(t: ^testing.T) {
  res := fizzbuzz(16)
  defer delete(res)
  testing.expect_value(t, res, "16")
}
