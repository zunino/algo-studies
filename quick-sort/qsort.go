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
    quicksort(coll[0:wall])
    quicksort(coll[wall:])
}

func main() {
    input := [][]int {
        {7},
        {7, 4},
        {7, 4, 9},
        {4, 3, 19, 6, 2},
        {2, 8, 5, 9, 3, 1, 4, 5},
    }
    for i := range input {
        elem := input[i]
        fmt.Print(elem, " => ")
        quicksort(elem[:])
        fmt.Println(elem)
    }
}

