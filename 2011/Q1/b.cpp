// Scores 3/3 | 100%

#include <iostream>
using namespace std;

#define pb push_back

int c(char chr) {
  return int(chr) - 64;
}
void solve(char c1, char res) {

  char c2 = 'A';
  int N = 3;

  int a[N];
  a[0] = c(c1);

  for(int j = 0; j < 26; j++) {
    a[0] = c(c1);
    c2 = char(int(c2) + 1);
    a[1] = c(c2);
    for(int i = 2; i < N; i++) {
      if(a[i - 1] + a[i - 2] > 26) {
        a[i] = (a[i - 1] + a[i - 2]) - 26;
      } else {
        a[i] = a[i - 1] + a[i - 2];
      }
    }
    if(char(a[N - 1] + 64) == res) {
      cout << c2 << endl;
    }
  }
}

int main() {
  solve('F', 'X');
  solve('Q', 'H');
}
