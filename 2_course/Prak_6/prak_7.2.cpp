#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Структура для представления ребра графа
struct Edge {
    int u, v, weight; // u и v — вершины, weight — вес ребра
    // Перегружаем оператор < для сортировки ребер по весу
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Структура для представления графа
struct Graph {
    int vertices, edges;            // Количество вершин и ребер
    vector<Edge> edgeList;          // Список ребер
};

// Класс Union-Find (Объединение и поиск)
// Используется для отслеживания соединений вершин и проверки на наличие циклов
class UnionFind {
    vector<int> parent, rank; // parent — родитель вершины, rank — глубина дерева
public:
    // Конструктор для инициализации структур данных
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0); // Изначально глубина дерева равна 0
        for (int i = 0; i < n; ++i) {
            parent[i] = i; // Каждая вершина сначала является своим родителем
        }
    }

    // Функция "поиск" с реализацией сжатия пути
    int find(int u) {
        if (u != parent[u]) {
            parent[u] = find(parent[u]); // Сжимаем путь к корню для оптимизации
        }
        return parent[u];
    }

    // Функция "объединение" двух множеств по рангам
    void unite(int u, int v) {
        int rootU = find(u); // Найти корень множества u
        int rootV = find(v); // Найти корень множества v
        if (rootU != rootV) { // Объединяем только если они принадлежат разным множествам
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU; // rootU становится родителем
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV; // rootV становится родителем
            } else {
                parent[rootV] = rootU; // При равных рангах rootU становится родителем
                rank[rootU]++; // Увеличиваем ранг rootU
            }
        }
    }
};

// Основная функция для выполнения алгоритма Крускала
void kruskalMST(Graph& graph) {
    // Сортируем ребра по возрастанию веса
    sort(graph.edgeList.begin(), graph.edgeList.end());

    UnionFind uf(graph.vertices); // Инициализация Union-Find для вершин графа
    vector<Edge> mst;            // Список ребер минимального остовного дерева
    int totalWeight = 0;         // Общий вес дерева

    // Проходим по отсортированным ребрам
    for (const Edge& edge : graph.edgeList) {
        // Если вершины ребра находятся в разных множествах (нет цикла)
        if (uf.find(edge.u) != uf.find(edge.v)) {
            uf.unite(edge.u, edge.v); // Объединяем множества
            mst.push_back(edge);      // Добавляем ребро в дерево
            totalWeight += edge.weight; // Увеличиваем общий вес
        }
    }

    // Вывод минимального остовного дерева
    cout << "Минимальное остовное дерево:\n";
    for (const Edge& edge : mst) {
        cout << edge.u << " -- " << edge.v << " [вес: " << edge.weight << "]\n";
    }
    cout << "Общий вес: " << totalWeight << endl;
}

// Функция для добавления ребра в граф
void addEdge(Graph& graph, int u, int v, int weight) {
    graph.edgeList.push_back({u, v, weight});
}

// Функция для создания тестового графа из задания
Graph createTestGraph() {
    Graph graph;
    graph.vertices = 7;  // Задаем количество вершин
    graph.edges = 11;    // Задаем количество ребер
    // Добавляем ребра с весами
    addEdge(graph, 1, 2, 4);
    addEdge(graph, 1, 6, 23);
    addEdge(graph, 1, 7, 20);
    addEdge(graph, 2, 3, 15);
    addEdge(graph, 2, 7, 9);
    addEdge(graph, 3, 4, 3);
    addEdge(graph, 3, 7, 16);
    addEdge(graph, 4, 5, 17);
    addEdge(graph, 5, 6, 28);
    addEdge(graph, 5, 7, 25);
    addEdge(graph, 6, 7, 36);
    return graph;
}

// Пользовательское меню
void menu() {
    while (true) {
        // Выводим доступные действия
        cout << "\nВыберите действие:\n";
        cout << "1. Ввести собственный граф\n";
        cout << "2. Выполнить тестирование на предложенном графе\n";
        cout << "3. Выйти из программы\n";
        cout << "Ваш выбор: ";
        int choice;
        cin >> choice;

        if (choice == 1) { // Ввод собственного графа
            Graph graph;
            cout << "Введите количество вершин: ";
            cin >> graph.vertices;
            cout << "Введите количество ребер: ";
            cin >> graph.edges;

            // Запрашиваем ребра у пользователя
            cout << "Введите ребра в формате (u v вес):\n";
            for (int i = 0; i < graph.edges; ++i) {
                int u, v, weight;
                cin >> u >> v >> weight;
                addEdge(graph, u, v, weight);
            }

            // Выполнение алгоритма Крускала
            cout << "\nВыполняется алгоритм Крускала...\n";
            kruskalMST(graph);

        } else if (choice == 2) { // Тестирование на предложенном графе
            cout << "\nВыполняется тестирование на предложенном графе...\n";
            Graph testGraph = createTestGraph(); // Создаем тестовый граф
            kruskalMST(testGraph);              // Применяем алгоритм Крускала

        } else if (choice == 3) { // Выход из программы
            cout << "Выход из программы. До свидания!\n";
            break;

        } else { // Обработка некорректного ввода
            cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }
}


int main() {
    cout << ("\e[1;1H\e[2J");
    cout << "Программа для построения минимального остовного дерева (алгоритм Крускала)\n";
    menu(); 
    return 0;
}
