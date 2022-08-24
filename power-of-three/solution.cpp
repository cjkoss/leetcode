#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool isPowerOfThreeV1(int n) {
        std::unordered_set<int> set = {1,3,9,27,81,243,729,2187,6561,19683,59049,177147,531441,1594323,4782969,14348907,43046721,129140163,387420489,1162261467};
        return set.find(n) != set.end();
    }
    bool isPowerOfThreeV2(int n) { // better
        switch (n) {
        case 1:
        case 3:
        case 9:
        case 27:
        case 81:
        case 243:
        case 729:
        case 2187:
        case 6561:
        case 19683:
        case 59049:
        case 177147:
        case 531441:
        case 1594323:
        case 4782969:
        case 14348907:
        case 43046721:
        case 129140163:
        case 387420489:
        case 1162261467:
            return true;
        }
        return false;
    }
    bool isPowerOfThree(int n) { //correct not my answer
        return n > 0 && 1162261467 % n == 0;
    }
};

int main() {
    // int data = 27;
    // int data = 0;
    // int data = 9;
    int data = -6;

    // for (int64_t i = 3; i <= 2147483647L; i *= 3) {
    //     cout << i << ",";
    // }

    Solution s;
    cout << s.isPowerOfThree(data) << endl;
}