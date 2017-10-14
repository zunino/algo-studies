package main

import "fmt"

func bubbleSort(coll []int) []int {
    result := make([]int, len(coll))
    copy(result, coll)
    for {
        swapped := false
        for i := 0; i < (len(result) - 1); i++ {
            if result[i] > result[i + 1] {
                tmp := result[i]
                result[i] = result[i + 1]
                result[i + 1] = tmp
                swapped = true
            }
        }
        if !swapped {
            break
        }
    }
    return result
}

func main() {
    numbers := [...]int {3, 8, 1, 7, 9, 12, 6, 2}
    sorted := bubbleSort(numbers[:])
    fmt.Println(sorted)
}

