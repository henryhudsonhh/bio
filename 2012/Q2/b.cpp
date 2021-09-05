// Scores 2/2 | 100%

#include <iostream>
#include <vector>
#include <algorithm>
#include <map>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define pb push_back

class Point{
  public:
    char straight, lCurve, rCurve, next;
    int type = 0;
    Point(char straight, char lCurve, char rCurve){
      this->straight = straight;
      this->lCurve = lCurve;
      this->rCurve = rCurve;
      this->next = lCurve;
    };
    void setFlipFlop() {
      this->type = 1;
    }
    Point() = default;
};

void updateFlipFlop(char point, map<char, Point>& map) {
  if(map[point].next == map[point].lCurve) map[point].next = map[point].rCurve;
  else map[point].next = map[point].lCurve;
}

void updateLazy(char point, map<char, Point>& map, char prev) {
  if(prev == map[point].rCurve) map[point].next = map[point].rCurve;
  else map[point].next = map[point].lCurve;
}

char getNext(vector<char> path, map<char, Point>& map) {
  char curr = path.back(), prev = path.end()[-2];
  char next;
  if(map[curr].straight != prev) {
    next = map[curr].straight;
    if(map[curr].type == 0) updateLazy(curr, map, prev);
  } else {
    next = map[curr].next;
    if(map[curr].type == 1) updateFlipFlop(curr, map);
  }
  return next;
}

map<char, Point> buildGraph(string flipflops) {
  map<char, Point> map;

  map['A'] = Point('D', 'E', 'F');
  map['B'] = Point('C', 'G', 'H');
  map['C'] = Point('B', 'I', 'J');
  map['D'] = Point('A', 'K', 'L');
  map['E'] = Point('A', 'M', 'N');
  map['F'] = Point('A', 'N', 'O');
  map['G'] = Point('B', 'O', 'P');
  map['H'] = Point('B', 'P', 'Q');
  map['I'] = Point('C', 'Q', 'R');
  map['J'] = Point('C', 'R', 'S');
  map['K'] = Point('D', 'S', 'T');
  map['L'] = Point('D', 'T', 'M');
  map['M'] = Point('U', 'L', 'E');
  map['N'] = Point('U', 'E', 'F');
  map['O'] = Point('V', 'F', 'G');
  map['P'] = Point('V', 'G', 'H');
  map['Q'] = Point('W', 'H', 'I');
  map['R'] = Point('W', 'I', 'J');
  map['S'] = Point('X', 'J', 'K');
  map['T'] = Point('X', 'K', 'L');
  map['U'] = Point('V', 'M', 'N');
  map['V'] = Point('U', 'O', 'P');
  map['W'] = Point('X', 'Q', 'R');
  map['X'] = Point('W', 'S', 'T');

  for(char c : flipflops) map[c].setFlipFlop();

  return map;
}

int main() {
  string flipflops, starts;
  cin >> flipflops;
  cin >> starts;

  map<char, Point> graph;

  graph = buildGraph(flipflops);

  vector<char> path;
  path.pb(starts[0]);
  path.pb(starts[1]);

  cout << starts[1] << " ";

  char next = ' ';

  while(next != 'P') {
    next = getNext(path, graph);
    path.pb(next);
    cout << next << " ";
  }
}
