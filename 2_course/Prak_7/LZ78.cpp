#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

// Структура для хранения выходного кода (index, nextSymbol)
struct LZ78Pair {
    int index;
    char nextSymbol;
};

// Функция для сжатия методом LZ78
vector<LZ78Pair> compressLZ78(const string &input) {
    unordered_map<string, int> dictionary;
    vector<LZ78Pair> compressed;

    string current = "";
    int dictIndex = 1; // Индекс для словаря

    for (char ch : input) {
        current += ch;
        if (dictionary.find(current) == dictionary.end()) {
            // Если текущая строка не найдена в словаре, добавляем пару
            int prefixIndex = (current.size() == 1) ? 0 : dictionary[current.substr(0, current.size() - 1)];
            compressed.push_back({prefixIndex, ch});
            dictionary[current] = dictIndex++;
            current = "";
        }
    }

    // Если остался непустой остаток, добавляем его
    if (!current.empty()) {
        int prefixIndex = dictionary[current.substr(0, current.size() - 1)];
        compressed.push_back({prefixIndex, current.back()});
    }

    return compressed;
}

// Функция для декодирования методом LZ78
string decompressLZ78(const vector<LZ78Pair> &compressed) {
    vector<string> dictionary = {""}; // Начальный словарь с пустой строкой
    string decompressed = "";

    for (const auto &pair : compressed) {
        string entry = dictionary[pair.index] + pair.nextSymbol;
        decompressed += entry;
        dictionary.push_back(entry);
    }

    return decompressed;
}

int main() {
    // Входные данные
    string input = "какатанекатанекатата";

    // Сжатие
    vector<LZ78Pair> compressed = compressLZ78(input);

    // Вывод сжатых данных
    cout << "Compressed Data (LZ78):" << endl;
    for (const auto &pair : compressed) {
        cout << "(" << pair.index << ", " << pair.nextSymbol << ")" << endl;
    }

    // Декодирование
    string decompressed = decompressLZ78(compressed);

    // Вывод результата декодирования
    cout << "Decompressed Data: " << decompressed << endl;

    return 0;
}
