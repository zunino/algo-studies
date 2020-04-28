/**
 * Depth-first traversal.
 *
 * The first implementation does not contain checks for visited nodes.
 * Therefore, it will only work when there are no cycles in the graph,
 * i.e. trees.
 *
 * Sample tree:   0
 *               / \
 *             1     2
 *            / \   / \
 *           3   4 5   6
 *
 * The second implementation adds the aforementioned checks and becomes
 * a generic solution to any graph.
 *
 * Sample graph:    A---D
 *                 / \ /
 *                B---C--E---G
 *                    | /
 *                    |/
 *                    F
 */

"use strict";

let tree = {
    value: 0,
    children: [
        { value: 1, children: [ { value: 3, children: [] }, { value: 4, children: [] } ] },
        { value: 2, children: [ { value: 5, children: [] }, { value: 6, children: [] } ] }
    ]
};

function treeDepthFirst(node, visit) {
    visit(node);
    for (const child of node.children) {
        treeDepthFirst(child, visit);
    }
}

function treeNodeVisitor(node) {
    treeNodeVisitor.values += node.value + " ";
}

treeNodeVisitor.values = "";
treeDepthFirst(tree, treeNodeVisitor);

console.log("Tree depth-first traversal:", treeNodeVisitor.values);

// -- Generic implementation allowing cycles

const graph1 = {
    "A": ["B", "C", "D"],
    "B": ["A", "C"],
    "C": ["A", "B", "D", "E", "F"],
    "D": ["A", "C"],
    "E": ["C", "F", "G"],
    "F": ["C", "E"],
    "G": ["E"]
};

function depthFirst(graph, node, visit, visited = []) {
    visit(node);
    visited.push(node);
    for (const neighboor of graph1[node]) {
        if (visited.includes(neighboor)) {
            continue;
        }
        depthFirst(graph, neighboor, visit, visited);
    }
}

function graphNodeVisitor(node) {
    graphNodeVisitor.values += node + " ";
}

graphNodeVisitor.values = "";
depthFirst(graph1, "A", graphNodeVisitor);

console.log("Graph depth-first traversal:", graphNodeVisitor.values);

// --- Starting from a different node ('C')

graphNodeVisitor.values = "";
depthFirst(graph1, "C", graphNodeVisitor);

console.log("Graph depth-first traversal (starting from node 'C'):", graphNodeVisitor.values);

// --- Starting from a different node ('G')

graphNodeVisitor.values = "";
depthFirst(graph1, "G", graphNodeVisitor);

console.log("Graph depth-first traversal (starting from node 'G'):", graphNodeVisitor.values);

