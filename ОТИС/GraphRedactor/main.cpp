#include "Graph.h"
#include <vector>
#include <map>
#include <windows.h>

void printMenu() {
    std::cout << "Меню:\n";
    std::cout << "1. Создать новый граф\n";
    std::cout << "2. Удалить граф\n";
    std::cout << "3. Выбрать граф\n";
    std::cout << "4. Добавить узел\n";
    std::cout << "5. Удалить узел\n";
    std::cout << "6. Добавить дугу\n";
    std::cout << "7. Удалить дугу\n";
    std::cout << "8. Переименовать узел\n";
    std::cout << "9. Изменить цвет узла\n";
    std::cout << "10. Изменить цвет дуги\n";
    std::cout << "11. Вывести граф\n";
    std::cout << "12. Информация о графе\n";
    std::cout << "13. Вывести матрицу инцидентности\n";
    std::cout << "14. Проверить, является ли граф эйлеровым\n";
    std::cout << "15. Привести граф к бинарному дереву\n";
    std::cout << "16. Привести граф к обычному дереву\n";
    std::cout << "17. Найти гамильтоновы циклы\n";
    std::cout << "18. Вычислить диаметр графа\n";
    std::cout << "19. Вычислить радиус графа\n";
    std::cout << "20. Найти центр графа\n";
    std::cout << "21. Вычислить тензорное произведение двух графов\n";
    std::cout << "22. Вычислить декартово произведение двух графов\n";
    std::cout << "23. Объединение двух графов\n";
    std::cout << "24. Пересечение двух графов\n";
    std::cout << "25. Сочетание двух графов\n";
    std::cout << "26. Дополнение графа\n";
    std::cout << "0. Выход\n";
}

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);
    std::map<std::string, Graph> graphs;
    std::string currentGraphName;
    int choice;
    bool choice_graph = false;

    do {
        if (choice_graph == true) {
            std::cout << std::endl << "Выбранный граф: " << currentGraphName << std::endl << std::endl;
        }
        printMenu();
        std::cout << std::endl << std::endl;
        std::cin >> choice;
        std::cout << std::endl << std::endl;

        switch (choice) {
        case 1: {
            std::string name;
            std::cout << "Введите имя нового графа: ";
            std::cin >> name;
            graphs[name] = Graph(name);
            currentGraphName = name;
            choice_graph = true;
            break;
        }
        case 2: {
            std::string name;
            std::cout << "Введите имя графа для удаления: ";
            std::cin >> name;
            if (graphs.find(name) != graphs.end()) {
                graphs.erase(name);
                if (currentGraphName == name) {
                    currentGraphName.clear();
                }
            }
            else {
                std::cout << "Граф не найден!" << std::endl << std::endl;
            }
            break;
        }
        case 3: {
            std::cout << "Список всех графов:\n";
            for (const auto& graphPair : graphs) {
                std::cout << graphPair.first << std::endl;
            }
            std::string name;
            std::cout << "Введите имя графа для выбора: ";
            std::cin >> name;
            if (graphs.find(name) != graphs.end()) {
                currentGraphName = name;
                choice_graph = true;
            }
            else {
                std::cout << "Граф не найден!" << std::endl << std::endl;
            }
            break;
        }
        case 4: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string name, color;
            std::cout << "Введите имя узла и цвет: ";
            std::cin >> name >> color;
            graphs[currentGraphName].addNode(name, color);
            break;
        }
        case 5: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string name;
            std::cout << "Введите имя узла: ";
            std::cin >> name;
            graphs[currentGraphName].removeNode(name);
            break;
        }
        case 6: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string from, to, color;
            bool directed;
            std::cout << "Введите начальный узел, конечный узел, цвет и тип (1 - ориентированная, 0 - неориентированная): ";
            std::cin >> from >> to >> color >> directed;
            graphs[currentGraphName].addEdge(from, to, directed, color);
            break;
        }
        case 7: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string from, to;
            std::cout << "Введите начальный и конечный узлы: ";
            std::cin >> from >> to;
            graphs[currentGraphName].removeEdge(from, to);
            break;
        }
        case 8: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string oldName, newName;
            std::cout << "Введите старое и новое имя узла: ";
            std::cin >> oldName >> newName;
            graphs[currentGraphName].renameNode(oldName, newName);
            break;
        }
        case 9: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string name, color;
            std::cout << "Введите имя узла и новый цвет: ";
            std::cin >> name >> color;
            graphs[currentGraphName].setNodeColor(name, color);
            break;
        }
        case 10: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string from, to, color;
            std::cout << "Введите начальный узел, конечный узел и новый цвет дуги: ";
            std::cin >> from >> to >> color;
            graphs[currentGraphName].setEdgeColor(from, to, color);
            break;
        }
        case 11: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            graphs[currentGraphName].printAdjacencyMatrix();
            break;
        }
        case 12: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            graphs[currentGraphName].printGraphInfo();
            break;
        }
        case 13: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            graphs[currentGraphName].printIncidenceMatrix();
            break;
        }
        case 14: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            bool isEulerian = graphs[currentGraphName].isEulerian();
            std::cout << "Граф " << (isEulerian ? "является" : "не является") << " эйлеровым." << std::endl;
            break;
        }
        case 15: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            graphs[currentGraphName].convertToBinaryTree();
            std::cout << "Граф преобразован в бинарное дерево." << std::endl;
            break;
        }
        case 16: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            graphs[currentGraphName].convertToTree();
            std::cout << "Граф преобразован в обычное дерево." << std::endl;
            break;
        }
        case 17: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            graphs[currentGraphName].findHamiltonianCycles();
            break;
        }
        case 18: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            int diameter = graphs[currentGraphName].calculateDiameter();
            std::cout << "Диаметр графа: " << diameter << std::endl;
            break;
        }
        case 19: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            int radius = graphs[currentGraphName].calculateRadius();
            std::cout << "Радиус графа: " << radius << std::endl;
            break;
        }
        case 20: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string center = graphs[currentGraphName].findGraphCenter();
            std::cout << center << std::endl;
            break;
        }
        case 21: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string otherGraphName;
            std::cout << "Введите имя второго графа: ";
            std::cin >> otherGraphName;
            if (graphs.find(otherGraphName) != graphs.end()) {
                Graph tensorProductGraph = graphs[currentGraphName].tensorProduct(graphs[otherGraphName]);
                std::cout << "Тензорное произведение графов выполнено." << std::endl;
                tensorProductGraph.printAdjacencyMatrix();
            }
            else {
                std::cout << "Второй граф не найден!" << std::endl;
            }
            break;
        }
        case 22: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string otherGraphName;
            std::cout << "Введите имя второго графа: ";
            std::cin >> otherGraphName;
            if (graphs.find(otherGraphName) != graphs.end()) {
                Graph cartesianProductGraph = graphs[currentGraphName].cartesianProduct(graphs[otherGraphName]);
                std::cout << "Декартово произведение графов выполнено." << std::endl;
                cartesianProductGraph.printAdjacencyMatrix();
            }
            else {
                std::cout << "Второй граф не найден!" << std::endl;
            }
            break;
        }
        case 23: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string otherGraphName;
            std::cout << "Введите имя второго графа: ";
            std::cin >> otherGraphName;
            if (graphs.find(otherGraphName) != graphs.end()) {
                Graph unionGraph = graphs[currentGraphName].unionGraph(graphs[otherGraphName]);
                std::cout << "Объединение графов выполнено." << std::endl;
                unionGraph.printAdjacencyMatrix();
            }
            else {
                std::cout << "Второй граф не найден!" << std::endl;
            }
            break;
        }
        case 24: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string otherGraphName;
            std::cout << "Введите имя второго графа: ";
            std::cin >> otherGraphName;
            if (graphs.find(otherGraphName) != graphs.end()) {
                Graph intersectionGraph = graphs[currentGraphName].intersectionGraph(graphs[otherGraphName]);
                std::cout << "Пересечение графов выполнено." << std::endl;
                intersectionGraph.printAdjacencyMatrix();
            }
            else {
                std::cout << "Второй граф не найден!" << std::endl;
            }
            break;
        }
        case 25: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            std::string otherGraphName;
            std::cout << "Введите имя второго графа: ";
            std::cin >> otherGraphName;
            if (graphs.find(otherGraphName) != graphs.end()) {
                Graph combinationGraph = graphs[currentGraphName].combinationGraph(graphs[otherGraphName]);
                std::cout << "Сочетание графов выполнено." << std::endl;
                combinationGraph.printAdjacencyMatrix();
            }
            else {
                std::cout << "Второй граф не найден!" << std::endl;
            }
            break;
        }
        case 26: {
            if (currentGraphName.empty()) {
                std::cout << "Сначала выберите граф!" << std::endl;
                break;
            }
            Graph complementGraph = graphs[currentGraphName].complementGraph();
            std::cout << "Дополнение графа найдено." << std::endl;
            complementGraph.printAdjacencyMatrix();
            break;
        }
        case 0:
            std::cout << "Выход из программы.\n";
            break;
        default:
            std::cout << "Неверный выбор!\n" << std::endl;
        }
    } while (choice != 0);

    return 0;
}

