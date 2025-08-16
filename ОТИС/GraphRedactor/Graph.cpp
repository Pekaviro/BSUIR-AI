#include "Graph.h"

Graph::Graph() : name("Unnamed") {}

Graph::Graph(const std::string& graphName) : name(graphName) {}

// Добавление узла
void Graph::addNode(const std::string& name, const std::string& color) {
    if (nodes.find(name) != nodes.end()) {
        std::cout << "Узел с таким именем уже существует!" << std::endl;
        return;
    }
    nodes[name] = { name, color };
}

// Удаление узла
void Graph::removeNode(const std::string& name) {
    if (nodes.find(name) == nodes.end()) {
        std::cout << "Узел не найден!" << std::endl;
        return;
    }
    nodes.erase(name);

    // Удаляем все дуги, связанные с этим узлом
    edges.erase(
        std::remove_if(edges.begin(), edges.end(),
            [&name](const Edge& edge) { return edge.from == name || edge.to == name; }),
        edges.end());
}

// Добавление дуги
void Graph::addEdge(const std::string& from, const std::string& to, bool directed, const std::string& color) {
    if (nodes.find(from) == nodes.end() || nodes.find(to) == nodes.end()) {
        std::cout << "Один из узлов не найден!" << std::endl;
        return;
    }
    edges.push_back({ from, to, directed, color });

    // Обновление списка смежности 
    adj[from].push_back(to); 
    if (!directed) { 
        adj[to].push_back(from); 
    }
}

// Удаление дуги
void Graph::removeEdge(const std::string& from, const std::string& to) {
    edges.erase(
        std::remove_if(edges.begin(), edges.end(),
            [&from, &to](const Edge& edge) { return edge.from == from && edge.to == to; }),
        edges.end());
}

// Переименование узла
void Graph::renameNode(const std::string& oldName, const std::string& newName) {
    if (nodes.find(oldName) == nodes.end()) {
        std::cout << "Узел не найден!" << std::endl;
        return;
    }
    if (nodes.find(newName) != nodes.end()) {
        std::cout << "Узел с таким именем уже существует!" << std::endl;
        return;
    }
    nodes[newName] = nodes[oldName];
    nodes[newName].name = newName;
    nodes.erase(oldName);

    // Обновляем дуги
    for (auto& edge : edges) {
        if (edge.from == oldName) edge.from = newName;
        if (edge.to == oldName) edge.to = newName;
    }
}

// Изменение цвета узла
void Graph::setNodeColor(const std::string& name, const std::string& color) {
    if (nodes.find(name) == nodes.end()) {
        std::cout << "Узел не найден!" << std::endl;
        return;
    }
    nodes[name].color = color;
}

// Изменение цвета дуги
void Graph::setEdgeColor(const std::string& from, const std::string& to, const std::string& color) {
    for (auto& edge : edges) {
        if (edge.from == from && edge.to == to) {
            edge.color = color;
            return;
        }
    }
    std::cout << "Дуга не найдена!" << std::endl;
}

