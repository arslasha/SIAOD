#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

// Функция для сжатия текста
string compressText(const char *text)
{
    string result;
    int length = strlen(text);
    for (int i = 0; i < length;)
    {
        char currentChar = text[i];
        int count = 1;
        while (i + count < length && text[i + count] == currentChar)
        {
            count++;
        }
        if (count > 1)
        {
            result += "(" + to_string(count) + ")" + currentChar;
            i += count;
        }
        else
        {
            string nonSeries;
            while (i < length && (i == 0 || text[i] != text[i + 1]))
            {
                nonSeries += text[i++];
            }
            result += "(-" + to_string(nonSeries.size()) + ")" + nonSeries;
        }
    }
    return result;
}

// Функция для восстановления текста
string decompressText(const char *text)
{
    string result;
    int length = strlen(text);
    for (int i = 0; i < length;)
    {
        if (text[i] == '(')
        {
            int j = i + 1;
            while (text[j] != ')')
                j++;
            string numStr = string(text + i + 1, text + j);
            int num = stoi(numStr);
            char symbol = text[j + 1];
            if (symbol == '-')
            {
                result += string(text + j + 2, text + j + 2 + num);
                i = j + 2 + num;
            }
            else
            {
                result.append(num, symbol);
                i = j + 2;
            }
        }
        else
        {
            result += text[i++];
        }
    }
    return result;
}

// Функция для вычисления коэффициента сжатия
double compressionRatio(const char *original, const char *compressed)
{
    return (double)strlen(compressed) / strlen(original);
}

// Текстовое меню
void menu()
{
    char *text = nullptr;
    int choice;
    do
    {
        cout << "Menu:" << endl;
        cout << "1. Enter text" << endl;
        cout << "2. Compress text" << endl;
        cout << "3. Decompress text" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice)
        {
        case 1:
        {
            cout << "Enter text: ";
            string input;
            getline(cin, input);

            delete[] text;                       // Удаление предыдущего текста, если он был
            text = new char[input.length() + 1]; // Выделение новой памяти
            strcpy(text, input.c_str());         // Копирование строки в выделенную память
            break;
        }
        case 2:
        {
            if (text == nullptr)
            {
                cout << "No text entered yet." << endl;
            }
            else
            {
                string compressed = compressText(text);
                cout << "Compressed text: " << compressed << endl;
            }
            break;
        }
        case 3:
        {
            if (text == nullptr)
            {
                cout << "No text entered yet." << endl;
            }
            else
            {
                string decompressed = decompressText(text);
                cout << "Decompressed text: " << decompressed << endl;
            }
            break;
        }
        case 4:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice!" << endl;
        }
    } while (choice != 4);

    delete[] text; // Освобождение памяти перед выходом
}

int main()
{
    menu();
    return 0;
}

