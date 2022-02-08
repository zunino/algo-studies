/*
 * Simple example to exercise the structure of recursive, backtracking
 * algorithms.
 *
 * Given an undirected graph of nodes where each node is associated with a
 * numeric value, find all paths with ascending values.
 *
 * Notes:
 *   - If n1 and n2 are connected, then each will be in the other's list of
 *     connections.
 *   - The list of visited nodes and the list of nodes forming the
 *     current path are passed by value in the recursive calls, so that they
 *     revert to their original values when backtracking.
 *   - Wrote this example as I was working on Day 12 of the Advent of Code
 *     2021 programming challenge event.
 *
 * Andre Zunino <neyzunino@gmail.com>
 * 8 February 2022
 */

#include <algorithm>
#include <iostream>
#include <iterator>
#include <list>
#include <memory>
#include <sstream>
#include <string>
#include <vector>

const int START_VALUE = -999;
const int END_VALUE = 999;

struct Node {
    Node(int n) : value(n) {}
    int value;
    std::list<std::shared_ptr<Node>> connections;
};

std::shared_ptr<Node> make_graph() {
    auto n_end = std::make_shared<Node>(END_VALUE);
    auto n_7 = std::make_shared<Node>(7);
    auto n_8 = std::make_shared<Node>(8);
    auto n_11 = std::make_shared<Node>(11);
    auto n_12 = std::make_shared<Node>(12);
    auto n_10 = std::make_shared<Node>(10);
    auto n_4 = std::make_shared<Node>(4);
    auto n_5 = std::make_shared<Node>(5);
    auto n_2 = std::make_shared<Node>(2);
    auto n_3 = std::make_shared<Node>(3);

    n_3->connections.push_back(n_2);
    n_3->connections.push_back(n_4);
    n_3->connections.push_back(n_5);

    n_2->connections.push_back(n_3);
    n_2->connections.push_back(n_8);

    n_4->connections.push_back(n_3);
    n_4->connections.push_back(n_8);
    n_4->connections.push_back(n_5);
    n_4->connections.push_back(n_7);

    n_5->connections.push_back(n_3);
    n_5->connections.push_back(n_4);
    n_5->connections.push_back(n_10);

    n_8->connections.push_back(n_2);
    n_8->connections.push_back(n_end);

    n_10->connections.push_back(n_5);
    n_10->connections.push_back(n_7);
    n_10->connections.push_back(n_11);
    n_10->connections.push_back(n_12);

    n_7->connections.push_back(n_4);
    n_7->connections.push_back(n_10);
    n_7->connections.push_back(n_end);

    n_11->connections.push_back(n_10);
    n_11->connections.push_back(n_end);

    n_12->connections.push_back(n_10);
    n_12->connections.push_back(n_end);

    return n_3;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::shared_ptr<T> &ptr) {
    return os << ptr->value;
}

template <typename Iterator> std::string join(Iterator begin, Iterator end) {
    std::ostringstream oss;
    const int size = std::distance(begin, end);
    for (int i = 0; i < size; ++i) {
        oss << *begin++;
        if (i < size - 1) {
            oss << ", ";
        }
    }
    return oss.str();
}

void visit(std::shared_ptr<Node> node, std::list<std::shared_ptr<Node>> visited,
           std::vector<int> path, int value) {
    std::cout << "Visiting " << node->value
              << " | visited: {" << join(visited.begin(), visited.end()) << "}\n";

    if (node->value == END_VALUE) {
        std::cout << "=> Path: {" << join(path.begin(), path.end()) << "}\n";
        path.pop_back();
        return;
    }

    visited.push_back(node);

    if (node->value < value) {
        std::cout << "* Node value " << node->value << " less than base value "
                  << value << "; returning\n";
        return;
    }

    path.push_back(node->value);

    for (std::shared_ptr<Node> conn : node->connections) {
        if (std::find(visited.begin(), visited.end(), conn) != visited.end()) {
            continue;
        }
        visit(conn, visited, path, node->value);
    }
}

int main() {
    auto graph = make_graph();
    std::list<std::shared_ptr<Node>> visited;
    std::vector<int> path;
    visit(graph, visited, path, START_VALUE);
}
