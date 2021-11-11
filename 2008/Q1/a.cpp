// Scores 25/25 | 100%

#include <iostream>
#include <algorithm>
#include <numeric>
#include <map>
#include <cmath>
#include <queue>
using namespace std;

typedef map<char, char> mcc;

#define pb push_back

deque<int> first;
deque<int> second;

deque<int> firstBack;
deque<int> secondBack;

deque<int> reflect;
map<int, char> mappingTable = {{0, 'A'}, {1, 'B'}, {2, 'C'}, {3, 'D'}};

void rotate(deque<int>& rotor) {
  int topValue = rotor.front();
  rotor.pop_front();
  rotor.pb(topValue);
}

int validate(int val) {
  // Keeps the value within 0 - 3 inclusive
  int retVal = val;
  if(val < 0) retVal = 4 + val;
  if(val > 3) retVal = val - 4;
  return retVal;
}

int decrypt(int initialValue) {
  int returnValue = initialValue;
  
  int firstShift = first[returnValue];

  returnValue = validate(returnValue + firstShift);
  int secondShift = second[returnValue];
  returnValue = validate(returnValue + secondShift);

  return returnValue;
}

int main() {
  first.pb(0);
  first.pb(2);
  first.pb(-1);
  first.pb(-1);

  second.pb(0);
  second.pb(1);
  second.pb(-1);
  second.pb(0);

  reflect.pb(3);
  reflect.pb(1);
  reflect.pb(-1);
  reflect.pb(-3);

  string word;
  int done, rotorCounter;
  cin >> done;
  cin >> word;

  rotorCounter = done;

  for(int i = 0; i < done % 4; i++) rotate(first);

  for(int i = 0; i < (int)floor(done / 4) % 4; i++) rotate(second);

  for(int i = 0; i < word.length(); i++) {
    map<int, int> backwardsMappingTable;
    for(int j = 0; j < 4; j++) {      
      int decrypted = decrypt(j);
      backwardsMappingTable[decrypted] = j;
    }

    int x = decrypt((int)word[i] - 65);
    int z = reflect[x];
    char output = mappingTable[backwardsMappingTable[x + z]];
    
    cout << output;
    rotate(first);
    rotorCounter++;
    if(rotorCounter % 4 == 0) rotate(second);
  }
}
