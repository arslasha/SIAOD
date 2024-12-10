#include <iostream>
#include <vector>
using namespace std;

int countPathsDP(int n, int m) {
    vector<vector<int>> dp(n, vector<int>(m, 0));

    // Заполняем базовые случаи
    for (int i = 0; i < n; i++) dp[i][0] = 1; // Первый столбец
    for (int j = 0; j < m; j++) dp[0][j] = 1; // Первая строка

    // Вычисляем значения для остальных клеток
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < m; j++) {
            dp[i][j] = dp[i-1][j] + dp[i][j-1];
        }
    }
    return dp[n-1][m-1];
}

int main() {
    cout << ("\e[1;1H\e[2J");
    int n, m;
    cout << "Введите размеры поля (n m): ";
    cin >> n >> m;

    int result = countPathsDP(n, m);
    cout << "Количество путей (грубая сила):1 " << result << endl;
    return 0;
}
