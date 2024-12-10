#include <iostream>
#include <iomanip>
using namespace std;

// Структура узла дерева
struct Node {
    float data;
    Node* left;
    Node* right;
    
    Node(float value) : data(value), left(nullptr), right(nullptr) {}
};

// Класс бинарного дерева поиска
class BinarySearchTree {
private:
    Node* root;

    // Вспомогательная функция для вставки элемента
    Node* insert(Node* node, float value) {
        if (node == nullptr) return new Node(value);
        if (value < node->data)
            node->left = insert(node->left, value);
        else
            node->right = insert(node->right, value);
        return node;
    }

    // Вспомогательная функция для симметричного обхода
    void inorderTraversal(Node* node) {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << node->data << " ";
            inorderTraversal(node->right);
        }
    }

    // Вспомогательная функция для нахождения суммы и количества узлов
    void sumAndCountNodes(Node* node, float &sum, int &count) {
        if (node != nullptr) {
            sum += node->data;
            count++;
            sumAndCountNodes(node->left, sum, count);
            sumAndCountNodes(node->right, sum, count);
        }
    }

    // Вспомогательная функция для нахождения длины пути
    int findPathLength(Node* node, float value, int pathLength) {
        if (node == nullptr) return -1;
        if (node->data == value) return pathLength;
        
        int leftPath = findPathLength(node->left, value, pathLength + 1);
        if (leftPath != -1) return leftPath;
        
        return findPathLength(node->right, value, pathLength + 1);
    }

public:
    // Конструктор
    BinarySearchTree() : root(nullptr) {}

    // Метод для вставки элемента
    void insert(float value) {
        root = insert(root, value);
    }

    // Метод для симметричного обхода
    void inorderTraversal() {
        inorderTraversal(root);
        cout << endl;
    }

    // Метод для нахождения среднего арифметического всех узлов
    float findAverage() {
        float sum = 0;
        int count = 0;
        sumAndCountNodes(root, sum, count);
        return count ? sum / count : 0;
    }

    // Метод для нахождения длины пути от корня до заданного значения
    int findPathLength(float value) {
        return findPathLength(root, value, 0);
    }
};

// Функция для вывода меню
void menu() {
    BinarySearchTree tree;
    int choice;
    float value;
    
    do {
        cout << "\nМеню:\n";
        cout << "1. Вставить элемент\n";
        cout << "2. Симметричный обход\n";
        cout << "3. Найти среднее арифметическое всех узлов\n";
        cout << "4. Найти длину пути до заданного значения\n";
        cout << "0. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;
        
        switch (choice) {
            case 1:
                cout << "Введите значение: ";
                cin >> value;
                tree.insert(value);
                break;
                
            case 2:
                cout << "Симметричный обход: ";
                tree.inorderTraversal();
                break;
                
            case 3:
                cout << "Среднее арифметическое всех узлов: " << fixed << setprecision(2) << tree.findAverage() << endl;
                break;
                
            case 4:
                cout << "Введите значение для поиска пути: ";
                cin >> value;
                int pathLength;
                pathLength = tree.findPathLength(value);
                if (pathLength != -1)
                    cout << "Длина пути до узла " << value << ": " << pathLength << endl;
                else
                    cout << "Значение не найдено в дереве.\n";
                break;
                
            case 0:
                cout << "Выход из программы.\n";
                break;
                
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
        
    } while (choice != 0);
}

int main() {
    setlocale(0, ""); 
    cout << ("\e[1;1H\e[2J"); 
    menu();
    return 0;
}