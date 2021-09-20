// Scores 25/25 | 100%

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>
#include <math.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define pb push_back
#define FOR(i, k) for (int i = 0; i < k; i++)

string toNumeral(vi vals, vector<string> nums, int n) {
  string s;
  while(n != 0) {
    FOR(i, vals.size()) {
      while(n - vals[i] >= 0) {
        s.append(nums[i]);
        n -= vals[i];
      }
    }
  }
  return s;
}

int main() {
  vi vals = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
  vector<string> nums = {"M", "CM", "D" ,"CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

  string s;

  string num;
  int n;

  cin >> num >> n;
  
  FOR(i, n) {
    s = "";
    char currentChar = ' ';
    int currC = 1;
    FOR(j, num.length()) {
      if(j == 0) currentChar = num[j];
      else if(num[j] == currentChar) currC++;
      else {
        s.append(toNumeral(vals, nums, currC) + currentChar);
        currentChar = num[j];
        currC = 1;
      }
    }
    s.append(toNumeral(vals, nums, currC) + currentChar);
    num = s;
  }
  int IC = 0, VC = 0;

  FOR(i, s.length()) {
    if(s[i] == 'I') IC++;
    else if(s[i] == 'V') VC++;
  }
  cout << IC << " " << VC;
}
