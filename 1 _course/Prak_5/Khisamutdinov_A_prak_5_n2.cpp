#include <iostream>
#include <string>

using namespace std;

// Функция для сжатия текста
string compressText(const string& text)
{
    string result;
    int length = text.length();
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
string decompressText(const string& text)
{
    string result;
    int length = text.length();
    for (int i = 0; i < length;)
    {
        if (text[i] == '(')
        {
            int j = i + 1;
            while (text[j] != ')')
                j++;
            string numStr = text.substr(i + 1, j - (i + 1));
            int num = stoi(numStr);
            char symbol = text[j + 1];
            if (symbol == '-')
            {
                result += text.substr(j + 2, num);
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
double compressionRatio(const string& original, const string& compressed)
{
    return static_cast<double>(compressed.length()) / original.length();
}

// Текстовое меню
void menu()
{
    string text;
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
        cin.ignore(); // Игнорирование символа новой строки после ввода выбора

        switch (choice)
        {
        case 1:
        {
            cout << "Enter text: ";
            getline(cin, text);
            break;
        }
        case 2:
        {
            if (text.empty())
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
            if (text.empty())
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
}

int main()
{
    menu();
    return 0;
}
