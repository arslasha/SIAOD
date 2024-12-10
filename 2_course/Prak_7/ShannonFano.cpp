#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <string>
using namespace std;

// Структура для символов и их вероятностей
struct Symbol {
    char ch;
    double freq;
    string code;
};

// Сравнение для сортировки по частоте
bool compareByFrequency(const Symbol &a, const Symbol &b) {
    return a.freq > b.freq;
}

// Рекурсивная функция для построения кодов
void buildShannonFanoCodes(vector<Symbol> &symbols, int start, int end) {
    if (start >= end) return;
    if (end - start == 1) {
        symbols[start].code += "0";
        symbols[end].code += "1";
        return;
    }

    double totalFreq = 0;
    for (int i = start; i <= end; i++) {
        totalFreq += symbols[i].freq;
    }

    double halfFreq = totalFreq / 2.0;
    double currentFreq = 0;
    int splitIndex = start;

    while (splitIndex <= end && currentFreq + symbols[splitIndex].freq <= halfFreq) {
        currentFreq += symbols[splitIndex].freq;
        splitIndex++;
    }

    for (int i = start; i < splitIndex; i++) {
        symbols[i].code += "0";
    }
    for (int i = splitIndex; i <= end; i++) {
        symbols[i].code += "1";
    }

    buildShannonFanoCodes(symbols, start, splitIndex - 1);
    buildShannonFanoCodes(symbols, splitIndex, end);
}

// Функция для сжатия текста
string compressShannonFano(const string &text, unordered_map<char, string> &codeMap) {
    string compressed = "";
    for (char ch : text) {
        compressed += codeMap[ch];
    }
    return compressed;
}

// Функция для декодирования текста
string decompressShannonFano(const string &compressed, unordered_map<string, char> &reverseCodeMap) {
    string decompressed = "";
    string buffer = "";
    for (char bit : compressed) {
        buffer += bit;
        if (reverseCodeMap.find(buffer) != reverseCodeMap.end()) {
            decompressed += reverseCodeMap[buffer];
            buffer = "";
        }
    }
    return decompressed;
}

int main() {
    string text = "Прибавь к ослиной голове Еще одну, получишь две. Но сколько б ни было ослов, Они и двух не свяжут слов.";

    // Подсчет частот символов
    unordered_map<char, double> frequencyMap;
    for (char ch : text) {
        frequencyMap[ch]++;
    }

    vector<Symbol> symbols;
    for (auto &pair : frequencyMap) {
        symbols.push_back({pair.first, pair.second / text.size(), ""});
    }

    // Сортировка символов по частоте
    sort(symbols.begin(), symbols.end(), compareByFrequency);

    // Построение кодов Шеннона-Фано
    buildShannonFanoCodes(symbols, 0, symbols.size() - 1);

    // Создание карты кодов
    unordered_map<char, string> codeMap;
    unordered_map<string, char> reverseCodeMap;
    for (const auto &symbol : symbols) {
        codeMap[symbol.ch] = symbol.code;
        reverseCodeMap[symbol.code] = symbol.ch;
    }

    // Сжатие текста
    string compressed = compressShannonFano(text, codeMap);
    cout << "Compressed: " << compressed << endl;

    // Восстановление текста
    string decompressed = decompressShannonFano(compressed, reverseCodeMap);
    cout << "Decompressed: " << decompressed << endl;

    return 0;
}
