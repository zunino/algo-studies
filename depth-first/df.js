/**
 * Depth-first traversal.
 *
 * Sample tree:   0
 *               / \
 *             1     2
 *            / \   / \
 *           3   4 5   6
 *
 */

"use strict";

let tree = {
    value: 0,
    children: [
        { value: 1, children: [ { value: 3, children: [] }, { value: 4, children: [] } ] },
        { value: 2, children: [ { value: 5, children: [] }, { value: 6, children: [] } ] }
    ]
};

function depthFirst(node, visit) {
    visit(node);
    for (let child of node.children) {
        depthFirst(child, visit);
    }
}

function nodeVisitor(node) {
    nodeVisitor.values += node.value + " ";
}

nodeVisitor.values = "";

depthFirst(tree, nodeVisitor);

console.log(nodeVisitor.values);