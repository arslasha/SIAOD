#include <iostream>
#include <string>
#include <sstream>

using namespace std;

// Функция для удаления всех слов, равных заданному
string removeWord(const string &sentence, const string &wordToRemove) {
    stringstream ss(sentence);  // Строковый поток для разделения предложения на слова
    string result = "";         // Результирующая строка
    string word;                // Текущее слово

    // Проходим по каждому слову в предложении
    while (ss >> word) {
        // Если текущее слово не совпадает с удаляемым, добавляем его в результат
        if (word != wordToRemove) {
            if (!result.empty()) result += " ";  // Добавляем пробел перед следующим словом
            result += word;
        }
    }
    return result;
}

int main() {
    setlocale(0, ""); 
    cout << ("\e[1;1H\e[2J");  // Очистка экрана с помощью escape-последовательности

    string sentence = "Привет мир , мир прекрасен , и мир огромен.";
    string wordToRemove = "мир";

    cout << "Исходное предложение: " << sentence << endl;
    cout << "Удаляем слово: " << wordToRemove << endl;

    string updatedSentence = removeWord(sentence, wordToRemove);
    cout << "Обновленное предложение: " << updatedSentence << endl;

    return 0;
}
