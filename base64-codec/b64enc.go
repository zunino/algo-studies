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

func base64enc(text string) string {
    src := []byte(text)
    mod3 := len(src) % 3
    padding := 0
    if mod3 != 0 {
        padding = 3 - mod3
    }
    b64 := make_b64_slice(src)
    srclen := len(src)
    di := 0
    for si := 0; si < srclen; {
        b1 := src[si]
        b64[di] = table[b1 >> 2]                      // 6 most-significant bits of byte 1
        di++
        si++
        if si == srclen {
            b64[di] = table[b1 & 0x3 << 4]
            di++
            break;
        }
        b2 := src[si]
        b64[di] = table[(b1 & 0x3) << 4 + b2 >> 4]    // 2 bits from byte 1 plus 4 from byte 2 
        di++
        si++
        if si == srclen {
            b64[di] = table[b2 & 0x0f << 2]
            di++
            break;
        }
        b3 := src[si]
        si++
        b64[di] = table[(b2 & 0x0f) << 2 + b3 >> 6]
        di++
        b64[di] = table[b3 & 0x3f]
        di++
    }
    for i := 0; i < padding; i++ {
        b64[di] = paddingchar
        di++
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

