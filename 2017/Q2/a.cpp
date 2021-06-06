#include <iostream>
#include <vector>
#include <math.h>
#include <map>
#include <string>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;


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

class Box{
  public:
    map<int, int> sides = {
      {0, 0}, // top
      {1, 0}, // right
      {2, 0}, // bottom
      {3, 0} // left
    };
    int loc[2] = {};
    int claimer = 0;
    Box(){}
    Box(int row, int col){
      this->loc[0] = row;
      this->loc[1] = col;
    }
};

class Board{
  public:
    Dot board[6][6];
    Box boxes[5][5];

    Board(int h, int w){
    
      // Dot board
      for(int i = 0; i < h; i++) for(int j = 0; j < w; j++) { // Adding Dots to Board
        Dot d(i,j);
        // If Dot is on an edge, set the connection to the outside to -2: invisible
        if(i == 0) d.cts[0] = {-2,-2};

        if(i == 5) d.cts[2] = {-2,-2};

        if(j == 0) d.cts[3] = {-2,-2};
        
        if(j == 5) d.cts[1] = {-2,-2};

        this->board[i][j] = d;
      }

      // Box board
      for(int i = 0; i < h - 1; i++) for(int j = 0; j < w - 1; j++) this->boxes[i][j] = Box(i,j);
    }
};

Board b(6,6); // global Board
char output[5][5]; // Output grid
int count = 0;
int boxes1 = 0, boxes2 = 0; // global Box Count for each player

// If line is vertical
  // If higher dot is not on an edge of board (can only be on left and right edge)
    // Make sides of boxes to the side (3 and 1) 1
    // box1 loc = higher dot, col - 1
    // box2 loc = higher dot
  // Else
    // depending on col, ignore box1 (col=0) or box2 (col=4)

// If line is horizontal
  // If left dot is not on an edge of the board (can only be on top and bottom edge)
    // Make sides of boxes on the ends (2 and 0) 1
    // box1 loc = left dot, row - 1
    // box2 loc = left dot
  // Else
    // depending on row, ignore box1 (row=0) or box2(row=4)

bool conIsVertical(int row1, int row2){
  return row1 == row2 ? false : true;
}

void printBox(Box box){  
  for(int i = 0; i < 4; i++){
    cout << box.sides[i] << " ";
  }
  cout << endl;
}

void drawBoard(){
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++){
      Box bx = b.boxes[i][j];
      if(bx.claimer == 1) {cout << "X"; boxes1++;}
      else if(bx.claimer == 2) {cout << "O"; boxes2++;}
      else cout << "*";
    }
    cout << endl;
  }
}

