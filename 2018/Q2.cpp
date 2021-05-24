// Score: 24/24 | 100%

#include <iostream>
#include <string>
#include <vector>
#include <string.h>
using namespace std;

int main(){
  string ipt;
  int iv, ct = 0;
  string alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
  cin >> iv >> ipt;
  vector<char> a(alph.begin(), alph.end()), b;
  while(b.size() != 26){
    ct++;
    if(ct % iv == 0) {
      b.push_back(a[0]);
      a.erase(a.begin());
    } else {
      char current = a[0];
      memmove(&a[0], &a[1], (a.size() - 1) * sizeof(a[0]));
      a[a.size() - 1] = current;
    }
  }
  for(int i = 0; i < 6; i++){
    cout << b[i];
  }
  cout << endl;
  for(int i = 0; i < ipt.length(); i++){
    for(int j = 0; j < alph.length(); j++){
      if(ipt[i] == alph[j]){
        cout << b[j];
      }
    }
    char current = b[0];
    memmove(&b[0], &b[1], (b.size() - 1) * sizeof(b[0]));
    b[b.size() - 1] = current;
  }
}
