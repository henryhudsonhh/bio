// Scores 24/24 | 100%

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

int d_row[4] = {-1, 0, 1, 0};
int d_col[4] = {0, 1, 0, -1};

vi getCoords(int pos) {
  return {(int)floor((pos - 1) / 5), (pos - 1) % 5};
}

bool areStacks(map<vi, int> grid) {
  for(auto const& [key, val] : grid) {
    if(val >= 4) return true;
  }
  return false;
}

void expandNode(vi coords, map<vi, int>& grid) {
  for(int i = 0; i < 4; i++) {
    vi c = {coords[0] + d_row[i], coords[1] + d_col[i]};
    grid[c]++;
  }
  grid[coords] -= 4;
}

void checkExpansions(map<vi, int>& grid) {
  for(auto const& [key, val] : grid) {
    if(val >= 4) {
      expandNode(key, grid);
    }
  }
}

int main() {
  map<vi, int> grid;
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      grid[{i, j}] = 0;
    }
  }
  int p, s, n, ind;
  cin >> p >> s >> n;
  int seq[s];
  for(int i = 0; i < s; cin >> seq[i++]);

  for(int i = 0; i < n; i++) {
    while(p >= 26) p -= 25;
    grid[getCoords(p)]++;
    ind = (i < s ? i : i % s);
    p += seq[ind];
    while(areStacks(grid)) {
      checkExpansions(grid);
    }
  }

  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++) {
      cout << grid[{i, j}] << " ";
    }
    cout << endl;
  }
}
