#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isValid(string s) {
        int pos = -1;
        for (int i = 0; i < s.length(); ++i) {
            switch(s[i]) {
                case '{':
                    s[++pos] = '}';
                    break;
                case '[':
                    s[++pos] = ']';
                    break;
                case '(':
                    s[++pos] = ')';
                    break;
                case '}':
                case ']':
                case ')':
                    if (pos < 0 || s[pos--] != s[i]) {
                        return false;
                    }
                    break;
            }
        }
        return pos == -1;
    }
};

int main() {
    // string data = "()";
    // string data = "()[]{}";
    string data = "(]";

    Solution s;
    cout << s.isValid(data) << endl;
}