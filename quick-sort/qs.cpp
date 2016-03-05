/**
 * Quick sort implementation.
 *
 * Andre Zunino
 * 16 May 2015
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

std::vector<int> quicksort(const std::vector<int>& coll) {
    if (coll.size() < 2) {
        return coll;
    }
    int pivot = coll[0];
    std::vector<int> left;
    std::vector<int> right;
    for (int i = 1; i < coll.size(); ++i) {
        int elem = coll[i];
        if (elem > pivot) {
            right.push_back(elem);
        } else {
            left.push_back(elem);
        }
    }
    left = quicksort(left);
    right = quicksort(right);
    std::vector<int> rearranged_coll;
    rearranged_coll.insert(rearranged_coll.end(), left.begin(), left.end());
    rearranged_coll.push_back(pivot);
    rearranged_coll.insert(rearranged_coll.end(), right.begin(), right.end());
    return rearranged_coll;
}

void test_quicksort(std::initializer_list<int> elements,
                    std::initializer_list<int> sorted_elements) {
    assert (elements.size() == sorted_elements.size());
    std::vector<int> vec { elements };
    std::vector<int> sorted_vec = quicksort(vec);
    std::cout << "quicksort { ";
    print("", elements);
    std::cout << "} : ";
    println("", sorted_vec);
    assert (sorted_vec.size() == elements.size());
    assert (std::equal(sorted_vec.begin(), sorted_vec.end(), sorted_elements.begin()));
}

int main() {
    test_quicksort({7},                 {7});
    test_quicksort({7, 4},              {4, 7});
    test_quicksort({7, 4, 9},           {4, 7, 9});
    test_quicksort({4, 3, 19, 6, 2},    {2, 3, 4, 6, 19});
}

