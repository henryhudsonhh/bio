// Scores 2/2 | 100%

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define pb push_back

int main() {

  int N;
  cin >> N;
  vi v;

  for(int i = 1; i <= N; i+=2) v.pb(i);

  for(int i = 3; i <= N; ++i) { 
    if(count(v.begin(), v.end(), i)) {
      vi remInds = {}, newv = {};
      for(int j = 0; j < v.size(); ++j) {
        if((j + 1) % i == 0) {
          remInds.pb(j);
        }

      }

      for(int k = 0; k < v.size(); ++k) {
        bool flag = true;
        for(int& j : remInds) {
          if(k == j) flag = false;
        }
        if(flag) newv.pb(v[k]);
      }

      v = newv;
    }
  }

  cout << v.size();
}
