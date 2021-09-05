// Scores 25/25 | 100%

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define pb push_back

int main() {
  int d1, d2;
  int mins1 = 0, mins2 = 0;

  cin >> d1 >> d2;

  do {
    mins1 = (mins1 + 60 + d1) % 1440;
    mins2 = (mins2 + 60 + d2) % 1440;

  } while(mins1 != mins2);

  int hours = int(mins1 / 60);
  if(hours < 10) cout << 0 << hours << ":";
  else cout << hours << ":";

  int mins = mins1 % 60;
  if(mins < 10) cout << 0 << mins;
  else cout << mins;
}
