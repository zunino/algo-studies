#include <vector>
#include <list>
#include <algorithm>
#include <iterator>
#include <iostream>

template <typename Coll>
void write(Coll&& coll, std::ostream& os = std::cout) {
	for (const auto& elem : coll) {
		os << elem << ' ';
	}
	os << '\n';
}

template <typename Iter>
void heapsort(Iter first, Iter last) {
	std::make_heap(first, last);
	Iter end = last;
	while (end != first) {
		std::pop_heap(first, end);
		end = std::prev(end);
	}
}

int main() {
	std::vector<int> v {5, 78, 10, 12, 1, 45, 16};
	write(v);
	heapsort(v.begin(), v.end());
	write(v);

	std::list<int> l {17, 3, 8, 22, 35, 4, 101, 12, 7, 32};
	write(l);
	heapsort(l.begin(), l.end());
	write(l);
}
