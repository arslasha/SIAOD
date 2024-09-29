#include <iostream>    // Подключение библиотеки для работы с вводом/выводом
#include <vector>      // Подключение библиотеки для работы с динамическими массивами (векторами)
#include <bitset>      // Подключение библиотеки для работы с битовыми полями
#include <fstream>     // Подключение библиотеки для работы с файлами
#include <string>      // Подключение библиотеки для работы со строками
#include <chrono>      // Подключение библиотеки для работы с временем
using namespace std;   // Использование стандартного пространства имен

void newFile() {  // Функция для создания нового файла с рандомными числами
    const long n = 1000000;         // Начальное значение для диапазона чисел
    const long n_max = 9999999;     // Конечное значение для диапазона чисел
    const int len = n_max - n + 1;  // Количество элементов в диапазоне
    long* array = new long[len];    // Динамическое выделение массива для чисел

    for (long i = 0; i < len; i++) {  // Заполнение массива числами от n до n_max
        array[i] = n + i;             // Каждому элементу присваивается соответствующее значение
    }
    srand(time(NULL));  // Инициализация генератора случайных чисел текущим временем
    for (long i = 0; i < len; i++)  // Перемешивание массива с помощью случайных перестановок
        swap(array[i], array[rand() % len]);  // Обмен значениями с случайным индексом

    ofstream fout;  // Создание объекта для записи в файл
    fout.open("Text.txt");  // Открытие файла для записи

    if (!fout.is_open())  // Проверка, удалось ли открыть файл
        cout << "Ошибка открытия файла! \n";  // Сообщение об ошибке
    else {
        for (int i = 0; i < len; i++)  // Запись элементов массива в файл построчно
            fout << array[i] << endl;  // Запись числа в файл
    }

    fout.close();  // Закрытие файла
    delete[] array;  // Освобождение памяти, выделенной под массив
}



int main() {
    cout << ("\e[1;1H\e[2J");
    setlocale(LC_ALL, "ru");

    const int n = 10000000 / 8;
    int num;
    auto start = chrono::high_resolution_clock::now();
    unsigned char mask = 1;
    vector <unsigned char> arr(n);
    string file = "Text.txt";
    ifstream fin;
    fin.open(file);
    if (!fin.is_open())
        cout << "Ошибка открытия файла" << endl;
    else {
        while (!fin.eof()) {
            fin >> num;
            arr[num / 8] |= (mask << num % 8);
        }
    }

    fin.close();
    auto end = chrono::high_resolution_clock::now();
    ofstream fout;
    fout.open(file);
    if (!fout.is_open())
        cout << "Ошибка открытия файла!\n";
    else {
        for (int i = 0; i < n; i++){
            for (int j = 0; j < 8; j++) {
                if ((arr[i] & 1) == 1)
                    fout << 8 * i * j << endl;
                arr[i] >>= 1;
            }
        }
    }
    fout.close();
    chrono::duration<double, milli> duration = end - start;
    arr.shrink_to_fit();
    cout << arr.capacity() << " b\n";
    cout << arr.capacity() / 1024 << " kb\n";
    cout << arr.capacity() / (1024 * 1024) << " mb\n";
    cout << "Время работы алгоритма: " << duration.count() << " миллисекунд\n";
}