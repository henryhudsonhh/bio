// Scores 24/24 | 100%

#include <iostream>
#include <vector>
using namespace std;

typedef vector<string> vs;

int main() {
  vs nums = {"ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};

  int c = 0;
  string word;
  cin >> word;

  for(int i = 0; i < nums.size(); i++) {
    int checkInd = 0;
    char checkLetter = nums[i][checkInd];
    for(int j = 0; j < word.length(); j++) {
      if(word[j] == checkLetter) {
        if(checkInd + 1 != nums[i].length()) {
          checkInd++;
          checkLetter = nums[i][checkInd];
        } else {
          cout << i + 1;
          c++;
          break;
        }
      }
    }
  }
  if(c == 0) cout << "NO";
}
