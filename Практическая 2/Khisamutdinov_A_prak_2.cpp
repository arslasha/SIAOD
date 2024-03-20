#include <iostream>
#include "Header.h"
#include <limits>
#include <stdio.h>
#include <stdlib.h>

int main() {
    std::cout << ("\e[1;1H\e[2J");
    typeX a;
    
    std::cout << "Введите размер массива: ";
    std::cin >> a.n;
    
    std::cout << "Введите элементы массива:" << "\n";
    int elem;
    std::cin >> elem;
    input_arr(&a);
    int x;

    do {
        std::cout << "Список операций: \n";
        std::cout << "1)Вывести массив. \n";
        std::cout << "2)Удалить значения, которые содержат цифру 5 в неупорядоченном по убыванию массиве. \n";
        std::cout << "3)Вставить новый элемент массива перед элементом меньшим его по значению в упорядоченном массиве. \n" << "0)Выйти из программы. \n";
        std::cout << "Введите номер оперции: ";
        std::cin >> x;
    
    
        switch (x)
        {
        case 1:
            std::cout << "Результирующий массив: ";
            call_arr(&a);
            break;
        case 2:
            removeValueWithFive(&a, elem);
            break;
        case 3:
            insertElement(&a, elem);
            break;        
        case(0):
            std::cout << "Вы вышли из программы! \n";
            break;
        
        default:
            std::cout << "Вы ввели неправильный номер операции, попробуйте еще раз!";
            break;
        }
    } while(x != 0);
    return 0;
}
