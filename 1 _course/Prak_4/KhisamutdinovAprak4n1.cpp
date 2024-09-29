#include <iostream>
#include <cmath>
#include "headerprak4n1.h"

//Функция inputMatrix(Matrix &mat) запрашивает у пользователя ввод элементов матрицы с клавиатуры.
void inputMatrix(Matrix &mat) {
    std::cout << "Введите элементы матрицы:" << std::endl;
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.n; j++) {
            std::cin >> mat.matrix[i][j];
        }
    }
}

//Функция fillMatrix(Matrix &mat) заполняет матрицу случайными значениями от 0 до 99.
void fillMatrix(Matrix &mat) {
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.n; j++) {
            mat.matrix[i][j] = rand() % 100; // генерирует рандомное число от 0 до 99
        }
    }
}


//Функция replaceZeros(Matrix &mat) заменяет каждый нулевой элемент матрицы на ближайший ненулевой элемент.
void replaceZeros(Matrix &mat) {
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.n; j++) {
            if (mat.matrix[i][j] == 0) {
                int minDistance = mat.n * 2; // инициализируйте с максимально возможным расстоянием
                for (int p = 0; p < mat.n; p++) {
                    for (int q = 0; q < mat.n; q++) {
                        if (mat.matrix[p][q] != 0) {
                            int distance = std::abs(i - p) + std::abs(j - q);
                            if (distance < minDistance) {
                                minDistance = distance;
                                mat.matrix[i][j] = mat.matrix[p][q];
                            }
                        }
                    }
                }
            }
        }
    }
}

//Функция displayMatrix(Matrix &mat) выводит содержимое матрицы на экран.
void displayMatrix(Matrix &mat) {
    for (int i = 0; i < mat.n; i++) {
        for (int j = 0; j < mat.n; j++) {
            std::cout << mat.matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}



int main() {
    cout << ("\e[1;1H\e[2J");
    Matrix matrix;
    int x;
    std::cout << "Введите размер квадратной матрицы (n * n): ";
    std::cin >> matrix.n;

     do {
        std::cout << "\n\nСписок операций: \n" << "1)Вывести матрицу. \n";
        std::cout << "2)Заполнить матрицу значениями с клавиатуры. \n" << "3)Заполнить матрицу случайными значениями. \n"; 
        std::cout << "4)Заменить каждый нулевой элемент матрицы ближайшим ненулевым. \n";
        std::cout << "0)Выйти из программы. \n" << "Введите номер оперции: ";
        std::cin >> x;

        switch (x)
        {
        case 1:
            std::cout << "\nМатрица:\n ";
            displayMatrix(matrix);
            break;
        case 2:
            inputMatrix(matrix);
            break;
        case 3:
            fillMatrix(matrix);
            break;
        case 4:
            replaceZeros(matrix);
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