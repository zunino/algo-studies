package main

import (
    "os"
    "fmt"
)

var table = [64]byte {
    'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
    'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
    'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
    'w', 'x', 'y', 'z', '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '+', '/',
}

const paddingchar = '='

// make_b64_slice creates a byte slice with a calculated length to hold the Base64-
// encoded version of text.
func make_b64_slice(src []byte) []byte {
    srclen := len(src)
    triplets := srclen / 3
    mod3 := srclen % 3
    if mod3 != 0 {
        triplets++
    }
    return make([]byte, triplets * 4)
}

func encodeTriplet(b1, b2, b3 byte, b64 []byte, di int) {
    b64[di + 0] = table[b1 >> 2]                      // 6 most-significant bits of byte 1
    b64[di + 1] = table[b1 & 0x3 << 4 + b2 >> 4]    // 2 bits from byte 1 plus 4 from byte 2 
    b64[di + 2] = table[b2 & 0x0f << 2 + b3 >> 6]
    b64[di + 3] = table[b3 & 0x3f]
}

func base64enc(text string) string {
    src := []byte(text)
    srclen := len(src)
    triplets := srclen / 3
    mod3 := srclen % 3
    padding := 0
    if mod3 != 0 {
        padding = 3 - mod3
    }
    b64 := make_b64_slice(src)
    si := 0
    di := 0
    for i := 0; i < triplets; i++ {
        b1 := src[si + 0]
        b2 := src[si + 1]
        b3 := src[si + 2]
        encodeTriplet(b1, b2, b3, b64, di)
        si += 3
        di += 4
    }
    if padding == 2 {
        encodeTriplet(src[si + 0], 0, 0, b64, di)
        b64[di + 2] = paddingchar
        b64[di + 3] = paddingchar
    } else if padding == 1 {
        encodeTriplet(src[si + 0], src[si + 1], 0, b64, di)
        b64[di + 3] = paddingchar
    }
    return string(b64)
}

func main() {
    if len(os.Args) != 2 {
        fmt.Fprintf(os.Stderr, "Wrong number of arguments.\n")
        os.Exit(1)
    }
    encoded := base64enc(os.Args[1])
    fmt.Println(encoded)
}

