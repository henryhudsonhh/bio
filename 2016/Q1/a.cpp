// Score: 23/23 | 100%

#include <iostream>
using namespace std;

int main(){
  int latestL[2] = {1,0};
  int latestR[2] = {0,1};
  int latest[2] = {1,1};
  string st;

  cin >> st;

  for(int i = 0; i < st.length(); i++) {
    if(st[i] == 'L'){
      latestL[0] = latest[0];
      latestL[1] = latest[1];
      latest[0] += latestR[0];
      latest[1] += latestR[1];
    } else {
      latestR[0] = latest[0];
      latestR[1] = latest[1];
      latest[0] += latestL[0];
      latest[1] += latestL[1];
    }
  }
  
  // LRLL
  // L --> before latest L = 1/1, before latest R (none) = (0/1) = 1/2
  // R --> before latest L = 1/1, before latest R = 1/2 = 2/3
  // L --> before latest L = 2/3, before latest R = 1/2 = 3/5
  // L --> before latest L = 3/5, before latest R = 1/2 = 4/7

  // RL
  // R --> before latest L (none) = 1/0, before latest R = 1/1 = 2/1
  // L --> before latest L = 2/1, before latest R = 1/1 = 3/2
  
  cout << latest[0] << " / " << latest[1];
}
