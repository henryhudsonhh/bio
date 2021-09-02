// Scores 25/25 | 100%

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define pb push_back

const int UP = 0, RIGHT = 1, DOWN = 2, LEFT = 3;

int score(map<vi,vvi>& map) {
  int score = 0, counter;
  vvi checked, path;
  vi prev, curr;
  for(auto const& [start, startLinks] : map) {
    path.clear();
    if(!(find(checked.begin(), checked.end(), start) != checked.end())) {
      if(startLinks.size() == 2) {
        path.pb(start);
        path.pb(startLinks[0]);
        counter = 1;
        curr = path[path.size() - 1];
        prev = path[path.size() - 2];
        while(curr != start && map[curr].size() == 2) {
          if(map[curr][0] != prev) path.pb(map[curr][0]);
          else path.pb(map[curr][1]);
          counter++;
          curr = path[path.size() - 1];
          prev = path[path.size() - 2];
        }
        if(curr == start) score += counter;
      }
    }
    for(auto v : path) checked.pb(v);
  }
  return score;
}

int getColour(vvi board, int row, int col, int dir) { // 0 = red, 1 = green
  int val = board[row][col];
  switch(dir) {
    case UP:
      if(val == 1 || val == 3 || val == 4) return 0;
      return 1;
    case RIGHT:
      if(val == 2 || val == 4 || val == 5) return 0;
      return 1;
    case DOWN:
      if(val == 1 || val == 5 || val == 6) return 0;
      return 1;
    case LEFT:
      if(val == 2 || val == 3 || val == 6) return 0;
      return 1;
  }
  return -1;
}

void addEdge(map<vi,vvi>& map, vi v1, vi v2) {
  map[v1].pb(v2);
  map[v2].pb(v1);
}

int main() {
  int N, scoreRed = 0, scoreGreen = 0;
  cin >> N;

  vvi board(N);
  map<vi,vvi> edgeMapRed, edgeMapGreen;
  int value;
  int counter = 1;

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < N; j++) {
      cin >> value;
      board[i].pb(value);
    }
  }

  for(int row = 0; row < N; row++) {
    for(int col = 0; col < N; col++) {
      if(col != N - 1 && getColour(board, row, col, RIGHT) == getColour(board, row, col + 1, LEFT)) {
        if(getColour(board, row, col, RIGHT) == 0) addEdge(edgeMapRed, {row, col}, {row, col + 1});
        else addEdge(edgeMapGreen, {row, col}, {row, col + 1});
      }
      if(row != N - 1 && getColour(board, row, col, DOWN) == getColour(board, row + 1, col, UP)) {
        if(getColour(board, row, col, DOWN) == 0) addEdge(edgeMapRed, {row, col}, {row + 1, col});
        else addEdge(edgeMapGreen, {row, col}, {row + 1, col});
      }
    }
  }

  cout << endl;

  cout << score(edgeMapRed) << " " << score(edgeMapGreen) << endl;
}
