package b64dec

import (
    "errors"
)

// This table holds the 64 sextets (6-bit patterns) from the Base64 encoding table.
// They are distributed such that, when decoding, subtracting 43 from each encoded
// character's value yields the right index into this table. E.g. 'T' has the ASCII
// value of 84; 84 - 43 = 41; table[41] = 19 (010011b).
var dectable = [80]byte {
     62, '.', '.', '.',  63,  52,  53,  54,  55,  56,  57,  58,  59,  60,  61, '.',
    '.', '.', '.', '.', '.', '.',   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,
     10,  11,  12,  13,  14,  15,  16,  17,  18,  19,  20,  21,  22,  23,  24,  25,
    '.', '.', '.', '.', '.', '.',  26,  27,  28,  29,  30,  31,  32,  33,  34,  35,
     36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,  48,  49,  50,  51,
}

const toffset = 43
const paddingchar = '='

func decode1byte(src string, si int, dst []byte, di int) {
    sextet1 := dectable[src[si + 0] - toffset]
    sextet2 := dectable[src[si + 1] - toffset]
    dst[di + 0] = sextet1 << 2 + sextet2 >> 4;
}

func decode2bytes(src string, si int, dst []byte, di int) {
    decode1byte(src, si, dst, di)
    sextet2 := dectable[src[si + 1] - toffset]
    sextet3 := dectable[src[si + 2] - toffset]
    dst[di + 1] = sextet2 << 4 + sextet3 >> 2;
}

func decode3bytes(src string, si int, dst []byte, di int) {
    decode2bytes(src, si, dst, di)
    sextet3 := dectable[src[si + 2] - toffset]
    sextet4 := dectable[src[si + 3] - toffset]
    dst[di + 2] = sextet3 << 6 + sextet4;
}

func Base64dec(src string) (string, error) {
    srclen := len(src)
    quadruplets := srclen / 4
    mod4 := srclen % 4
    if mod4 != 0 {
        return "", errors.New("Invalid Base64 input.")
    }
    if quadruplets == 0 {
        return "", nil
    }
    padding := 0
    if src[srclen - 1] == paddingchar {
        padding++
    }
    if src[srclen - 2] == paddingchar {
        padding++
    }
    declen := quadruplets * 3 - padding
    text := make([]byte, declen)
    if padding > 0 {
        quadruplets--
    }
    si := 0
    di := 0
    for i := 0; i < quadruplets; i++ {
        decode3bytes(src, si, text, di)
        si += 4
        di += 3
    }
    if padding == 1 {
        decode2bytes(src, si, text, di)
    } else if padding == 2 {
        decode1byte(src, si, text, di)
    }
    return string(text), nil
}