// Печать графа в виде матрицы смежности
void Graph::printAdjacencyMatrix() const {
    std::cout << "Граф, представленный матрицей смежности: " << name << std::endl;

    // Создаем вектор для хранения имен узлов
    std::vector<std::string> nodeNames;
    for (const auto& nodePair : nodes) {
        nodeNames.push_back(nodePair.first);
    }

    // Создаем матрицу смежности
    std::vector<std::vector<int>> adjacencyMatrix(nodeNames.size(), std::vector<int>(nodeNames.size(), 0));

    // Заполняем матрицу смежности
    for (const auto& edge : edges) {
        auto fromIt = std::find(nodeNames.begin(), nodeNames.end(), edge.from);
        auto toIt = std::find(nodeNames.begin(), nodeNames.end(), edge.to);
        if (fromIt != nodeNames.end() && toIt != nodeNames.end()) {
            int fromIndex = std::distance(nodeNames.begin(), fromIt);
            int toIndex = std::distance(nodeNames.begin(), toIt);
            adjacencyMatrix[fromIndex][toIndex] = 1;
            if (!edge.directed) {
                adjacencyMatrix[toIndex][fromIndex] = 1;
            }
        }
    }

    // Печатаем матрицу смежности
    std::cout << std::setw(4) << "  ";
    for (const auto& nodeName : nodeNames) {
        std::cout << std::setw(3) << nodeName << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < nodeNames.size(); ++i) {
        std::cout << std::setw(3) << nodeNames[i] << " ";
        for (size_t j = 0; j < nodeNames.size(); ++j) {
            std::cout << std::setw(3) << adjacencyMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Вывод информации о графе
void Graph::printGraphInfo() const {
    std::cout << "Граф: " << name << std::endl;
    std::cout << "Количество узлов: " << nodes.size() << std::endl;
    std::cout << "Количество дуг: " << edges.size() << std::endl;

    for (const auto& nodePair : nodes) {
        const auto& nodeName = nodePair.first;
        const auto& node = nodePair.second;
        std::cout << "Узел " << nodeName << " (цвет: " << node.color << ")" << std::endl;
    }
}

// Вывод информации о графе: матрица инцидентности
void Graph::printIncidenceMatrix() const {
    std::cout << "Граф, представленный матрицей инцидентности: " << name << std::endl;

    // Создаем вектор для хранения имен узлов
    std::vector<std::string> nodeNames;
    for (const auto& nodePair : nodes) {
        nodeNames.push_back(nodePair.first);
    }

    // Создаем матрицу инцидентности
    std::vector<std::vector<int>> incidenceMatrix(nodeNames.size(), std::vector<int>(edges.size(), 0));

    // Заполняем матрицу инцидентности
    for (size_t i = 0; i < edges.size(); ++i) {
        const auto& edge = edges[i];
        auto fromIt = std::find(nodeNames.begin(), nodeNames.end(), edge.from);
        auto toIt = std::find(nodeNames.begin(), nodeNames.end(), edge.to);
        if (fromIt != nodeNames.end() && toIt != nodeNames.end()) {
            int fromIndex = std::distance(nodeNames.begin(), fromIt);
            int toIndex = std::distance(nodeNames.begin(), toIt);
            incidenceMatrix[fromIndex][i] = 1;
            incidenceMatrix[toIndex][i] = edge.directed ? -1 : 1;
        }
    }

    // Печатаем матрицу инцидентности
    std::cout << std::setw(3) << "  ";
    for (size_t i = 0; i < edges.size(); ++i) {
        std::cout << std::setw(2) << "e" << i << " ";
    }
    std::cout << std::endl;

    for (size_t i = 0; i < nodeNames.size(); ++i) {
        std::cout << std::setw(3) << nodeNames[i] << " ";
        for (size_t j = 0; j < edges.size(); ++j) {
            std::cout << std::setw(3) << incidenceMatrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

// Проверка, является ли граф эйлеровым
bool Graph::isEulerian() const {
    // Граф эйлеров, если все вершины имеют четную степень
    for (const auto& nodePair : nodes) {
        int degree = 0;
        for (const auto& edge : edges) {
            if (edge.from == nodePair.first || edge.to == nodePair.first) {
                degree++;
            }
        }
        if (degree % 2 != 0) {
            return false;
        }
    }
    return true;
}

// Приведение произвольного графа к бинарному дереву
void Graph::convertToBinaryTree() {
    if (adj.empty()) return;

    std::unordered_map<std::string, bool> visited;
    for (const auto& node : adj) {
        visited[node.first] = false;
    }

    bfsConvert(adj.begin()->first, visited);
}

void Graph::bfsConvert(const std::string& start, std::unordered_map<std::string, bool>& visited) {
    std::queue<std::string> q;
    q.push(start);
    visited[start] = true;

    while (!q.empty()) {
        std::string node = q.front();
        q.pop();

        std::vector<std::string> children;
        for (const std::string& neighbor : adj[node]) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                children.push_back(neighbor);
                q.push(neighbor);
            }
        }

        // Преобразование в бинарное дерево
        if (!children.empty()) {
            adj[node] = { children[0] };
            for (size_t i = 1; i < children.size(); ++i) {
                adj[children[i - 1]].push_back(children[i]);
            }
        }
    }
}


// Приведение произвольного графа к обычному дереву
void Graph::convertToTree() {
    parent.clear(); // Очистка карты родительских узлов

    // Начинаем обход с первого узла (или любого другого узла)
    std::string startNode = nodes.begin()->first;
    bfs(startNode);
}

std::string Graph::bfs(const std::string& start, std::map<std::string, int>& distances) const {
    std::map<std::string, int> distance;
    for (const auto& node : nodes) {
        distance[node.first] = -1;
    }
    std::queue<std::string> q;
    q.push(start);
    distance[start] = 0;

    std::string farthestNode = start;
    while (!q.empty()) {
        std::string node = q.front();
        q.pop();

        for (const std::string& neighbor : adj.at(node)) {
            if (distance[neighbor] == -1) {
                distance[neighbor] = distance[node] + 1;
                q.push(neighbor);
                if (distance[neighbor] > distance[farthestNode]) {
                    farthestNode = neighbor;
                }
            }
        }
    }

    distances.clear();
    for (const auto& pair : distance) {
        distances[pair.first] = pair.second;
    }

    return farthestNode;
}

void Graph::bfs(const std::string& startNode) {
    std::queue<std::string> q;
    std::unordered_set<std::string> visited;

    q.push(startNode);
    visited.insert(startNode);

    while (!q.empty()) {
        std::string node = q.front();
        q.pop();

        for (const std::string& neighbor : adj[node]) {
            if (visited.find(neighbor) == visited.end()) {
                visited.insert(neighbor);
                parent[neighbor] = node; // Устанавливаем родительский узел
                q.push(neighbor);
            }
        }
    }
}


// Нахождение гамильтоновых циклов
bool Graph::isSafe(const std::string& v, const std::vector<std::string>& path, int pos) const {
    if (pos == 0 || pos >= path.size()) return false; // Проверка границ
    const std::string& lastVertex = path[pos - 1];
    const auto& neighbors = adj.at(lastVertex);
    if (std::find(neighbors.begin(), neighbors.end(), v) == neighbors.end())
        return false;

    if (std::find(path.begin(), path.end(), v) != path.end())
        return false;

    return true;
}

void Graph::hamiltonianCycleUtil(std::vector<std::string>& path, int pos) const {
    if (pos == path.size()) {
        const std::string& lastVertex = path[pos - 1];
        const auto& neighbors = adj.at(lastVertex);
        if (std::find(neighbors.begin(), neighbors.end(), path[0]) != neighbors.end()) {
            for (const auto& vertex : path)
                std::cout << vertex << " ";
            std::cout << path[0] << std::endl;
        }
        return;
    }

    for (const auto& nodePair : nodes) {
        const std::string& v = nodePair.first;
        if (isSafe(v, path, pos)) {
            path[pos] = v;
            hamiltonianCycleUtil(path, pos + 1);
            path[pos] = "";
        }
    }
}

void Graph::findHamiltonianCycles() const {
    if (adj.empty()) return; // Проверка на пустой граф
    std::vector<std::string> path(nodes.size(), "");
    path[0] = nodes.begin()->first;
    hamiltonianCycleUtil(path, 1);
}


// Вычисление диаметра графа
int Graph::calculateDiameter() const {
    std::map<std::string, int> distances;
    std::string startNode = nodes.begin()->first;
    std::string farthestNode = bfs(startNode, distances);
    std::string diameterNode = bfs(farthestNode, distances);

    // Находим максимальное расстояние в distances
    int diameter = 0;
    for (const auto& pair : distances) {
        if (pair.second > diameter) {
            diameter = pair.second;
        }
    }

    return diameter;
}


// Вычисление радиуса графа
int Graph::calculateRadius() const {
    int radius = std::numeric_limits<int>::max();

    for (const auto& node : nodes) {
        std::map<std::string, int> distances;
        bfs(node.first, distances);

        int maxDistance = 0;
        for (const auto& pair : distances) {
            if (pair.second > maxDistance) {
                maxDistance = pair.second;
            }
        }

        if (maxDistance < radius) {
            radius = maxDistance;
        }
    }

    return radius;
}


// Вычисление центра графа
std::string Graph::findGraphCenter() const {
    std::map<std::string, int> distances;
    std::string startNode = nodes.begin()->first;
    std::string farthestNode = bfs(startNode, distances);
    bfs(farthestNode, distances);

    int minEccentricity = std::numeric_limits<int>::max();
    std::string centerNode;
    for (const auto& pair : distances) {
        if (pair.second < minEccentricity) {
            minEccentricity = pair.second;
            centerNode = pair.first;
        }
    }
    return "Центр графа: " + centerNode;
}


// Вычисление тензорного произведения двух графов
Graph Graph::tensorProduct(const Graph& other) const {
    Graph result = Graph("tensor_product");

    for (const auto& node1 : nodes) {
        for (const auto& node2 : other.nodes) {
            std::string newNodeName = node1.first + "_" + node2.first;
            std::string newNodeColor = node1.second.color + "_" + node2.second.color;
            result.addNode(newNodeName, newNodeColor);
        }
    }

    for (const auto& edge1 : edges) {
        for (const auto& edge2 : other.edges) {
            std::string from = edge1.from + "_" + edge2.from;
            std::string to = edge1.to + "_" + edge2.to;
            bool directed = edge1.directed || edge2.directed;
            std::string color = edge1.color + "_" + edge2.color;
            result.addEdge(from, to, directed, color);
        }
    }

    return result;
}

// Вычисление декартова произведения двух графов
Graph Graph::cartesianProduct(const Graph& other) const {
    Graph result = Graph("cartesian_product");

    for (const auto& node1 : nodes) {
        for (const auto& node2 : other.nodes) {
            std::string newNodeName = node1.first + "_" + node2.first;
            std::string newNodeColor = node1.second.color + "_" + node2.second.color;
            result.addNode(newNodeName, newNodeColor);
        }
    }

    for (const auto& edge1 : edges) {
        for (const auto& node2 : other.nodes) {
            std::string from = edge1.from + "_" + node2.first;
            std::string to = edge1.to + "_" + node2.first;
            result.addEdge(from, to, edge1.directed, edge1.color + "_" + node2.second.color);
        }
    }

    for (const auto& edge2 : other.edges) {
        for (const auto& node1 : nodes) {
            std::string from = node1.first + "_" + edge2.from;
            std::string to = node1.first + "_" + edge2.to;
            result.addEdge(from, to, edge2.directed, node1.second.color + "_" + edge2.color);
        }
    }

    return result;
}


//Объединение графов
Graph Graph::unionGraph(const Graph& other) const {
    Graph result = Graph("union_graph");

    // Копируем узлы и дуги из текущего графа
    for (const auto& node : nodes) {
        result.addNode(node.first, node.second.color);
    }
    for (const auto& edge : edges) {
        result.addEdge(edge.from, edge.to, edge.directed, edge.color);
    }

    // Копируем узлы и дуги из другого графа
    for (const auto& node : other.nodes) {
        if (result.nodes.find(node.first) == result.nodes.end()) {
            result.addNode(node.first, node.second.color);
        }
    }
    for (const auto& edge : other.edges) {
        if (std::find(result.edges.begin(), result.edges.end(), edge) == result.edges.end()) {
            result.addEdge(edge.from, edge.to, edge.directed, edge.color);
        }
    }

    return result;
}

//Пересечение графов
Graph Graph::intersectionGraph(const Graph& other) const {
    Graph result = Graph("intersection_graph");

    // Добавляем узлы, которые есть в обоих графах
    for (const auto& node : nodes) {
        if (other.nodes.find(node.first) != other.nodes.end()) {
            result.addNode(node.first, node.second.color);
        }
    }

    // Добавляем дуги, которые есть в обоих графах
    for (const auto& edge : edges) {
        if (std::find(other.edges.begin(), other.edges.end(), edge) != other.edges.end()) {
            result.addEdge(edge.from, edge.to, edge.directed, edge.color);
        }
    }

    return result;
}

//Сочетание графов
Graph Graph::combinationGraph(const Graph& other) const {
    Graph result = Graph("combination_graph");

    // Копируем узлы и дуги из текущего графа
    for (const auto& node : nodes) {
        result.addNode(node.first, node.second.color);
    }
    for (const auto& edge : edges) {
        result.addEdge(edge.from, edge.to, edge.directed, edge.color);
    }

    // Копируем узлы и дуги из другого графа
    for (const auto& node : other.nodes) {
        if (result.nodes.find(node.first) == result.nodes.end()) {
            result.addNode(node.first, node.second.color);
        }
    }
    for (const auto& edge : other.edges) {
        result.addEdge(edge.from, edge.to, edge.directed, edge.color);
    }

    return result;
}

//Дополнение графа
Graph Graph::complementGraph() const {
    Graph result = Graph("complement_graph");

    // Копируем узлы из текущего графа
    for (const auto& node : nodes) {
        result.addNode(node.first, node.second.color);
    }

    // Добавляем дуги, которых нет в текущем графе
    for (const auto& node1 : nodes) {
        for (const auto& node2 : nodes) {
            if (node1.first != node2.first) {
                Edge edge = { node1.first, node2.first, false, "black" };
                auto it = std::find_if(edges.begin(), edges.end(), [&edge](const Edge& e) {
                    return (e.from == edge.from && e.to == edge.to) ||
                        (e.from == edge.to && e.to == edge.from);
                    });
                if (it == edges.end()) {
                    result.addEdge(node1.first, node2.first, false, "black");
                }
            }
        }
    }

    return result;
}



std::string Graph::getName() const {
    return name;
};