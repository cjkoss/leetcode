#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int romanToInt(string s) {
        int ret = 0;
        char chars[7] = { 'I', 'V', 'X', 'L', 'C', 'D', 'M' };
        int numPos = 0;
        int lastOne = 0;
        char ch;
        int values[7] = { 1, 5, 10, 50, 100, 500, 1000 };
        int i = s.length() - 1;
        while (i >= 0) {
            ch = s[i];
            if (ch != chars[numPos]) {
                if (ch == chars[lastOne]) {
                    ret -= values[lastOne];
                    --i;
                    continue;
                }
                do {
                    ++numPos;
                    if (numPos % 2 == 1) lastOne = numPos - 1;
                }
                while (ch != chars[numPos]);
            }
            ret += values[numPos];
            --i;
        }

        return ret;
    }
};

int main() {
    // string data = "III";
    // string data = "LVIII";
    string data = "MCMXCIV";

    Solution s;
    cout << s.romanToInt(data) << endl;
}