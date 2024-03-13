#include <iostream>

using namespace std;

int checknum(int n, int arr[]) { 
  int k = 0, starnum;                  // 1
  for (int i = 0;i < n;i++) {          // n + 1
    starnum = arr[i];                  // n * 2                
    while (starnum >= 10) {            //n * (len(starnum))
      starnum /= 10;                   //2 * n *(len(starnum) - 1)
    }                                  //od
    int mladnum = starnum % 10;        //2 * n
    if (starnum < mladnum) {           //n
      k += 1;                          //n * 2
    }                                  //endif
  }                                    //for
  return k;
}

int main() {
  int n; 
  cout << "n = ";
  cin >> n;
  int arr[100000];
  cout << "arr = ";
  for (int i = 0; i < n; i++){
    cin >> arr[i];
  }
  cout << "answ = " << checknum(n, arr) << "      ";
}
