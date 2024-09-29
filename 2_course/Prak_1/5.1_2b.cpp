#include <iostream>   // Подключение библиотеки для ввода-вывода в консоль
#include <vector>     // Подключение библиотеки для работы с векторами (динамическими массивами)
#include <bitset>     // Подключение библиотеки для работы с битовыми полями
using namespace std;  // Использование стандартного пространства имен

int main() {
    cout << "\e[1;1H\e[2J";  // Очистка консоли и установка курсора в начало
    setlocale(LC_ALL, "ru");  // Установка локали для корректного отображения русских символов
    cout << "Введите размер от 1 до 64: \n";  // Запросить размер массива от пользователя
    int n, num;  // Переменные для хранения размера массива и элементов
    unsigned long long mask = 0, mask_ = 0;  // Переменные для хранения битовой маски
    cin >> n;  // Ввод размера массива

    vector<int> arr(n);  // Создание динамического массива для хранения элементов
    for (int i = 0; i < n; i++) {  // Ввод элементов массива
        cout << "Введите элемент от 0 до 63: ";  
        cin >> num;
        if (num < 0 || num > 63) {  // Проверка корректности ввода элемента
            cout << "Некорректный элемент. Завершение программы." << endl;
            return 1;  // Завершение программы при некорректном вводе
        }
        arr[i] = num;  // Сохранение введенного числа в массив
    }
    for (int i = 0; i < n; i++) {  // Формирование битовой маски
        mask = (1ULL << arr[i]);  // Сдвиг 1 на позицию arr[i] битов влево
        mask_ |= mask;  // Установка бита в итоговой маске с помощью операции побитового ИЛИ
    }
    cout << "Маска: " << bitset<64>(mask_) << endl;  // Вывод итоговой маски в виде битовой последовательности
    for (int i = 0; i < 64; i++) {  // Вывод индексов установленных битов в маске
        if ((mask_ & 1) == 1)  // Проверка младшего бита
            cout << i << " ";  // Вывод индекса установленного бита
        mask_ >>= 1;  // Сдвиг маски вправо на 1 бит
    }
    cout << endl;  // Переход на новую строку
    return 0;  // Завершение программы
}
