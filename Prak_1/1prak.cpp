#include <iostream>
#include <ctime>
using namespace std;

float arithmetic_mean(int n, int arr[])
{
    float sum = 0, count = 0;
    for (int i = 0; i < n; ++i)
    {
        int num = arr[i];
        int sum_num = 0;
        while (num > 0)
        {
            sum_num += num % 10;
            num /= 10;
        }
        if (sum_num % 7 == 0)
        {
            sum += arr[i];
            count++;
        }
    }
    float average = sum / count;
    return average;
}

int main()
{
    cout << ("\e[1;1H\e[2J");
    cout << "n = ";
    int n, a = 1000, b = 9999;
    cin >> n;
    int arr[10000];
    cout << "arr = ";
    for (int i = 0; i < n; ++i)
    {
        cin >> arr[i];
        //arr[i]= a+(b-a)*1.0*rand()/RAND_MAX;
    }
    //unsigned int start = clock();
    cout << "average: " << arithmetic_mean(n, arr) << "  ";
    //unsigned int end = clock();
    //cout << "time = " << end - start << "    ";
}