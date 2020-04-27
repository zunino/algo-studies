/**
 * Breadth-first traversal.
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

const tree = {
    value: 0,
    children: [
        { value: 1, children: [ { value: 3, children: [] }, { value: 4, children: [] } ] },
        { value: 2, children: [ { value: 5, children: [] }, { value: 6, children: [] } ] }
    ]
};

function treeBreadthFirst(queue, visit) {
    while (queue.length > 0) {
        let node = queue.shift();
        visit(node);
        queue = queue.concat(node.children);
    }
}

function treeNodeVisitor(node) {
    treeNodeVisitor.values += node.value + " ";
}

treeNodeVisitor.values = "";
treeBreadthFirst([tree], treeNodeVisitor);

console.log("Tree breadth-first traversal:", treeNodeVisitor.values);

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

function breadthFirst(graph, startingNode, visit) {
    const visited = [];
    let queue = [startingNode];
    while (queue.length != 0) {
        const node = queue.shift();
        if (visited.includes(node)) {
            continue;
        }
        visit(node);
        visited.push(node);
        queue = queue.concat(graph[node]);
    }
}

function graphNodeVisitor(node) {
    graphNodeVisitor.values += node + " ";
}

graphNodeVisitor.values = "";
breadthFirst(graph1, "A", graphNodeVisitor);

console.log("Graph breadth-first traversal:", graphNodeVisitor.values);

// --- Starting from a different node ('C')

graphNodeVisitor.values = "";
breadthFirst(graph1, "C", graphNodeVisitor);

console.log("Graph breadth-first traversal (starting from node 'C'):", graphNodeVisitor.values);

// --- Starting from a different node ('G')

graphNodeVisitor.values = "";
breadthFirst(graph1, "G", graphNodeVisitor);

console.log("Graph breadth-first traversal (starting from node 'G'):", graphNodeVisitor.values);

// --- Original tree represented by adjacency list

const graph2 = {
    0: [1, 2],
    1: [0, 3, 4],
    2: [0, 5, 6],
    3: [1],
    4: [1],
    5: [2],
    6: [2]
};

graphNodeVisitor.values = "";
breadthFirst(graph2, 0, graphNodeVisitor);

console.log("Graph breadth-first traversal (original tree):", graphNodeVisitor.values);
