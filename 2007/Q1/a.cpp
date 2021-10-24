// Scores 24/24 | 100%

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <numeric>
#include <map>
#include <cmath>
#include <math.h>
#include <bitset>
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
#define SUM(v) accumulate(v.begin(), v.end(), 0)

int combinations(vi cards) {
  int combs = 0;
  vs matches(32);

  for(int i = 1; i <= 31; i++) {
    string b = bitset<5>(i).to_string();
    vi current(5);
    FOR(j, b.length()) {
      if(b[j] == '1') current[j] = cards[j];
      else current[j] = 0;
    }

    if(SUM(current) == 15) combs++;
  }
  return combs;
}

int main() {
  int score = 0;
  vi cards(5);
  for(int i = 0; i < 5; cin >> cards[i++]);

  FOR(i, 5) {
    for(int j = i + 1; j < 5; j++) {
      if(cards[i] == cards[j]) score++;
    }
  }

  score += combinations(cards);
  cout << score;
}
