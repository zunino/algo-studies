# Base64 CODEC

Andre Zunino <neyzunino@gmail.com>
May 2019

Implementation of Base64 encoding and decoding. The main source was the
[Wikipedia article on the topic](https://en.wikipedia.org/wiki/Base64).

## Usage

```
<b64> <operation> <input>
```

Where:

* `<b64>` is the `go run` invocation (examples below)
* `operation` is one of `e` (encode) and `d` (decode)
* `input` is the content to be encoded or decoded.

### Encoding

```
GOPATH=$(pwd) go run b64.go e "This is a sentence to be encoded."
```

### Decoding

```
GOPATH=$(pwd) go run b64.go d "VGhpcyBpcyBhIHNlbnRlbmNlIHRvIGJlIGVuY29kZWQu"
```


## Note

Since the Bas64 codec Go implementation has been reorganized into
packages, it is important to remember that the `GOPATH` environment
variable needs to be set in order for the `go` command to properly
resolve the import directives.

