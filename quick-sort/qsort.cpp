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
    for (typename C::value_type elem : coll) {
        std::cout << elem << ' ';
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
    int wall = start;
    for (int i = 1; i < end; ++i) {
        int elem = coll[i];
        if (pivot > elem) {
            coll[i] = coll[wall];
            coll[wall++] = elem;
        }
    }
    // Need to move the pivot to *wall, its final location.
    // The question is: where is the pivot?
    quicksort(coll, start, wall);
    quicksort(coll, wall + 1, end);
}

void test_quicksort(std::initializer_list<int> elements,
                    std::initializer_list<int> sorted_elements) {
    assert (elements.size() == sorted_elements.size());
    std::vector<int> vec { elements };
    std::vector<int> sorted_vec(vec);
    quicksort(sorted_vec, 0, sorted_vec.size());
    std::cout << "quicksort { ";
    print("", elements);
    std::cout << "} : ";
    println("", sorted_vec);
    assert (sorted_vec.size() == elements.size());
    assert (std::equal(sorted_vec.begin(), sorted_vec.end(), sorted_elements.begin()));
}

int main() {
    //test_quicksort({7},                 {7});
    //test_quicksort({7, 4},              {4, 7});
    //test_quicksort({7, 4, 9},           {4, 7, 9});
    test_quicksort({4, 3, 19, 6, 2},    {2, 3, 4, 6, 19});
}

