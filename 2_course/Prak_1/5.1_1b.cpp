#include <iostream>  // Подключение библиотеки для ввода-вывода в консоль
using namespace std;  // Использование стандартного пространства имен, чтобы не писать каждый раз std::

int main() {  // Главная функция программы
    cout << "\e[1;1H\e[2J";  // Очистка консоли и установка курсора в начало (это управляющая последовательность терминала)
    
    unsigned int x = 191;  // Объявление переменной x типа unsigned int и инициализация значением 191
    unsigned int maska = 1;  // Объявление переменной maska типа unsigned int и инициализация значением 1
    x = x | (maska << 6);  // Операция побитового ИЛИ между x и результатом сдвига maska на 6 битов влево
    cout << x << endl;  // Вывод значения переменной x в консоль
}
