#include <iostream>
using namespace std;

// Вычисление факториала
long long factorial(int x) {
    long long result = 1;
    for (int i = 1; i <= x; i++) {
        result *= i;
    }
    return result;
}

// Число путей с использованием комбинаторики
long long countPathsBruteForce(int n, int m) {
    return factorial(n + m - 2) / (factorial(n - 1) * factorial(m - 1));
}

int main() {
    setlocale(0, ""); 
    cout << ("\e[1;1H\e[2J");
    int n, m;
    cout << "Введите размеры поля (n m): ";
    cin >> n >> m;

    long long result = countPathsBruteForce(n, m);
    cout << "Количество путей (грубая сила): " << result << endl;
    return 0;
}
