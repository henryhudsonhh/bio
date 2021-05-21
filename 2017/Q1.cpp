// Score: 24/24 | 100%

#include <iostream>
#include <vector>
using namespace std;

int main() {
  string row;
  cin >> row;
  vector<char> a(row.begin(), row.end());
  vector<char> b;
  for(int _ = 0; _ < row.length() - 1; _++){
    for(int i = 0; i < a.size() - 1; ++i){
      if(a[i] == a[i+1]) {
        b.push_back(a[i]);
      } else {
      if(a[i] != 'R' && a[i+1] != 'R') b.push_back('R');
      else if(a[i] != 'G' && a[i+1] != 'G') b.push_back('G');
      else if(a[i] != 'B' && a[i+1] != 'B') b.push_back('B');
      }
    }
    a = b;
    b.clear();
  }
  cout << a[0] << endl;
  
  main();
}
