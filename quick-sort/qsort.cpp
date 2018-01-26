/**
 * Quick sort implementation.
 *
 * Andre Zunino
 * 16 May 2015
 *
 * Revised on October 2017 to make the changes in-place, reducing the overall
 * runtime complexity of the algorithm.
 */
 
#include <vector>
#include <algorithm>
#include <iostream>
#include <cassert>

template <typename H, typename C>
void print(const H& heading, const C& coll) {
    std::cout << heading;
    int size = coll.size();
    int i = 0;
    for (typename C::const_reference elem : coll) {
        std::cout << elem;
        if (++i < size) {
            std::cout << ' ';
        }
    }
}

template <typename H, typename C>
void println(const H& heading, const C& coll) {
    print(heading, coll);
    std::cout << '\n';
}

void quicksort(std::vector<int>& coll, int start, int end) {
    if ((end - start < 2) || coll.size() < 2) {
        return;
    }
    int pivot = coll[start];
    int wall = start + 1;
    for (int i = wall; i < end; ++i) {
        int elem = coll[i];
        if (pivot > elem) {
            if (i != wall) {
                coll[i] = coll[wall];
                coll[wall] = elem;
            }
            ++wall;
        }
    }
    coll[start] = coll[wall - 1];
    coll[wall - 1] = pivot;
    quicksort(coll, start, wall - 1);
    quicksort(coll, wall, end);
}

void test_quicksort(std::initializer_list<int> elements,
                    std::initializer_list<int> sorted_elements) {
    assert (elements.size() == sorted_elements.size());
    std::vector<int> vec { elements };
    std::vector<int> sorted_vec(vec);
    quicksort(sorted_vec, 0, sorted_vec.size());
    print("[", elements);
    std::cout << "] => [";
    print("", sorted_vec);
    std::cout << "]\n";
    assert (sorted_vec.size() == elements.size());
    assert (std::equal(sorted_vec.begin(), sorted_vec.end(), sorted_elements.begin()));
}

int main() {
    test_quicksort({7}, {7});
    test_quicksort({7, 4}, {4, 7});
    test_quicksort({7, 4, 9}, {4, 7, 9});
    test_quicksort({4, 3, 19, 6, 2}, {2, 3, 4, 6, 19});
    test_quicksort({4, 12, 6, 1, 5}, {1, 4, 5, 6, 12});
    test_quicksort({5, 8, 2, 6, 9, 1}, {1, 2, 5, 6, 8, 9});
    test_quicksort({2, 8, 5, 9, 3, 1, 4, 5}, {1, 2, 3, 4, 5, 5, 8, 9});
    test_quicksort({4, 10, 1, 6, 3, 8, 2, 4, 0, 5}, {0, 1, 2, 3, 4, 4, 5, 6, 8, 10});
}
