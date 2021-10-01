// Scores 24/24 | 100%

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <cmath>
#include <math.h>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<char> vc;
typedef vector<vc> vvc;

#define pb push_back
#define FOR(i, n) for(int i = 0; i < n; i++)
#define RFOR(i, n) for(int i = n - 1; i >= 0; i--)
#define SORT(v) sort(v.begin(), v.end())

int main() {
  string s1, s2;
  vc v1, v2;
  cin >> s1;
  cin >> s2;

  for(char s : s1) v1.pb(s);
  for(char s : s2) v2.pb(s);

  SORT(s1);
  SORT(s2);

  cout << (s1 == s2 ? "Anagrams" : "Not anagrams");
}
