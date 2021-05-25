// Score: 24/24 | 100%

#include <iostream>
#include <math.h>
#include <set>
using namespace std;

set<int> sumPrimeFactors(int n){
  set<int> set;
  int sum = 0;
  while(n%2 == 0){
    set.insert(2);
    n /= 2;
  }

  int m = (int)(sqrt(n));
  for(int i = 3; i <= m; i+=2){
    while(n%i == 0){
      set.insert(i);
      n /= i;
    }
  }

  if(n > 2){
    set.insert(n);
  }

  return set;
}

int main() {
  int n;
  cin >> n;
  int prod = 1;
  set<int> set = sumPrimeFactors(n);
  for(auto& num : set){
    prod *= num;
  }
  cout << prod;
}
