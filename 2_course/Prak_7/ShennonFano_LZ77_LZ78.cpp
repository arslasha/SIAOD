#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <string>

using namespace std;

// Узел для представления символов и их кодов (для Шеннона-Фано)
struct Node {
    char symbol;
    double probability;
    string code;
    Node* left;
    Node* right;

    Node(char s, double p) : symbol(s), probability(p), left(nullptr), right(nullptr), code("") {}
};

// Функция сравнения для сортировки узлов по вероятности
bool compareNodes(const Node& a, const Node& b) {
    return a.probability > b.probability;
}

// Рекурсивная функция для генерации кодов методом Шеннона-Фано
void generateShannonFanoCodes(vector<Node>& nodes, int start, int end, string code) {
    if (start == end) {
        nodes[start].code = code;
        return;
    }

    // Найти точку разделения
    double total = 0;
    for (int i = start; i <= end; i++) {
        total += nodes[i].probability;
    }

    double half = 0;
    int splitIndex = start;
    for (int i = start; i <= end; i++) {
        half += nodes[i].probability;
        if (half >= total / 2) {
            splitIndex = i;
            break;
        }
    }

    // Присвоить коды
    for (int i = start; i <= splitIndex; i++) {
        nodes[i].code = code + "0";
    }
    for (int i = splitIndex + 1; i <= end; i++) {
        nodes[i].code = code + "1";
    }

    // Рекурсивно обработать две группы
    generateShannonFanoCodes(nodes, start, splitIndex, code + "0");
    generateShannonFanoCodes(nodes, splitIndex + 1, end, code + "1");
}

// Функция кодирования методом Шеннона-Фано
void shannonFanoEncoding(const string& text) {
    // Подсчёт частоты символов
    map<char, int> frequency;
    for (char ch : text) {
        frequency[ch]++;
    }

    // Создать узлы для каждого символа
    vector<Node> nodes;
    int total = text.length();
    for (auto& entry : frequency) {
        nodes.emplace_back(entry.first, static_cast<double>(entry.second) / total);
    }

    // Отсортировать узлы по вероятности
    sort(nodes.begin(), nodes.end(), compareNodes);

    // Генерация кодов
    generateShannonFanoCodes(nodes, 0, nodes.size() - 1, "");

    // Вывод кодов
    cout << "Коды символов (метод Шеннона-Фано):\n";
    for (const auto& node : nodes) {
        cout << node.symbol << ": " << node.code << "\n";
    }

    // Кодирование текста
    string encodedText = "";
    for (char ch : text) {
        for (const auto& node : nodes) {
            if (node.symbol == ch) {
                encodedText += node.code;
                break;
            }
        }
    }

    cout << "Закодированный текст: " << encodedText << "\n";
}

// Функция для сжатия методом LZ77
void lz77Compression(const string& input) {
    cout << "Сжатие по методу LZ77:\n";

    string result;
    int len = input.length();
    int buffer_size = 5; // Размер окна поиска

    for (int i = 0; i < len;) {
        int max_match_length = 0, match_position = 0;
        
        for (int j = max(0, i - buffer_size); j < i; ++j) {
            int k = 0;
            while (j + k < i && input[j + k] == input[i + k] && (i + k) < len) {
                k++;
            }
            if (k > max_match_length) {
                max_match_length = k;
                match_position = i - j;
            }
        }

        if (max_match_length > 0) {
            result += "(" + to_string(match_position) + "," + to_string(max_match_length) + "," + input[i + max_match_length] + ")";
            i += max_match_length + 1;
        } else {
            result += "(0,0," + string(1, input[i]) + ")";
            i++;
        }
    }

    cout << "Сжатый результат: " << result << "\n";
}

// Функция для кодирования методом LZ78
void lz78Encoding(const string& input) {
    cout << "Кодирование по методу LZ78:\n";

    map<string, int> dictionary;
    string current = "";
    int code = 1;

    vector<pair<int, char>> encoded;

    for (char ch : input) {
        current += ch;
        if (dictionary.find(current) == dictionary.end()) {
            dictionary[current] = code++;
            encoded.push_back({dictionary[current.substr(0, current.size() - 1)], ch});
            current = "";
        }
    }

    if (!current.empty()) {
        encoded.push_back({dictionary[current], ' '});
    }

    cout << "Закодированная последовательность:\n";
    for (const auto& pair : encoded) {
        cout << "(" << pair.first << "," << pair.second << ") ";
    }
    cout << "\n";
}

// Главное меню программы
int main() {
    setlocale(LC_ALL, "Russian");
    string phrase = "Прибавь к ослиной голове Ещё одну, получишь две. Но сколько б ни было ослов, Они и двух не свяжут слов.";
    int choice;

    do {
        cout << "\nМеню:\n";
        cout << "1. Кодирование методом Шеннона-Фано\n";
        cout << "2. Сжатие методом LZ77\n";
        cout << "3. Кодирование методом LZ78\n";
        cout << "4. Выход\n";
        cout << "Выберите действие: ";
        cin >> choice;

        switch (choice) {
            case 1:
                shannonFanoEncoding(phrase);
                break;
            case 2:
                lz77Compression("1010001001010101000101");
                break;
            case 3:
                lz78Encoding("какатанекатанекатата");
                break;
            case 4:
                cout << "Выход из программы.\n";
                break;
            default:
                cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 4);

    return 0;
}
