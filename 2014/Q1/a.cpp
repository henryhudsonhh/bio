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
  N += 50;
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

  N -= 50;

  for(int i = 0; i < v.size(); ++i) {
    if(v[i] > N) {
      cout << (v[i-1] != N ? v[i-1] : v[i-2]) << ' ' << v[i] << endl;
      break;
    }
  }
}
