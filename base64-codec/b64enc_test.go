package main

import (
    "testing"
)

func Test_make_b64_slice_for_input_ABC(t *testing.T) {
    result := make_b64_slice([]byte("ABC"))
    if len(result) != 4 {
        t.Errorf("Length should have been 4")
    }
}

func Test_make_b64_slice_for_input_AB(t *testing.T) {
    result := make_b64_slice([]byte("AB"))
    if len(result) != 4 {
        t.Errorf("Length should have been 4")
    }
}

func Test_make_b64_slice_for_input_A(t *testing.T) {
    result := make_b64_slice([]byte("A"))
    if len(result) != 4 {
        t.Errorf("Length should have been 4")
    }
}

func Test_encode_ABC(t *testing.T) {
    result := base64enc("ABC")
    expected := "QUJD"
    if result != expected {
        t.Errorf("ABC should have been encoded as %s (was %s)", expected, result)
    }
}

func Test_encode_AB(t *testing.T) {
    result := base64enc("AB")
    expected := "QUI="
    if result != expected {
        t.Errorf("AB should have been encoded as %s (was %s)", expected, result)
    }
}

func Test_encode_A(t *testing.T) {
    result := base64enc("A")
    expected := "QQ=="
    if result != expected {
        t.Errorf("A should have been encoded as %s (was %s)", expected, result)
    }
}

func Test_encode_big_sentence(t *testing.T) {
    sentence := `Man is distinguished, not only by his reason, but by this ` +
                `singular passion from other animals, which is a lust of the ` +
                `mind, that by a perseverance of delight in the continued ` +
                `and indefatigable generation of knowledge, exceeds the ` +
                `short vehemence of any carnal pleasure.`
    result := base64enc(sentence)
    expected := `TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24s` +
                `IGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmlt` +
                `YWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBw` +
                `ZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBp` +
                `bmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRz` +
                `IHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=`
    if result != expected {
        t.Errorf("Result should have been encoded as %s (was %s)", expected, result)
    }
}

