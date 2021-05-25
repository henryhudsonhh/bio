// Score: 2/2 | 100%

#include <iostream>
#include <math.h>
using namespace std;

int main(){
  double debt = 10000, total = 0, ist, rep, paid, max;
  int counter = 0;

  cin >> ist >> rep;

  while(debt > 0){
    debt += ceil(debt * (ist / 100));
    paid = ceil(debt * (rep / 100));
    max = 5000 < paid ? paid : 5000;
    paid = debt < max ? debt : max;
    debt -= paid;
    total += paid;
    counter++;
  }
  cout << counter << endl;
}
