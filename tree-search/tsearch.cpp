/**
 * Tree search using depth-first traversal (based on the depth-first traversal example).
 * Created September 16th, 2016, on the occasion of such need coming up at work.
 *
 * C++ version, based on the JavaScript implementation done earlier.
 *
 * Sample tree:   0
 *               / \
 *             1     2
 *            / \   / \
 *           3   4 5   6
 *                / \
 *               7   8
 *
 */

#include <iostream>
#include <vector>
#include <cstdlib>

struct Node {
    int value;
    std::vector<Node> children;
};

Node tree = {0, {
    {1, {
            {3, {}},
            {4, {}}
        }
    },
    {2, {
            {5, {
                    {7, {}},
                    {8, {}}
                }
            },
            {6, {}}
        }
    }
}};

const Node* tree_search(const Node& node, int value) {
    std::cout << "searching node " << node.value << "...\n";
    if (node.value == value) return &node;
    const Node* found = nullptr;
    for (const Node& child : node.children) {
        found = tree_search(child, value);
        if (found) break;
    }
    return found;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Missing search value argument.\n";
        return EXIT_FAILURE;
    }
    int value = std::atoi(argv[1]);
    auto found = tree_search(tree, value);
    if (found) {
        std::cout << "Found it!\n";
    } else {
        std::cout << "Did not find it.\n";
    }
}
