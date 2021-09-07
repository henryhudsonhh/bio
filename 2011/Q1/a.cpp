// Scores 24/24 | 100%

#include <iostream>
using namespace std;

#define pb push_back

int c(char chr) {
  return int(chr) - 64;
}

int main() {
  char c1, c2;
  int N;
  cin >> c1 >> c2 >> N;

  int a[N];
  a[0] = c(c1);
  a[1] = c(c2);

  for(int i = 2; i < N; i++) {
    if(a[i - 1] + a[i - 2] > 26) {
      a[i] = (a[i - 1] + a[i - 2]) - 26;
    } else {
      a[i] = a[i - 1] + a[i - 2];
    }
  }

  cout << char(a[N - 1] + 64);
}
