// Scores 25/25 | 100%

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;

#define pb push_back
#define COUNT(v, i) count(v.begin(), v.end(), i)

bool isPrime(int n) {
  for (int i = 2; i < n; i++) if (n % i == 0) return false;
  return true;
}

int main() {
  int n, c = 0;
  cin >> n;
  vi check = {1};

  for(int i = 2; i < n; i++) {
    if(i % 2 == 0) continue;
    else if(isPrime(i)){
      if(isPrime(n - i) && !COUNT(check, n - i)) {
        c++;
        check.pb(i);
      }
    }
  }
  
  cout << c;
}
