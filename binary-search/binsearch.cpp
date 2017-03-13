#include <iostream>

template <typename C>
void print(const C& collection, std::ostream& out = std::cout) {
    const char* const SEP = ", ";
    for (auto iter = std::begin(collection); iter != std::end(collection); ++iter) {
        out << *iter;
        if (iter + 1 != std::end(collection)) {
            out << SEP;
        }
    }
    out << '\n';
}

int binary_search(const int* const arr, int size, int elem) {
    int si = 0;
    int ei = size - 1;
    if ((ei - si) <= 0) return -1;
    do {
        int mi = (si + ei) / 2;
        if (arr[mi] > elem) {
            ei = mi - 1;
        } else if (arr[mi] < elem) {
            si = mi + 1;
        } else {
            return mi;
        }
    } while (ei - si >= 0);
    return -1;
}

int main() {
    std::ostream& out = std::cout;
    int arr[] = {4, 9, 10, 16, 32, 40, 42, 64, 96, 100};
    print(arr);
    const int SIZE = sizeof arr / sizeof (int);
    for (int elem : arr) {
        out << elem << ": " << binary_search(arr, SIZE, elem) << '\n';
    }
}
