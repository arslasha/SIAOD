#include <iostream>
#include "header_prak_2.h"
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <string>

//Функция для заполнения массива
void input_arr(typeX* a) {
    std::cout << "\nВведите элементы массива:\n";
    for (int i = 0; i < a->n; ++i) {
        std::cout << i << ") ";
        std::cin >> a->x[i];
    }
}

//Функция для вызова массива
void call_arr(typeX* a) {
    for (int i = 0; i < a->n; ++i) {
        std::cout << a->x[i] << " ";
    }
}

//Функция для удаление элемента 
void del_elem(typeX* a, int pos) {
    for (int i = pos; i < a->n - 1; ++i) {
        a->x[i] = a->x[i + 1];
    }
    --a->n;
}

//Функция для втавки элемента
void paste_elem(typeX* a, int pos, int elem) {
    a->n++;
    for (int i = a->n - 1; i > pos; --i) {
        a->x[i] = a->x[i - 1];
    }
    a->x[pos] = elem;
}

//Функция для проверки правильности порядка элементов в массиве (по убыванию или нет)
bool isDecreasing(typeX* a) {
    for (int i = 0; i < a->n - 1; ++i) {
        if (a->x[i] < a->x[i + 1]) {
            return false;
        }
    }
    return true;
}

//Функция для нахождения и удаление из массива чисел, содержащих цифру 5
void removeValueWithFive(typeX* a) {
    if (!isDecreasing(a)) {
        for (int i = 0; i < a->n; ++i) {
            if (std::to_string(a->x[i]).find('5') != std::string::npos) {
                del_elem(a, i);
            }
        }
    }
    else {
        std::cout << "\nМассив упорядочен по убыванию, попробуйте ещё раз!";
        return;
    }
}

//Функция для вставки нового элемента массива перед элементом меньшим его по значению
void insertElement(typeX* a, int elem) {
    if (isDecreasing(a)) {
        for (int i = 0; i < a->n; ++i) {
            if (elem > a->x[i]) {
                paste_elem(a, i, elem);
                return;
            }
        }
    }
    else {
        std::cout << "Массив не упорядочен по убыванию, попробуйте снова!";
        return;
    }
}


int main() {
    setlocale(LC_ALL, "rus");
    typeX a;
    std::cout << "Введите размер массива: ";
    std::cin >> a.n;
    input_arr(&a);
    std::cout << "elem: ";
    int elem;
    std::cin >> elem;
    int x;

    do {
        std::cout << "\n\nСписок операций: \n";
        std::cout << "1)Вывести массив. \n";
        std::cout << "2)Удалить значения, которые содержат цифру 5 в неупорядоченном по убыванию массиве. \n";
        std::cout << "3)Вставить новый элемент массива перед элементом меньшим его по значению в упорядоченном массиве. \n"; 
        std::cout << "0)Выйти из программы. \n";
        std::cout << "Введите номер оперции: ";
        std::cin >> x;


        switch (x)
        {
        case 1:
            std::cout << "\nРезультирующий массив: ";
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
            std::cout << "\nВы ввели неправильный номер операции, попробуйте еще раз!";
            break;
        }
    } while (x != 0);
    return 0;
}