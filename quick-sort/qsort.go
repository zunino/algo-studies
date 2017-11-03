package main

import "fmt"

func quicksort(coll []int) {
    if len(coll) < 2 {
        return
    }
    pivot := coll[0]
    wall := 1
    for i := wall; i < len(coll); i++ {
        elem := coll[i]
        if pivot > elem {
            if i != wall {
                coll[i], coll[wall] = coll[wall], coll[i]
            }
            wall++
        }
    }
    coll[0], coll[wall - 1] = coll[wall - 1], coll[0]
    quicksort(coll[0:wall - 1])
    quicksort(coll[wall:])
}

func main() {
    input := [][]int {
        {7},
        {7, 4},
        {7, 4, 9},
        {4, 3, 19, 6, 2},
        {5, 8, 2, 6, 9, 1},
        {2, 8, 5, 9, 3, 1, 4, 5},
        {4, 10, 1, 6, 3, 8, 2, 4, 0, 5},
    }
    for i := range input {
        elem := input[i]
        fmt.Print(elem, " => ")
        quicksort(elem[:])
        fmt.Println(elem)
    }
}

