// Scores 3/3 | 100%

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define pb push_back

int solve(int d1, int d2) {
  int mins1 = 0, mins2 = 0;

  do {
    mins1 = (mins1 + 60 + d1) % 1440;
    mins2 = (mins2 + 60 + d2) % 1440;

  } while(mins1 != mins2);

  int hours = int(mins1 / 60);
  int mins = mins1 % 60;

  return hours + mins;
}

int main() {
  for(int i = 0; i <= 20; i++) {
    if(solve(0, i) != 0) cout << i << " ";
  }
}
