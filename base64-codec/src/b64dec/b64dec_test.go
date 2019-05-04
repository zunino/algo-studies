package b64dec

import (
    "testing"
)

func Test_decode_TWFu(t *testing.T) {
    result := Base64dec("TWFu")
    expected := "Man"
    if result != expected {
        t.Errorf("TWFu should have been decoded to %s (was %s)", expected, result)
    }
}

func Test_decode_TWEeqsign(t *testing.T) {
    result := Base64dec("TWE=")
    expected := "Ma"
    if result != expected {
        t.Errorf("TWE= should have been decoded to %s (was %s)", expected, result)
    }
}

func Test_decode_TQeqsigneqsign(t *testing.T) {
    result := Base64dec("TQ==")
    expected := "M"
    if result != expected {
        t.Errorf("TQ== should have been decoded to %s (was %s)", expected, result)
    }
}

func Test_decode_big_sentence(t *testing.T) {
    sentence := `TWFuIGlzIGRpc3Rpbmd1aXNoZWQsIG5vdCBvbmx5IGJ5IGhpcyByZWFzb24s` +
                `IGJ1dCBieSB0aGlzIHNpbmd1bGFyIHBhc3Npb24gZnJvbSBvdGhlciBhbmlt` +
                `YWxzLCB3aGljaCBpcyBhIGx1c3Qgb2YgdGhlIG1pbmQsIHRoYXQgYnkgYSBw` +
                `ZXJzZXZlcmFuY2Ugb2YgZGVsaWdodCBpbiB0aGUgY29udGludWVkIGFuZCBp` +
                `bmRlZmF0aWdhYmxlIGdlbmVyYXRpb24gb2Yga25vd2xlZGdlLCBleGNlZWRz` +
                `IHRoZSBzaG9ydCB2ZWhlbWVuY2Ugb2YgYW55IGNhcm5hbCBwbGVhc3VyZS4=`
    result := Base64dec(sentence)
    expected := `Man is distinguished, not only by his reason, but by this ` +
                `singular passion from other animals, which is a lust of the ` +
                `mind, that by a perseverance of delight in the continued ` +
                `and indefatigable generation of knowledge, exceeds the ` +
                `short vehemence of any carnal pleasure.`
    if result != expected {
        t.Errorf("Result should have been decoded to %s (was %s)", expected, result)
    }
}

