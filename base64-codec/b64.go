package main

import (
    "os"
    "fmt"
    "b64enc"
    "b64dec"
)

func main() {
    if len(os.Args) != 3 {
        fmt.Fprintf(os.Stderr, "Wrong number of arguments.\n")
        os.Exit(1)
    }
    op := os.Args[1]
    if op == "e" {
        fmt.Println(b64enc.Base64enc(os.Args[2]))
    } else if op == "d" {
        fmt.Println(b64dec.Base64dec(os.Args[2]))
    } else {
        fmt.Fprintf(os.Stderr, "Invalid operation.\n")
        os.Exit(1)
    }
}

