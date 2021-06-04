#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <string>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;
typedef vector<char> vc;
typedef vector<vc> vvc;


// Dot Class
class Dot{
  public:
    // List of connections (format = 0:up ,1:right, 2:down, 3:left, value of pair = id (coords) of connected dot, empty = -1)
    map<int, vi> cts = {
      {0, {-1,-1}},
      {1, {-1,-1}},
      {2, {-1,-1}},
      {3, {-1,-1}}
    };
    vi id = {0, 0}; // coords
    Dot(){}
    Dot(int col, int row){
      this->id[0] = col;
      this->id[1] = row;
    }
};

class Board{
  public:
    Dot board[6][6];

    Board(int h, int w){
      for(int i = 0; i < h; i++) for(int j = 0; j < w; j++) { // Adding Dots to Board
        Dot d(i,j);
        // If Dot is on an edge, set the connection to the outside to -2: invisible
        if(i == 0) d.cts[0] = {-2,-2};
        if(i == 5) d.cts[2] = {-2,-2};
        if(j == 0) d.cts[3] = {-2,-2};
        if(j == 5) d.cts[1] = {-2,-2};
        this->board[i][j] = d;
      }
    }
};

Board b(6,6); // global Board
char output[5][5]; // Output grid
int boxes1, boxes2; // global Box Count for each player

int getNewPos(int pos, int mod){ // Gets player position from the number 1-36 ----> this works
  int max = 36;
  if(pos + mod <= max) return pos + mod;
  else return (pos + mod) - max;
}

Dot getDot(int pos){ // Gets dot using the player position number (1-36) ----> this works
  int row = floor(pos / 6);
  int col = pos - (floor(pos / 6) * 6) - 1;
  return b.board[row][col];
}

bool connectionExists(Dot d1, Dot d2){ // No idea if this works, I assume so
  for(int i = 0; i < d1.cts.size(); i++){
    if(d1.cts[i] == d2.id){ // d1.cts[i] gives an id
      return true;
    }
  }
  return false;
}

bool checkConnections(Dot dot, Dot latestCon, vi dirs, int player){ // checking connections around each box
  Dot copy = latestCon;
  Dot copy2 = latestCon;
  
  copy2.id = {copy.id[0]+dirs[0], copy.id[1]+dirs[1]}; // dirs = directions, given as a sequence of three moves (since we start from the newly connected dot, it should only take three lines to reach the original dot), in the format of {u/d,l/r,u/d,l/r,u/d,l/r}, where u/d = up/down, l/r = left/right
  if(connectionExists(copy, copy2)) {
    copy.id = {copy2.id[0]+dirs[2], copy2.id[1]+dirs[3]};
    if(connectionExists(copy2, copy)){
      copy2.id = {copy.id[0]+dirs[4], copy.id[1]+dirs[5]};
      if(connectionExists(copy2, dot)){
        if(player == 1) boxes1++;
        else boxes2++;
        return true;
      }
    }
  }
  return false;
}

void drawBoard(){
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++){
      cout << output[i][j];
    }
    cout << endl;
  }
}

void claimBoxes(Dot dot, int player, Dot latestCon, int newCon){
  char icon = player == 1 ? 'X' : 'O';
  Dot copy = latestCon;
  Dot copy2 = copy;
  if(newCon == 0){
    if(checkConnections(dot, latestCon, {0,1,1,0,0,-1}, player)) output[dot.id[0]-1][dot.id[1]] = icon;
    // right down left
    if(checkConnections(dot, latestCon, {0,-1,1,0,0,1}, player)) output[dot.id[0]-1][dot.id[1]-1] = icon;
    // left down right
  } else if(newCon == 1){
    if(checkConnections(dot, latestCon, {-1,0,0,-1,1,0}, player)) output[dot.id[0]-1][dot.id[1]] = icon;
    // up left down
    if(checkConnections(dot, latestCon, {1,0,0,-1,-1,0}, player)) output[dot.id[0]][dot.id[1]] = icon;
    // down left up
  } else if(newCon == 2){
    if(checkConnections(dot, latestCon, {0,1,-1,0,0,-1}, player)) output[dot.id[0]][dot.id[1]] = icon;
    // right up left
    if(checkConnections(dot, latestCon, {0,-1,-1,0,0,1}, player)) output[dot.id[0]][dot.id[1]-1] = icon;
    // left up right
  } else if(newCon == 3){
    if(checkConnections(dot, latestCon, {-1,0,0,1,1,0}, player)) output[dot.id[0]-1][dot.id[1]-1] = icon;
    // up right down
    if(checkConnections(dot, latestCon, {1,0,0,1,-1,0}, player)) output[dot.id[0]][dot.id[1]-1] = icon;
    // down right up
  }

}

void addConnection(Dot dot, int player){
  map<int, vi> cts = dot.cts;
  Dot conDot;

  // Get earliest empty connection
  int newCon = 0;
  for(int i = 0; i < cts.size(); i++){
    if(cts[i][0] == -1){
      newCon = i;
      break;
    }
  }

  // Based off predicted new connection, find Dot with modified current id
  int row = dot.id[0], col = dot.id[1];
  if(newCon == 0) {
    conDot = b.board[row-1][col];
    conDot.cts[2] = {row, col};
  } else if(newCon == 1) {
    conDot = b.board[row][col+1];
    conDot.cts[3] = {row, col};
  } else if(newCon == 2) {
    conDot = b.board[row+1][col];
    conDot.cts[0] = {row, col};
  } else if(newCon == 3) {
    conDot = b.board[row][col-1];
    conDot.cts[1] = {row, col};
  }

  claimBoxes(dot, player, conDot, newCon);
}

bool hasAvailableCons(map<int, vi> &cts){ // has available connections
    for(int i = 0; i < cts.size(); i++){
        if(cts[i][0] == -1){ // connection is empty
            return true;
        }
    }
    return false;
}

int main(){
  int pos1, mod1, pos2, mod2, t, cpos, cplayer;
  cin >> pos1 >> mod1 >> pos2 >> mod2 >> t;
  
  for(int i = 0; i < 5; i++) for(int j = 0; j < 5; j++){
      output[i][j] = '*';
  }

  for(int i = 0; i < t; i++){

    // Get New Positions of the Current Player

    if(i % 2 == 0){
      pos1 = getNewPos(pos1, mod1);
      cpos = pos1;
      cplayer = 1;
    } else {
      pos2 = getNewPos(pos2, mod2);
      cpos = pos2;
      cplayer = 2;
    }

    // Get Corresponding Dot from Board, having been given a number from 1-36

    Dot d = getDot(cpos);

    
    // Add Connection to Dot
    // While dot does not have any available connections, move one dot along (position++)    
    while(!hasAvailableCons(d.cts)){
      cpos = getNewPos(cpos, 1);
      d = getDot(cpos);
    }
    
    addConnection(d, cplayer);
  }
  drawBoard();

  cout << boxes1 << " " << boxes2 << endl;
}
