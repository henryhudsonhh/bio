// Scores 24/24 | 100%

#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<vc> vvc;
typedef map<char, char> mcc;

#define pb push_back
#define COUNT(v, i) count(v.begin(), v.end(), i)
#define CYCLE(v, n) rotate(v.begin(), v.begin() + n, v.end())

int d_row[4] = {-1, 0, 1, 0}, d_col[4] = {0, 1, 0, -1};

vvi equalNeighbours(vvc board, int row, int col) {
  vvi returned = {};
  for(int i = 0; i < 4; i++) {
    if(row == 0 && d_row[i] == -1) continue;
    else if(row == 3 && d_row[i] == 1) continue;
    else if(col == 0 && d_col[i] == -1) continue;
    else if(col == 3 && d_row[i] == 1) continue;
    else {
      if(board[row + d_row[i]][col + d_col[i]] == board[row][col]) {
        returned.pb({row + d_row[i], col + d_col[i]});
      }
    }
  }
  return returned;
}

void printBoard(vvc board){
  for(vc v : board) {
    for(char c : v) {
      cout << c;
    }
    cout << endl;
  }
}

int score(vvc& board) {
  int ct = 1, blockC = 0;
  vvi checkedIndexes;

  queue<vi> neighbours;

  for(int row = 0; row < 4; row++) {
    for(int col = 0; col < 4; col++) {
      blockC = 0;
      neighbours.push({row, col});
      while(neighbours.size() > 0) {
        for(int i = 0; i < 4; i++) {
          vi node = neighbours.front();
          int r = node[0], c = node[1];
          if(r == 0 && d_row[i] == -1) continue;
          else if(r == 3 && d_row[i] == 1) continue;
          else if(c == 0 && d_col[i] == -1) continue;
          else if(c == 3 && d_col[i] == 1) continue;
          else {
            vi curr = {r + d_row[i], c + d_col[i]};
            if(board[curr[0]][curr[1]] == board[r][c] && !COUNT(checkedIndexes, curr)) {
              neighbours.push(curr);
              blockC++;
              checkedIndexes.pb(curr);
            }
          }
        } 
        neighbours.pop();
      }
      if(blockC > 1) {
        ct *= blockC;
      }
    }
  }

  if(ct <= 1) {
    ct = 0;
  }

  for(int i = 0; i < checkedIndexes.size(); i++) {
    vi ind = checkedIndexes[i];
    board[ind[0]][ind[1]] = '0';
  }
  return ct;
}

void collapse(vvc& board) {
  bool flag = true;
  while(flag) {
    flag = false;
    for(int row = 0; row < 3; row++) {
      for(int col = 0; col < 4; col++) {
        if(board[row + 1][col] == '0' && board[row][col] != '0') {
          board[row + 1][col] = board[row][col];
          board[row][col] = '0';
          flag = true;
        }
      }
    }
  }
}

void fillBoard(vvc& board, vvc& fill) {
  for(int row = 3; row >= 0; row--) {
    for(int col = 0; col < 4; col++) {
      if(board[row][col] == '0') {
        board[row][col] = fill[col][0];
        vc current = fill[col];
        CYCLE(current, 1);
        fill[col] = current;
      }
    }
  }
}

int main() {
  int n = -1;
  vvc board(4), fill(4);
  fill = {
    {'G', 'R', 'G', 'R'},
    {'B', 'R', 'R', 'R'},
    {'R', 'G', 'B', 'G'},
    {'B', 'B', 'G', 'B'}
  };
  int s = 0, s1;

  for(int i = 0; i < 4; i++) {
    string row;
    cin >> row;
    for(int j = 0; j < row.length(); j++) {
      board[i].pb(row[j]);
      fill[j][3 - i] = row[j];
    }
  }
 
  cin >> n;

  vvc checkBoard = board;
  vvc copy;
  if(score(checkBoard) == 0 && n > 0) {
    cout << 0 << endl;
    cout << "GAME OVER" << endl;
  } else if(n > 0){

    while(n != 0) {
      for(int i = 0; i < n; i++) {
        copy = board;
        s1 = score(board);
        if(s1 == 0) {
          cout << s << endl;
          cout << "GAME OVER";
          n = 0;
          break;
        }

        s += s1;
        collapse(board);
        fillBoard(board, fill);
      }

      if(n != 0) {
        cout << endl;
        for(vc v : board) {
          for(char c : v) {
            cout << c;
          }
          cout << endl;
        }
        cout << endl;
        cout << s << endl;

        cin >> n;
      }
    }
  }
}
