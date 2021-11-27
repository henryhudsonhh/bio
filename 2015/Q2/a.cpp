// Scores 27/27 | 100%

#include <iostream>
#include <vector>
using namespace std;

typedef vector<string> vs;
typedef vector<vs> vvs;
typedef vector<bool> vb;
typedef vector<vb> vvb;

#define pb push_back

int d_row[8] = {-1, -1, 0, 1, 1, 1, 0, -1}, d_col[8] = {0, 1, 1, 1, 0, -1, -1, -1};

void placeShip(vvb& grid, int x, int y, int len, bool h) {
  if(h) {
    for(int i = 0; i < len; i++) {
      grid[y][x + i] = true;
    }
  } else {
    for(int i = 0; i < len; i++) {
      grid[y - i][x] = true;
    }
  }
}

bool isPlacementValid(vvb grid, int x, int y, int len, bool h) {
  if(x + (len - 1) > 9 && h) {
    return false;
  } else if(y - (len - 1) < 0 && !h) {
    return false;
  }

  if(grid[y][x]) return false;
  
  for(int _ = 0; _ < len; _++) {
    for(int i = 0; i < 8; i++) {
      if(x == 0 && d_col[i] == -1) continue;
      else if(x == 9 && d_col[i] == 1) continue;
      else if(y == 0 && d_row[i] == -1) continue;
      else if(y == 9 && d_row[i] == 1) continue;
      else {
        if(grid[y + d_row[i]][x + d_col[i]]) {
          return false;
        }
      }
    }
    if(h) x++;
    else y--;
  }
  
  return true;
}

int main() {
  vvb grid(10);
  vvs ships;

  int a, c, m, r = 0, x, y, len;
  cin >> a >> c >> m;

  bool placed = false;

  for(int i = 0; i < 10; i++) for(int j = 0; j < 10; j++) {
    grid[i].pb(false);
  }

  for(int i = 0; i < 10; i++) {
    placed = false;
    if(i == 0) len = 4;
    else if(i <= 2) len = 3;
    else if(i <= 5) len = 2;
    else len = 1;

    while(!placed) {
      r = (a * r + c) % m;
      x = r % 10;
      y = 9 - (r / 10) % 10;

      r = (a * r + c) % m;
      bool horizontal = r % 2 == 0; 

      if(isPlacementValid(grid, x, y, len, horizontal)) {
        string d = horizontal ? "H" : "V";
        string x_ship = to_string(x), y_ship = to_string(9 - y); 
        ships.pb({x_ship, y_ship, d});

        placeShip(grid, x, y, len, horizontal);
        placed = true;
      }
    }
  }

  for(vs v : ships) {
    for(string s : v) {
      cout << s << " ";
    }
    cout << endl;
  }
}
