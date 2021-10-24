// Scores 4/4 | 100%
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef vector<int> vi;
typedef vector<vi> vvi;

#define COUNT(v, i) count(v.begin(), v.end(), i)
#define pb push_back

int main()
{
    int c = 0;
    int total = 0;
    vvi checked;
    for(int i = 11111; i < 99999; i++) {
        int n = i;
        vi v;
        for(int j = 0; j < 5; j++) {
            total += n % 10;
            v.pb(n % 10);
            n /= 10;
        }
        sort(v.begin(), v.end());
        if(total == 15 && !COUNT(checked, v) && !COUNT(v, 0)) {
            c++;
            checked.pb(v);
        }
        total = 0;
    }
    cout << c;
}
