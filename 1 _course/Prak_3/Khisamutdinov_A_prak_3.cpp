#include <iostream>
#include "header_prak_3.h"
#include <limits>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <vector>

//Функция для заполнения массива
void input_arr(typeX* arr) {
    std::cout << "\nВведите элементы массива:\n";
    for (int i = 0; i < arr->n; ++i) {
        std::cout << i << ") ";
        std::cin >> arr->x[i];
    }
}

//Функция для вызова массива
void call_arr(typeX* arr) {
    for (int i = 0; i < arr->n; ++i) {
        std::cout << arr->x[i] << " ";
    }
}

//Функция для удаление элемента 
void del_elem(typeX arr, int pos) {
    for (int i = pos; i < arr.n; i++) {
        arr.x[i] = arr.x[i + 1];
    }
    --arr.n;
    typeitem *newPtr = (typeitem*)realloc(arr.x, (arr.n - 1) *sizeof(typeitem));
    if (newPtr != nullptr) {
    arr.x = newPtr;
    }
}

//Функция для вcтавки элемента
void paste_elem(typeX &arr, int pos, int elem) {
    arr.n++;
    for (int i = arr.n - 1; i > pos; i--) {
        arr.x[i] = arr.x[i - 1];
    }
    typeitem *newPtr = (typeitem*)realloc(arr.x, (arr.n + 1) *sizeof(typeitem));
    if (newPtr != nullptr)
        arr.x = newPtr;
    arr.x[pos] = elem;
}


//Функция для проверки правильности порядка элементов в массиве (по убыванию или нет)
bool isDecreasing(typeX arr) {
    for (int i = 0; i < arr.n - 1; ++i) {
        if (arr.x[i] < arr.x[i + 1]) {
            return false;
        }
    }
    return true;
}

bool valueWithFive(int elem){
    if (std::to_string(elem).find('5') != std::string::npos){
        return true;
    }
    return false;
}

//Функция для нахождения и удаление из массива чисел, содержащих цифру 5
void removeValueWithFive(typeX arr) {
    if (!isDecreasing(arr)) {
        for (int i = 0; i < arr.n; ++i) {
            if (std::to_string(arr.x[i]).find('5') != std::string::npos) {
                del_elem(arr, i);
            }
        }
    }
    else {
        std::cout << "\nМассив упорядочен по убыванию, попробуйте ещё раз!";
        return;
    }
}

//Функция для вставки нового элемента массива перед элементом меньшим его по значению
void insertElement(typeX arr, int elem) {
    if (isDecreasing(arr)) {
        for (int i = 0; i < arr.n; ++i) {
            if (elem > arr.x[i]) {
                paste_elem(arr, i, elem);
                return;
            }
        }
    }
    else {
        std::cout << "Массив не упорядочен по убыванию, попробуйте снова!";
        return;
    }
}

//Функция для создания нового массива 
void createNewArr(typeX arr, typeX* new_arr){
    new_arr->n = 0;
    typeitem* tmp;
    new_arr->x = (typeitem*)malloc(0);
    for(int i = 0; i < arr.n; ++i){
        if (valueWithFive(arr.x[i])){
            if ((new_arr->x = (typeitem*)realloc(new_arr->x, (new_arr->n + 1) * sizeof(typeitem)))!= nullptr) {
                new_arr->x[new_arr->n] = arr.x[i];
                new_arr->n++;
            }
        }
    }
}



int main() {
    cout << ("\e[1;1H\e[2J");
    setlocale(LC_ALL, "rus");
    int n, x;
    typeX arr(n), new_arr(0);
    std::cout << "Введите размер массива: "; std::cin >> arr.n;
    input_arr(&arr);
    int elem; std::cout << "Введите элемент для вствки в массив: "; std::cin >> elem;
    
    do {
        std::cout << "\n\nСписок операций: \n" << "1)Вывести массив. \n";
        std::cout << "2)Удалить значения, которые содержат цифру 5 в неупорядоченном по убыванию массиве. \n" << "3)Вставить новый элемент массива перед элементом меньшим его по значению в упорядоченном массиве. \n"; 
        std::cout << "4)Сформировать новый массив из чисел содержаших цифру 5. \n" << "5)Вывести новый массив. \n";
        std::cout << "0)Выйти из программы. \n" << "Введите номер оперции: ";
        std::cin >> x;
        switch (x)
        {
        case 1:
            std::cout << "\nРезультирующий массив: ";
            call_arr(&arr);
            break;
        case 2:
            removeValueWithFive(arr);
            break;
        case 3:
            insertElement(arr, elem);
            break;
        case 4:
            createNewArr(arr, &new_arr);
            break;
        case 5:
            std::cout << "\nНовый массив: ";
            call_arr(&new_arr);
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
