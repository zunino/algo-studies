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
  result := strings.to_string(sb)
  if len(result) == 0 {
    return "none"
  }
  return result
}

@(test)
test_fizz :: proc(t: ^testing.T) {
  res := fizzbuzz(9)
  testing.expect_value(t, res, "fizz")
}

@(test)
test_buzz :: proc(t: ^testing.T) {
  res := fizzbuzz(10)
  testing.expect_value(t, res, "buzz")
}

@(test)
test_fizzbuzz :: proc(t: ^testing.T) {
  res := fizzbuzz(15)
  testing.expect_value(t, res, "fizzbuzz")
}

@(test)
test_none :: proc(t: ^testing.T) {
  res := fizzbuzz(16)
  testing.expect_value(t, res, "none")
}
