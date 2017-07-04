/**
 * Reverse-order depth-first traversal.
 * July 4th, 2017.
 *
 * Sample tree:   1
 *             /  |  \
 *           2    3    4
 *          / \   |   / \
 *         5   6  7  8   9
 *                 / | \
 *               10 11 12
 *
 */

"use strict";

let tree = {
    value: 1,
    children: [
        { 
            value: 2, 
            children: [
                { value: 5, children: [] },
                { value: 6, children: [] }
            ]
        },
        { 
            value: 3, 
            children: [ 
                { value: 7, children: [] }
            ]
        },
        {
            value: 4,
            children: [
                { 
                    value: 8,
                    children: [
                        { value: 10, children: [] },
                        { value: 11, children: [] },
                        { value: 12, children: [] }
                    ]
                },
                { value: 9, children: [] }
            ]
        }
    ]
};

function depthFirstRev(node, visit) {
    let idx = node.children.length;
    while (--idx >= 0) {
        let child = node.children[idx];
        depthFirstRev(child, visit);
    }
    visit(node);
}

function nodeVisitor(node) {
    nodeVisitor.values += node.value + " ";
}

nodeVisitor.values = "";

depthFirstRev(tree, nodeVisitor);

console.log(nodeVisitor.values);
