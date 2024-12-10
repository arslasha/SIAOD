#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Функция для поиска максимального палиндрома в строке
string findLongestPalindrome(const string &str) {
    int n = str.size();
    if (n == 0) return "";

    vector<vector<bool>> dp(n, vector<bool>(n, false));  // Таблица для динамического программирования
    int maxLength = 1;  // Длина максимального палиндрома
    int start = 0;      // Начальная позиция палиндрома

    // Все подстроки длиной 1 являются палиндромами
    for (int i = 0; i < n; ++i) dp[i][i] = true;

    // Проверяем подстроки длиной 2
    for (int i = 0; i < n - 1; ++i) {
        if (str[i] == str[i + 1]) {
            dp[i][i + 1] = true;
            start = i;
            maxLength = 2;
        }
    }

    // Проверяем подстроки длиной больше 2
    for (int len = 3; len <= n; ++len) {
        for (int i = 0; i < n - len + 1; ++i) {
            int j = i + len - 1;  // Конечный индекс подстроки
            if (str[i] == str[j] && dp[i + 1][j - 1]) {
                dp[i][j] = true;
                if (len > maxLength) {
                    start = i;
                    maxLength = len;
                }
            }
        }
    }

    return str.substr(start, maxLength);  // Возвращаем максимальный палиндром
}

int main() {
    setlocale(0, ""); 
    cout << ("\e[1;1H\e[2J");  // Очистка экрана с помощью escape-последовательности

    string str = "babaddadgfg";
    cout << "Исходная строка: " << str << endl;

    string longestPalindrome = findLongestPalindrome(str);
    cout << "Максимальная подстрока-палиндром: " << longestPalindrome << endl;

    return 0;
}
