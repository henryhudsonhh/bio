#include <iostream>
#include <math.h>
using namespace std;

double run(double ist, double rep){
  double debt = 10000, total = 0, paid, max;

  while(debt > 0){
    debt += ceil(debt * (ist / 100));
    paid = ceil(debt * (rep / 100));
    max = 5000 < paid ? paid : 5000;
    paid = debt < max ? debt : max;
    debt -= paid;
    total += paid;
  }

  return total / 100;
}

int main(){
    double maxVals[2] = {0,0};
    double max = -1;
    for(int i = 0; i < 100; i++){ // 
        for(int j = 34; j < 100; j++){ // Trial and Error for the 34, no other smaller values worked
            double res = run(i,j);
            if(res > max && res != INFINITY){
                max = res;
                maxVals[0] = i;
                maxVals[1] = j;
            }
        }
    }
    cout << maxVals[0] << " " << maxVals[1] << endl;
}
