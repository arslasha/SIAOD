#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <fstream>
#include <iomanip>
#include <cmath>

using namespace std;

// Структура для узла дерева Хаффмана
struct HuffmanNode {
    char symbol;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;
    
    HuffmanNode(char symbol, int freq) : symbol(symbol), freq(freq), left(nullptr), right(nullptr) {}
};

// Компаратор для очереди с приоритетами (Хаффман)
struct Compare {
    bool operator()(HuffmanNode* l, HuffmanNode* r) {
        return l->freq > r->freq;
    }
};

// Функция для построения дерева Хаффмана
HuffmanNode* buildHuffmanTree(const map<char, int>& frequencies) {
    priority_queue<HuffmanNode*, vector<HuffmanNode*>, Compare> pq;
    
    for (const auto& pair : frequencies) {
        pq.push(new HuffmanNode(pair.first, pair.second));
    }
    
    while (pq.size() > 1) {
        HuffmanNode* left = pq.top(); pq.pop();
        HuffmanNode* right = pq.top(); pq.pop();
        HuffmanNode* combined = new HuffmanNode('\0', left->freq + right->freq);
        combined->left = left;
        combined->right = right;
        pq.push(combined);
    }
    
    return pq.top();
}

// Рекурсивная функция для генерации кодов Хаффмана
void generateHuffmanCodes(HuffmanNode* root, const string& code, map<char, string>& huffmanCodes) {
    if (!root) return;
    if (!root->left && !root->right) {
        huffmanCodes[root->symbol] = code;
    }
    generateHuffmanCodes(root->left, code + "0", huffmanCodes);
    generateHuffmanCodes(root->right, code + "1", huffmanCodes);
}

// Алгоритм Шеннона-Фано
void shannonFanoRecursive(vector<pair<char, int>>& frequencies, int left, int right, map<char, string>& codes, const string& currentCode) {
    if (left == right) {
        codes[frequencies[left].first] = currentCode;
        return;
    }

    int totalSum = 0;
    for (int i = left; i <= right; i++) {
        totalSum += frequencies[i].second;
    }
    
    int sum = 0, split = left;
    while (split < right && (sum + frequencies[split].second) * 2 <= totalSum) {
        sum += frequencies[split].second;
        split++;
    }
    
    shannonFanoRecursive(frequencies, left, split, codes, currentCode + "0");
    shannonFanoRecursive(frequencies, split + 1, right, codes, currentCode + "1");
}

// Построение кодов Шеннона-Фано
map<char, string> shannonFano(const map<char, int>& frequencies) {
    vector<pair<char, int>> freqVector(frequencies.begin(), frequencies.end());
    sort(freqVector.begin(), freqVector.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });
    map<char, string> codes;
    shannonFanoRecursive(freqVector, 0, freqVector.size() - 1, codes, "");
    return codes;
}

// Сжатие текста
string compressText(const string& text, const map<char, string>& codes) {
    string compressed = "";
    for (char c : text) {
        compressed += codes.at(c);
    }
    return compressed;
}

// Восстановление текста (для Хаффмана)
string decompressHuffman(const string& compressed, HuffmanNode* root) {
    string decompressed = "";
    HuffmanNode* current = root;
    for (char bit : compressed) {
        if (bit == '0') {
            current = current->left;
        } else {
            current = current->right;
        }
        if (!current->left && !current->right) {
            decompressed += current->symbol;
            current = root;
        }
    }
    return decompressed;
}

// Восстановление текста (для Шеннона-Фано)
string decompressShannonFano(const string& compressed, const map<string, char>& reverseCodes) {
    string decompressed = "";
    string buffer = "";
    for (char bit : compressed) {
        buffer += bit;
        if (reverseCodes.count(buffer)) {
            decompressed += reverseCodes.at(buffer);
            buffer = "";
        }
    }
    return decompressed;
}

// Подсчет коэффициента сжатия
double calculateCompressionRatio(const string& original, const string& compressed) {
    return ((double)compressed.length() / (original.length() * 8)) * 100;
}

void menu() {
    string text;
    cout << "Введите строку для сжатия: ";
    getline(cin, text);

    // Проверка пустого текста
    if (text.empty()) {
        cout << "Ошибка: введён пустой текст.\n";
        return;
    }

    // Подсчет частот символов
    map<char, int> frequencies;
    for (char c : text) {
        frequencies[c]++;
    }

    // Проверка, что есть символы для обработки
    if (frequencies.empty()) {
        cout << "Ошибка: текст не содержит символов для сжатия." << endl;
        return;
    }

    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Сжать текст методом Хаффмана\n";
        cout << "2. Декодировать текст методом Хаффмана\n";
        cout << "3. Сжать текст методом Шеннона-Фано\n";
        cout << "4. Декодировать текст методом Шеннона-Фано\n";
        cout << "5. Выйти\n";
        cout << "Выберите действие: ";
        int choice;
        cin >> choice;
        cin.ignore(); // Очистка буфера ввода

        if (choice == 1) {
            // Метод Хаффмана
            HuffmanNode* huffmanRoot = buildHuffmanTree(frequencies);

            if (!huffmanRoot) {
                cout << "Ошибка: дерево Хаффмана не удалось построить." << endl;
                continue;
            }

            map<char, string> huffmanCodes;
            generateHuffmanCodes(huffmanRoot, "", huffmanCodes);

            cout << "Коды Хаффмана:\n";
