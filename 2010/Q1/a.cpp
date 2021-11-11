// Scores 25/25 | 100%

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> sortedIntArray(int n, int ln){
  vector<int> a;
  for(int i = 0; i < ln; i++){
    a.push_back(n%10);
    n /= 10;
  }
  sort(a.begin(), a.end());
  return a;
}

int main() {
  int n, cn;
  vector<int> a, o, out;
  cin >> n;
  cn = n;
  int ln = to_string(n).length();
  for(int i = 0; i < ln; i++){
    o.push_back(n%10);
    n /= 10;
  }

  sort(o.begin(), o.end());

  for(int i = 2; i < 10; ++i){
    ln = to_string(cn*i).length();
    if(sortedIntArray(cn*i,ln) == o){
      out.push_back(i);
    }
  }

  if(out.size() > 0) for(auto& n : out) cout << n << ' ';
  else cout << "NO";
}
