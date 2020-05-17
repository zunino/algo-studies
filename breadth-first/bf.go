package main

import "fmt"

type Publisher struct {
	name string
}

type Game struct {
	title     string
	year      int
	publisher *Publisher
}

type PublisherNode struct {
	publisher Publisher
}

type GameNode struct {
	game *Game
}

type Node struct {
	value string
	adj   []*Node
}

func createGraph() map[string]*Node {
	nA := Node{value: "A"}
	nB := Node{value: "B"}
	nC := Node{value: "C"}
	nD := Node{value: "D"}
	nE := Node{value: "E"}
	nF := Node{value: "F"}
	nG := Node{value: "G"}

	nA.adj = []*Node{&nB, &nC, &nD}
	nB.adj = []*Node{&nA, &nC}
	nC.adj = []*Node{&nA, &nB, &nD, &nE, &nF}
	nD.adj = []*Node{&nA, &nC}
	nE.adj = []*Node{&nC, &nF, &nG}
	nF.adj = []*Node{&nC, &nE}
	nG.adj = []*Node{&nE}

	graph := make(map[string]*Node)
	graph["A"] = &nA
	graph["B"] = &nB
	graph["C"] = &nC
	graph["D"] = &nD
	graph["E"] = &nE
	graph["F"] = &nF
	graph["G"] = &nG

	return graph
}

type VisitorFn func(*Node)

func present(node *Node, nodes []*Node) bool {
	for _, n := range nodes {
		if n == node {
			return true
		}
	}
	return false
}

func breadthFirst(startingNode *Node, visitorFn VisitorFn) {
	queue := []*Node{startingNode}
	var visited []*Node
	for len(queue) > 0 {
		node := queue[0]
		queue = queue[1:]
		if present(node, visited) {
			continue
		}
		visitorFn(node)
		visited = append(visited, node)
		queue = append(queue, node.adj...)
	}
}

func printNode(node *Node) {
	fmt.Printf("Visiting node '%s'\n", node.value)
}

func main() {
	graph := createGraph()
	fmt.Println("Breadth-first starting from 'A'")
	breadthFirst(graph["A"], printNode)
	fmt.Println("\nBreadth-first starting from 'C'")
	breadthFirst(graph["C"], printNode)
	fmt.Println("\nBreadth-first starting from 'G'")
	breadthFirst(graph["G"], printNode)
}
