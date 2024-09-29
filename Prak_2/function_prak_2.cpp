#include <iostream>
#include <string>
#include "Header.h"



void input_arr(typeX* a) {
    std::cout << "\nВведите элементы массива:\n";
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


int findNumberWithFive(typeX* a) {
    for (int i = 0; i < a->n; ++i) {      
        while (a->x[i] > 0) {
            if (a->x[i] % 10 == 5) {
                return i;
            }
            a->x[i] /= 10;
        }
    }
    return -1;
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
void removeValueWithFive(typeX* a, int elem) {
    if (!isDecreasing(a)) {
        int ind = findNumberWithFive(a);
        del_elem(a, ind);    
    }
    else {
        std::cout << "Массив упорядочен по убыванию, попробуйте ещё раз!";
        return;
    }
}

//Функция для вставки нового элемента массива перед элементом меньшим его по значению
void insertElement(typeX* a, int elem) {
    // int count = 0;
    if (isDecreasing(a)) {
        for (int i = 0; i < a->n; ++i) {
            // count++;
            if (elem > a->x[i]) {
                paste_elem(a, i+1, elem);
                return;
            }
        }
    }
    else {
        std::cout << "Массив не упорядочен по убыванию, попробуйте снова!";
        return;
    }
}
