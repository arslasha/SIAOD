#include <iostream>
#include "Header.h"
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <string>

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
void removeValueWithFive(typeX* a, int elem) {
    if (!isDecreasing(a)) {
        for (int i = 0; i < a->n; ++i) {
            if (std::to_string(a->x[i]).find('5') != std::string::npos) {
                del_elem(a, i);
            }
        }
    }
    else {
        std::cout << "Массив упорядочен по убыванию, попробуйте ещё раз!";
        return;
    }
}
//Функция для вставки нового элемента массива перед элементом меньшим его по значению
void insertElement(typeX* a, int elem) {
    int count = 0;
    if (isDecreasing(a)) {
        for (int i = 0; i < a->n; ++i) {
            count++;
            if (elem > a->x[i]) {
                paste_elem(a, count, elem);
                return;
            }
        }
    }
    else {
        std::cout << "Массив не упорядочен по убыванию, попробуйте снова!";
        return;
    }
}

void input_arr(typeX* a) {
    std::cout << "Введите элементы массива:\n";
    for (int i = 0; i < a->n; ++i) {
        std::cout << i << ") ";
        std::cin >> a->x[i];
    }
}

void call_arr(typeX* a) {
    for (int i = 0; i < a->n; ++i) {
        std::cout << a->x[i] << " ";
    }
}

void del_elem(typeX* a, int pos) {
    for (int i = pos; i < a->n - 1; ++i) {
        a->x[i] = a->x[i + 1];
    }
    --a->n;
}

void paste_elem(typeX* a, int pos, int elem) {
    a->n++;
    for (int i = a->n - 1; i > pos; --i) {
        a->x[i] = a->x[i - 1];
    }
    a->x[pos - 1] = elem;
}

int main() {
    std::cout << ("\e[1;1H\e[2J");
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
        std::cout << "3)Вставить новый элемент массива перед элементом меньшим его по значению в упорядоченном массиве. \n" << "0)Выйти из программы. \n";
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
            std::cout << "Вы ввели неправильный номер операции, попробуйте еще раз!";
            break;
        }
    } while (x != 0);
    return 0;
}