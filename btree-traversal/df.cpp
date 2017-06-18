/**
 * Different flavors of depth-first traversal on binary trees: pre-order, in-order
 * and post-order. In-order and post-order traversal of generic trees requires
 * further specification on how to group child nodes as "left" and "right".
 *
 * Created June 17th, 2017, as I was facing a DOM traversal challenge in a project
 * at work.
 *
 * Pre-order: <root>, <left>, <right>
 * In-order: <left>, <root>, <right>
 * Post-order: <left>, <right>, <root>
 *
 * Sample tree:   0
 *               / \
 *             1     2
 *            / \   / \
 *           3   4 5   6
 *                / \
 *               7   8
 *
 * More on tree traversal: https://en.wikipedia.org/wiki/Tree_traversal
 */

#include <iostream>

struct Node {
    int value;
    Node* left = nullptr;
    Node* right = nullptr;
};

Node n3 = {3};
Node n4 = {4};
Node n1 = {1, &n3, &n4};
Node n7 = {7};
Node n8 = {8};
Node n5 = {5, &n7, &n8};
Node n6 = {6};
Node n2 = {2, &n5, &n6};
Node n0 = {0, &n1, &n2};

Node* tree = &n0;

void preorder(const Node* node) {
    if (node == nullptr) return;
    std::cout << node->value << " ";
    preorder(node->left);
    preorder(node->right);
}

void inorder(const Node* node) {
    if (node == nullptr) return;
    inorder(node->left);
    std::cout << node->value << " ";
    inorder(node->right);
}

void postorder(const Node* node) {
    if (node == nullptr) return;
    postorder(node->left);
    postorder(node->right);
    std::cout << node->value << " ";
}

int main(int argc, char* argv[]) {
    std::cout << "Pre-order:  "; preorder(tree);  std::cout << " (expectedi: 0 1 3 4 2 5 7 8 6)\n";
    std::cout << "In-order:   "; inorder(tree);   std::cout << " (expectedi: 3 1 4 0 7 5 8 2 6)\n";
    std::cout << "Post-order: "; postorder(tree); std::cout << " (expectedi: 3 4 1 7 8 5 6 2 0)\n";
}
