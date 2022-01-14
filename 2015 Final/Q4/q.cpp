#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <regex>
using namespace std;

int main() {
  string input = R"( Input here )";

  regex reg("[\\W\\d*]");

  input = regex_replace(input, reg, "");

  cout << input;

  vector<char> output;

  for(int i = 0; i < input.length(); i += 6) {
    string substring = input.substr(i, 6);
    
    int total = 0;
    for(int j = 0; j < 6; j++) {
      if((int)(substring[j]) < 97) {
        total += pow(2, 5 - j);
      }
    }
    if(total <= 26) {
      output.push_back((char)(total + 96));
    } else {
      output.push_back((char)(total + 64));
    }
  }
  for(char& c : output) {
    cout << c;
  }
} 
