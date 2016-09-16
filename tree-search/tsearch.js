/**
 * Tree search using depth-first traversal (based on the depth-first traversal example).
 * Created September 16th, 2016, on the occasion of such need coming up at work.
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

"use strict";

let tree = {
    value: 0, children: [
        {
            value: 1, children: [
                {value: 3, children: []},
                {value: 4, children: []}
            ]
        },
        {
            value: 2, children: [
                {
                    value: 5, children: [
                        {value: 7, children: []},
                        {value: 8, children: []}
                    ]
                },
                {value: 6, children: []}
            ]
        }
    ]
};

function treeSearch(node, value) {
    console.log(`visiting node ${node.value}...`);
    if (node.value === value) {
        return node;
    } else {
        let result = null;
        for (let child of node.children) {
            result = treeSearch(child, value);
            if (result) break;
        }
        return result;
    }
}

