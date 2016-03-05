/**
 * Bubble sort implementation. Illustrates the use of std::prev and std::next for obtaining the previous
 * and next iterators, respectively. The reason why operator+ is not being used is because it is only
 * supported by random-access iterators, which would keep the implementation from working on std::list,
 * for instance.
 *
 * Andre Zunino
 * 5 March 2016
 */

#include <vector>
#include <list>
#include <iostream>

template <typename C>
void write(C&& coll, std::ostream& os = std::cout) {
    for (const auto e : coll) {
        os << e << ' ';
    }
    os << '\n';
}

template <typename Iter>
void bubble_sort(Iter first, Iter last) {
    bool modified;
    do {
        modified = false;
        Iter e1 = first;
        while (e1 != std::prev(last)) {
            Iter e2 = std::next(e1);
            if (*e1 > *e2) {
                auto v = *e2;
                *e2 = *e1;
                *e1 = v;
                modified = true;
            }
            ++e1;
        }
    } while (modified);
}

int main() {
    std::vector<int> v{4, 1, 9, 6, 2};
    write(v);
    bubble_sort(v.begin(), v.end());
    write(v);

    std::list<int> l{5, 1, 18, 7, 4, 32, 90, 11, 2};
    write(l);
    bubble_sort(l.begin(), l.end());
    write(l);
}