void updateBoxes(Dot d1, Dot d2){ // this works
  if(conIsVertical(d1.id[0], d2.id[0])){ // is Vertical
    // cout << "Vertical" << endl;
    Dot m = d1.id[0] < d2.id[0] ? d1 : d2;
    if(m.id[1] == 0){
      // cout << "Box 2 (Right) = " << m.id[0] << ' ' << m.id[1] << " when marker (left) = " << m.id[0] << ' ' << m.id[1] << endl;
      Box &box2 = b.boxes[m.id[0]][m.id[1]];
      box2.sides[3] = 1;
      // cout << "Set Box2 side [3] to 1" << endl;
      // printBox(box2);
    } else if(m.id[1] == 5){
      // cout << "Box 1 (Left) = " << m.id[0] << ' ' << m.id[1]-1 << " when marker (left) = " << m.id[0] << ' ' << m.id[1] << endl;
      Box &box1 = b.boxes[m.id[0]][m.id[1]-1];
      box1.sides[1] = 1;
      // cout << "Set Box1 side [1] to 1" << endl;
      // printBox(box1);
    } else {
      // cout << "Box 1 (Left) = " << m.id[0] << ' ' << m.id[1]-1 << " when marker (left) = " << m.id[0] << ' ' << m.id[1] << endl;
      Box &box1 = b.boxes[m.id[0]][m.id[1]-1];
      // cout << "Box 2 (Right) = " << m.id[0] << ' ' << m.id[1] << " when marker (left) = " << m.id[0] << ' ' << m.id[1] << endl;
      Box &box2 = b.boxes[m.id[0]][m.id[1]];
      box1.sides[1] = 1;
      box2.sides[3] = 1;
      // cout << "Set Box1 side [1] to 1" << endl;
      // cout << "Set Box2 side [3] to 1" << endl;
      // printBox(box1);
      // printBox(box2);
    }
  } else { // is Horizontal
    // cout << "Horizontal" << endl;
    // cout << "[    " << count << "    ]" << endl;
    Dot m = d1.id[1] < d2.id[1] ? d1 : d2;
    if(m.id[0] == 0){
      // cout << "Box 2 (Bottom) = " << m.id[0] << ' ' << m.id[1] << " when marker (left) = " << m.id[0] << ' ' << m.id[1] << endl;
      Box &box2 = b.boxes[m.id[0]][m.id[1]];
      box2.sides[0] = 1;
      // cout << "Set Box2 side [0] to 1" << endl;
      // printBox(box2);
    } else if(m.id[0] == 5){
      // cout << "Box 1 (Top) = " << m.id[0]-1 << ' ' << m.id[1] << " when marker (left) = " << m.id[0] << ' ' << m.id[1] << endl;
      Box &box1 = b.boxes[m.id[0]-1][m.id[1]];
      box1.sides[2] = 1;
      // cout << "Set Box1 side [2] to 1" << endl;
      // printBox(box1);
    } else {
      // cout << "Box 1 (Top) = " << m.id[0]-1 << ' ' << m.id[1] << " when marker (left) = " << m.id[0] << ' ' << m.id[1] << endl;
      Box &box1 = b.boxes[m.id[0]-1][m.id[1]];
      Box &box2 = b.boxes[m.id[0]][m.id[1]];
      box1.sides[2] = 1;
      box2.sides[0] = 1;
      // cout << "Set Box1 side [2] to 1" << endl;
      // cout << "Set Box2 side [0] to 1" << endl;
      // printBox(box1);
      // printBox(box2);
    }
  }
  // drawBoard();
}

int getNewPos(int pos, int mod){ // Gets player position from the number 1-36 ----> this works
  int max = 36;
  if(pos + mod <= max) return pos + mod;
  else return (pos + mod) - max;
}

Dot* getDot(int pos){ // Gets dot using the player position number (1-36) ----> this works
  int row = floor(pos / 6);
  int col = pos - (floor(pos / 6) * 6) - 1;
  return &b.board[row][col];
}

bool isBoxContained(Box box){
  for(int i = 0; i < 4; i++){
    if(box.sides[i] == 0) return false;
  }
  return true;
}

void claimBoxes(Dot dot, int player){
  for(int i = 0; i < 5; i++) {
    for(int j = 0; j < 5; j++){
      int ct = 0;
      Box &bx = b.boxes[i][j];
      if(bx.claimer == 0){
        if(isBoxContained(bx)) bx.claimer = player;
      }
    }
  }
}

void addConnection(Dot &dot, int player){
  map<int, vi> &cts = dot.cts;
  Dot conDot;

  // Get earliest empty connection
  int newCon = 0;
  if(player == 1){
    if(cts[0][0] == -1) newCon = 0;
    else if(cts[1][0] == -1) newCon = 1;
    else if(cts[2][0] == -1) newCon = 2;
    else newCon = 3;
  } else {
    if(cts[0][0] == -1) newCon = 0;
    else if(cts[3][0] == -1) newCon = 3;
    else if(cts[2][0] == -1) newCon = 2;
    else newCon = 1;
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

  cts[newCon] = {conDot.id[0], conDot.id[1]};

  // cout << "Player " << player << endl;
  updateBoxes(dot, conDot);

  claimBoxes(dot, player);
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

  for(int i = 0; i < t; i++){

    count++;

    // Get New Positions of the Current Player
    if(i % 2 == 0){
      if(i > 1) pos1 = getNewPos(pos1, mod1);
      cpos = pos1;
      cplayer = 1;
    } else {
      if(i > 1) pos2 = getNewPos(pos2, mod2);
      cpos = pos2;
      cplayer = 2;
    }

    // Get Corresponding Dot from Board, having been given a number from 1-36

    Dot *d = getDot(cpos);

    // Add Connection to Dot
    // While dot does not have any available connections, move one dot along (position++)    
    while(!hasAvailableCons(d->cts)){
      cpos = getNewPos(cpos, 1);
      d = getDot(cpos);
    }
    
    addConnection(*d, cplayer);
  }
  drawBoard();

  cout << boxes1 << " " << boxes2 << endl;
}
