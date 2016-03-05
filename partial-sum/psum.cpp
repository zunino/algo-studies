/**
 * Simple implementation of a partial sums algorithm.
 *
 * Andre Zunino
 * 4 March 2016
 */

#include <iterator>
#include <vector>
#include <set>
#include <list>
#include <iostream>

template <typename ConstIter, typename Iter>
Iter partial_sum(ConstIter first, ConstIter last, Iter tgt) {
    *tgt = *first;
    while (first != last) {
        auto prev = tgt;
        *++tgt = *prev + *++first;
    }
    return tgt;
}

template <typename C>
void write(C&& coll, std::ostream& os = std::cout) {
    for (const auto e : coll) {
        os << e << ' ';
    }
    os << '\n';
}

int main() {
    std::vector<int> v{1, 2, 3, 4, 5};
    std::vector<int> w(v.size());
    partial_sum(v.begin(), v.end(), w.begin());
    write(v);
    write(w);

    std::list<int> l{3, 8, 10, 4, 1};
    partial_sum(l.begin(), l.end(), w.begin());
    write(l);
    write(w);
    
    std::set<int> s{3, 5, 12, 18, 20};
    partial_sum(s.begin(), s.end(), w.begin());
    write(s);
    write(w);
}
