// Scores 24/24 | 100%

#include <iostream>
#include <numeric>
using namespace std;

int main() {
  float f;
  int n, d = 10000, hcf;

  cin >> f;
  n = (int)(f * d);

  hcf = gcd(n, d);

  while(hcf != 1 ) {
    n /= hcf;
    d /= hcf;
    
    hcf = gcd(n, d);
  }

  cout << n << " / " << d << endl;
}
