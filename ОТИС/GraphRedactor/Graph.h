#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>
#include <algorithm>
#include <fstream>
#include <unordered_map>
#include <queue>
#include <unordered_set>
#include <iomanip>

// Структура для узла
struct Node {
    std::string name;
    std::string color;
};

// Структура для дуги
struct Edge {
    std::string from;
    std::string to;
    bool directed;
    std::string color;

    bool operator==(const Edge& other) const { 
        return from == other.from && to == other.to && directed == other.directed && color == other.color; 
    }
};

// Класс графа
class Graph {
public:
    Graph();
    Graph(const std::string& graphName);
    void addNode(const std::string& name, const std::string& color = "white");
    void removeNode(const std::string& name);
    void addEdge(const std::string& from, const std::string& to, bool directed = false, const std::string& color = "black");
    void removeEdge(const std::string& from, const std::string& to);
    void renameNode(const std::string& oldName, const std::string& newName);
    void setNodeColor(const std::string& name, const std::string& color);
    void setEdgeColor(const std::string& from, const std::string& to, const std::string& color);
    void printGraphInfo() const;
    void printAdjacencyMatrix() const;

    void printIncidenceMatrix() const;
    bool isEulerian() const;
    void convertToBinaryTree();
    void convertToTree();
    void hamiltonianCycleUtil(std::vector<std::string>& path, int pos) const;
    void findHamiltonianCycles() const;
    int calculateDiameter() const;
    int calculateRadius() const;
    std::string findGraphCenter() const;
    Graph tensorProduct(const Graph& other) const;
    Graph cartesianProduct(const Graph& other) const;
    Graph unionGraph(const Graph& other) const;
    Graph intersectionGraph(const Graph& other) const;
    Graph combinationGraph(const Graph& other) const;
    Graph complementGraph() const;

    std::string getName() const;

private:
    std::string name;
    std::map<std::string, Node> nodes;
    std::vector<Edge> edges;
    std::map<std::string, std::string> parent;
    std::map<std::string, std::vector<std::string>> adj;


    void bfsConvert(const std::string& start, std::unordered_map<std::string, bool>& visited);
    void bfs(const std::string& startNode);
    std::string bfs(const std::string& start, std::map<std::string, int>& distances) const;
    bool isSafe(const std::string& v, const std::vector<std::string>& path, int pos) const;
};