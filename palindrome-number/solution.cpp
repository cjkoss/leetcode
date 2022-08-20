#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isPalindromeV1(int x) { // 23:35
        if (x == 0) return true;
        int y = 0, mod = x % 10;
        if (mod == 0) return false;
        while (x > 0) {
            x = x / 10;
            if (y == x) return true;
            y = y * 10 + mod;
            if (y >= x) return y == x;
            mod = x % 10;
        }
        return false;
    }
};

int main() {
    // int data = 121;
    // int data = -121;
    // int data = 10;
    // int data = 101010;
    int data = 11;

    Solution s;
    cout << s.isPalindrome(data) << endl;
}