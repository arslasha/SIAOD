#include <iostream>
#include <unordered_set>
#include <stack>

// Структура для представления узла списка
struct Node {
    int data;
    Node* next;

    // Конструктор для инициализации узла
    Node(int val) : data(val), next(nullptr) {}
};

// Класс для представления однонаправленного списка
class LinkedList {
private:
    Node* head; // Указатель на голову списка

public:
    // Конструктор для инициализации пустого списка
    LinkedList() : head(nullptr) {}

    // Метод для вставки узла в начало списка
    void insertAtStart(int data) {
        Node* newNode = new Node(data);
        newNode->next = head;
        head = newNode;
    }

    // Метод для создания списка из массива значений
    void createList(int n, int values[]) {
        for (int i = 0; i < n; ++i) {
            insertAtStart(values[i]);
        }
    }

    // Метод для вывода списка в консоль (слева направо)
    void printList() {
        Node* current = head;
        while (current) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "None" << std::endl;
    }

    // Метод для вывода списка в консоль (справа налево)
    void printListReverse() {
        std::stack<int> nodes;
        Node* current = head;
        while (current) {
            nodes.push(current->data);
            current = current->next;
        }
        while (!nodes.empty()) {
            std::cout << nodes.top() << " -> ";
            nodes.pop();
        }
        std::cout << "None" << std::endl;
    }

    // Метод для нахождения узла с заданным значением
    Node* findNode(int value) {
        Node* current = head;
        while (current) {
            if (current->data == value) {
                return current;
            }
            current = current->next;
        }
        return nullptr;
    }

    // Метод для нахождения общих элементов между двумя списками
    LinkedList findCommonElements(LinkedList& otherList) {
        LinkedList commonElements;
        std::unordered_set<int> elements;

        Node* current1 = head;
        while (current1) {
            elements.insert(current1->data);
            current1 = current1->next;
        }

        Node* current2 = otherList.head;
        while (current2) {
            if (elements.find(current2->data) != elements.end()) {
                commonElements.insertAtStart(current2->data);
            }
            current2 = current2->next;
        }

        return commonElements;
    }

    // Метод для вставки списка в другой список после узла с заданным значением
    void insertListAfterValue(LinkedList& otherList, int value) {
        Node* targetNode = findNode(value);
        if (!targetNode) {
            std::cout << "Узел с заданным значением не найден." << std::endl;
            return;
        }

        Node* temp = targetNode->next;
        targetNode->next = otherList.head;

        Node* last = otherList.head;
        while (last && last->next) {
            last = last->next;
        }
        if (last) {
            last->next = temp;
        }
    }

    // Метод для удаления всех узлов с четными значениями из списка
    void removeEvenValues() {
        Node* current = head;
        Node* prev = nullptr;

        while (current) {
            if (current->data % 2 == 0) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                Node* temp = current;
                current = current->next;
                delete temp;
            } else {
                prev = current;
                current = current->next;
            }
        }
    }

    // Деструктор для освобождения памяти списка
    ~LinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

void mainMenu() {
    LinkedList L1, L2;

    while (true) {
        std::cout << "\nМеню:\n";
        std::cout << "1. Создать список L1\n";
        std::cout << "2. Создать список L2\n";
        std::cout << "3. Показать список L1 (слева направо)\n";
        std::cout << "4. Показать список L2 (слева направо)\n";
        std::cout << "5. Показать список L1 (справа налево)\n";
        std::cout << "6. Показать список L2 (справа налево)\n";
        std::cout << "7. Найти узел в L1\n";
        std::cout << "8. Найти узел в L2\n";
        std::cout << "9. Создать новый список из значений, входящих в L1 и L2\n";
        std::cout << "10. Вставить L1 в L2 после узла с заданным значением\n";
        std::cout << "11. Удалить из списка L1 все узлы с четными значениями\n";
        std::cout << "12. Выйти\n";

        int choice;
        std::cout << "Выберите действие: ";
        std::cin >> choice;

        if (choice == 1) {
            int n;
            std::cout << "Введите количество элементов для L1: ";
            std::cin >> n;
            int* values = new int[n];
            std::cout << "Введите элементы для L1: ";
            for (int i = 0; i < n; ++i) {
                std::cin >> values[i];
            }
            L1.createList(n, values);
            delete[] values;
        } else if (choice == 2) {
            int n;
            std::cout << "Введите количество элементов для L2: ";
            std::cin >> n;
            int* values = new int[n];
            std::cout << "Введите элементы для L2: ";
            for (int i = 0; i < n; ++i) {
                std::cin >> values[i];
            }
            L2.createList(n, values);
            delete[] values;
        } else if (choice == 3) {
            std::cout << "Список L1 (слева направо):\n";
            L1.printList();
        } else if (choice == 4) {
            std::cout << "Список L2 (слева направо):\n";
            L2.printList();
        } else if (choice == 5) {
            std::cout << "Список L1 (справа налево):\n";
            L1.printListReverse();
        } else if (choice == 6) {
            std::cout << "Список L2 (справа налево):\n";
            L2.printListReverse();
        } else if (choice == 7) {
            int value;
            std::cout << "Введите значение узла для поиска в L1: ";
            std::cin >> value;
            Node* node = L1.findNode(value);
            if (node) {
                std::cout << "Узел найден: " << node->data << std::endl;
            } else {
                std::cout << "Узел не найден.\n";
            }
        } else if (choice == 8) {
            int value;
            std::cout << "Введите значение узла для поиска в L2: ";
            std::cin >> value;
            Node* node = L2.findNode(value);
            if (node) {
                std::cout << "Узел найден: " << node->data << std::endl;
            } else {
                std::cout << "Узел не найден.\n";
            }
        } else if (choice == 9) {
            LinkedList commonElements = L1.findCommonElements(L2);
            std::cout << "Новый список из значений, входящих в L1 и L2:\n";
            commonElements.printList();
        } else if (choice == 10) {
            int value;
            std::cout << "Введите значение узла, после которого вставить L1 в L2: ";
            std::cin >> value;
            L2.insertListAfterValue(L1, value);
            std::cout << "Модифицированный список L2:\n";
            L2.printList();
        } else if (choice == 11) {
            L1.removeEvenValues();
            std::cout << "Список L1 после удаления четных значений:\n";
            L1.printList();
        } else if (choice == 12) {
            break;
        } else {
            std::cout << "Неверный выбор. Пожалуйста, попробуйте снова.\n";
        }
    }
}

int main() {
    mainMenu();
    return 0;
}
