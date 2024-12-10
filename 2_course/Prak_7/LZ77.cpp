#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Структура для хранения выходного триплета (offset, length, next symbol)
struct LZ77Triple {
    int offset;
    int length;
    char nextSymbol;
};

// Функция для сжатия методом LZ77
vector<LZ77Triple> compressLZ77(const string &input, int windowSize) {
    vector<LZ77Triple> compressed;
    int inputSize = input.size();

    for (int i = 0; i < inputSize;) {
        int matchOffset = 0, matchLength = 0;
        char nextSymbol = input[i];

        // Окно поиска ограничивается заданным размером
        int searchBufferStart = max(0, i - windowSize);

        // Поиск наибольшего совпадения в окне поиска
        for (int j = searchBufferStart; j < i; ++j) {
            int k = 0;
            while (j + k < i && i + k < inputSize && input[j + k] == input[i + k]) {
                k++;
            }
            if (k > matchLength) {
                matchOffset = i - j;
                matchLength = k;
                nextSymbol = (i + k < inputSize) ? input[i + k] : '\0';
            }
        }

        // Добавляем триплет (offset, length, nextSymbol) в результат
        compressed.push_back({matchOffset, matchLength, nextSymbol});

        // Переход к следующей позиции
        i += matchLength + 1;
    }

    return compressed;
}

// Функция для декодирования методом LZ77
string decompressLZ77(const vector<LZ77Triple> &compressed) {
    string decompressed = "";

    for (const auto &triple : compressed) {
        int start = decompressed.size() - triple.offset;
        for (int i = 0; i < triple.length; ++i) {
            decompressed += decompressed[start + i];
        }
        if (triple.nextSymbol != '\0') {
            decompressed += triple.nextSymbol;
        }
    }

    return decompressed;
}

int main() {
    // Входные данные
    string input = "101000100101010001011";

    // Задаем размер окна поиска
    int windowSize = 10;

    // Сжатие
    vector<LZ77Triple> compressed = compressLZ77(input, windowSize);

    // Вывод сжатых данных
    cout << "Compressed Data (LZ77):" << endl;
    for (const auto &triple : compressed) {
        cout << "(" << triple.offset << ", " << triple.length << ", " << triple.nextSymbol << ")" << endl;
    }

    // Декодирование
    string decompressed = decompressLZ77(compressed);

    // Вывод результата декодирования
    cout << "Decompressed Data: " << decompressed << endl;

    return 0;
}
