#include <algorithm>
#include <functional>
#include <initializer_list>
#include <ostream>
#include <queue>
#include <iostream>
#include <vector>
#include <map>
#include <climits>

using Distance = unsigned;

struct Node {
    char label;
};

struct Graph {
    Graph(std::initializer_list<Node> nodes);
    void connect(const Node& n1, const Node& n2, Distance distance);
    const Node& operator[](char label) const;
    std::map<char, Node> nodes;
    std::map<char, std::map<char, Distance>> adjacencies;
};

Graph::Graph(std::initializer_list<Node> nodes) {
    for (auto node : nodes) {
        this->nodes[node.label] = node;
    }
}

void Graph::connect(const Node& n1, const Node& n2, Distance distance) {
    adjacencies[n1.label][n2.label] = distance;
    adjacencies[n2.label][n1.label] = distance;
}

const Node& Graph::operator[](char label) const {
    return this->nodes.at(label);
}

std::ostream& operator<<(std::ostream& os, const Graph& g) {
    os << "= Nodes\n";
    os << "  ";
    for (const auto& [label, node] : g.nodes) {
        os << label << ' ';
    }
    os << "\n\n= Connections\n";
    for (const auto& [n1_label, n1_adjacencies] : g.adjacencies) {
        for (const auto& [n2_label, distance] : n1_adjacencies) {
            os << "  " << n1_label << " --[" << distance << "]-- " << n2_label << '\n';
        }
    }
    return os;
}

struct DistanceInfo {
    char label;
    unsigned distance = UINT_MAX;
    char from_label = '_';
};

std::ostream& operator<<(std::ostream& os, const DistanceInfo& d) {
    os << d.label << " - " << d.distance << " through " << d.from_label;
    return os;
}

using DistanceMap = std::map<char, DistanceInfo>;

struct DistanceComparator {
    DistanceComparator(const DistanceMap& distance_map)
    : distance_map{distance_map} {}
    bool operator()(char node_label_1, char node_label_2) {
        const auto& dist_1 = distance_map.at(node_label_1);
        const auto& dist_2 = distance_map.at(node_label_2);
        return dist_1.distance > dist_2.distance;
    }
    const DistanceMap& distance_map;
};

DistanceMap dijkstra(const Graph& graph, char source_node_label) {
    DistanceMap distance_map;
    DistanceComparator distance_comparator{distance_map};

    std::priority_queue<char,
        std::vector<char>,
        decltype(distance_comparator)> unvisited_nodes{distance_comparator};

    // source node gets distance 0; other nodes start with "infinite" distance
    for (auto [label, node] : graph.nodes) {
        DistanceInfo distance_info{.label = label, .from_label = source_node_label};
        if (label == source_node_label) {
            distance_info.distance = 0;
            unvisited_nodes.push(source_node_label);
        }
        distance_map.insert({label, distance_info});
    }

    while (!unvisited_nodes.empty()) {
        char curr_node_label = unvisited_nodes.top();
        unvisited_nodes.pop();

        const auto& neighbors = graph.adjacencies.at(curr_node_label);
        const DistanceInfo& curr_node_dist_info = distance_map.at(curr_node_label);

        for (auto [neighbor_label, neighbor_edge_distance] : neighbors) {
            auto& neighbor_dist_info = distance_map.at(neighbor_label);
            if (neighbor_dist_info.distance > neighbor_edge_distance + curr_node_dist_info.distance) {
                neighbor_dist_info.distance = neighbor_edge_distance + curr_node_dist_info.distance;
                neighbor_dist_info.from_label = curr_node_label;
                unvisited_nodes.push(neighbor_label);
            }
        }
    }

    return distance_map;
}

std::vector<char> distance_map_to_path(const DistanceMap& distance_map, char start_label, char end_label) {
    std::vector<char> path;
    char curr_label = end_label;
    while (curr_label != start_label) {
        const auto& distance_info = distance_map.at(curr_label);
        path.push_back(curr_label);
        curr_label = distance_info.from_label;
    }
    path.push_back(start_label);
    std::reverse(path.begin(), path.end());
    return path;
}

Graph make_graph() {
    Node a{'A'};
    Node b{'B'};
    Node c{'C'};
    Node d{'D'};
    Node e{'E'};
    Node f{'F'};

    Graph g{a, b, c, d, e, f};

    g.connect(a, b, 2);
    g.connect(a, d, 8);
    g.connect(b, e, 6);
    g.connect(b, d, 5);
    g.connect(d, e, 3);
    g.connect(d, f, 2);
    g.connect(e, f, 1);
    g.connect(c, e, 9);
    g.connect(c, f, 3);

    return g;
}

int main() {
    Graph graph = make_graph();
    /* std::cout << graph << '\n'; */

    DistanceMap distance_map = dijkstra(graph, 'A');

    // debug
    std::cout << "\n-- distance info\n";
    for (auto [label, dist_info] : distance_map) {
        std::cout << dist_info << '\n';
    }

    auto path_from_a_to_c = distance_map_to_path(distance_map, 'A', 'C');
    std::cout << "\nshortest path from A to C:\n    ";
    for (auto label : path_from_a_to_c) {
        if (label != 'A') std::cout << " \u2192  ";
        std::cout << label;
    }
    std::cout << '\n';
}
