/**
 * Identifying clusters of elements in binary matrices. There are several
 * similar problems, but this was inspired by the "River Sizes" challenge,
 * available at https://www.algoexpert.io/questions/River%20Sizes.
 *
 * ===
 * You're given a two-dimensional array (a matrix) of potentially unequal
 * height and width containing only 0s and 1s. Each 0 represents land, and each
 * 1 represents part of a river. A river consists of any number of 1s that are
 * either horizontally or vertically adjacent (but not diagonally adjacent).
 * The number of adjacent 1s forming a river determine its size.
 *
 * Write a function that returns an array of the sizes of all rivers represented
 * in the input matrix. The sizes don't need to be in any particular order.
 * ===
 *
 * The solution I came up with relies solely on the existing input, creating
 * no supporting data structures other than the one that holds the solution to
 * the problem.
 *
 * Andre Zunino <neyzunino@gmail.com>
 * 27 April 2020
 */

package main

import (
	"fmt"
)

type RiverMap [][]int
type Sizes []int

var input1 = RiverMap{
	{1, 0, 0, 1, 0},
	{1, 0, 1, 0, 0},
	{0, 0, 1, 0, 1},
	{1, 0, 1, 0, 1},
	{1, 0, 1, 1, 0},
}

var input2 = RiverMap{
	{1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 0},
	{1, 0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0},
	{0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1},
	{1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 0, 0},
	{1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 0, 1},
}

func (rm RiverMap) valueAt(row int, col int) int {
	if row < 0 || col < 0 || row >= len(rm) || col >= len(rm[0]) {
		return 0
	}
	return rm[row][col] & 1
}

func (rm RiverMap) riverAt(row int, col int) int {
	if row < 0 || col < 0 || row >= len(rm) || col >= len(rm[0]) {
		return 0
	}
	return rm[row][col] >> 1
}

func (rm RiverMap) setRiverAt(row, col, river int) {
	rm[row][col] |= river << 1
}

func (rm RiverMap) traverseRiver(row, col, river int, sizes Sizes) {
	if rm.riverAt(row, col) != 0 {
		return
	}
	rm.setRiverAt(row, col, river)
	sizes[river]++
	if right := rm.valueAt(row, col+1); right == 1 {
		rm.traverseRiver(row, col+1, river, sizes)
	}
	if bottom := rm.valueAt(row+1, col); bottom == 1 {
		rm.traverseRiver(row+1, col, river, sizes)
	}
	if left := rm.valueAt(row, col-1); left == 1 {
		rm.traverseRiver(row, col-1, river, sizes)
	}
	if top := rm.valueAt(row-1, col); top == 1 {
		rm.traverseRiver(row-1, col, river, sizes)
	}
}

func riverSizes(riverMap RiverMap) Sizes {
	sizes := make(Sizes, 1)
	for row := 0; row < len(riverMap); row++ {
		for col := 0; col < len(riverMap[0]); col++ {
			if riverMap[row][col] == 1 && riverMap.riverAt(row, col) == 0 {
				newRiver := len(sizes)
				sizes = append(sizes, 0)
				riverMap.traverseRiver(row, col, newRiver, sizes)
			}
		}
	}
	return sizes[1:]
}

func main() {
	fmt.Println("River Sizes")
	fmt.Printf("Sizes: %v\n", riverSizes(input1))
	fmt.Printf("Sizes: %v\n", riverSizes(input2))
}
