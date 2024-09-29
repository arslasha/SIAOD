#include <iostream>   // Подключение библиотеки для работы с вводом/выводом
#include <vector>     // Подключение библиотеки для работы с динамическими массивами (векторами)
#include <bitset>     // Подключение библиотеки для работы с битовыми полями
using namespace std;  // Использование стандартного пространства имен

int main() {
    cout << "\e[1;1H\e[2J";  // Очистка экрана и установка курсора в начало
    setlocale(LC_ALL, "ru");  // Установка локали для корректного отображения русских символов

    cout << "Введите размер от 1 до 64: \n";  // Запрос размера от пользователя
    int n, num;  // Переменные для размера и элемента
    unsigned char mask = 1, mask_ = 1;  // Переменные для битовых масок
    cin >> n;  // Ввод размера

    vector<unsigned char> arr(8, 0);  // Инициализация массива размером 8 (64 бита) с нулями
    for (int i = 0; i < n; i++) {  // Цикл для ввода элементов
        cout << "Введите элемент от 0 до 63: ";  // Запрос элемента
        cin >> num;  // Ввод элемента
        if (num < 0 || num > 63) {  // Проверка, что элемент в пределах от 0 до 63
            cout << "Некорректный элемент. Завершение программы." << endl;
            return 1;  // Завершение программы при некорректном элементе
        }
        arr[num / 8] |= (mask << num % 8);  // Установка соответствующего бита в массиве
    }
    
    for (int i = 0; i < 8; i++) {  // Цикл по массиву байт
        for (int j = 0; j < 8; j++) {  // Цикл по битам в каждом байте
            if ((arr[i] & 1) == 1)  // Проверка, установлен ли младший бит
                cout << 8 * i + j << " ";  // Вывод индекса установленного бита
            arr[i] >>= 1;  // Сдвиг байта вправо на 1 бит
        }
    }
    cout << endl;  // Переход на новую строку
    return 0;  // Завершение программы
}