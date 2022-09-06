#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<int> ret;
    int8_t n;
    int8_t k;

    void add(int v, int8_t last, int8_t l) {
        if (++l > n) {
            ret.push_back(v);
            return;
        }
        if (last + k < 10) {
            add(v * 10 + last + k, last + k, l);
        }
        if (k > 0 && last - k >= 0) {
            add(v * 10 + last - k, last - k, l);
        }
    }

    vector<int> numsSameConsecDiff(int n, int k) {
        for (int8_t start = 1; start < 10; ++start) {
            this->n = n;
            this->k = k;
            add(start, start, 1);
        }
        return ret;
    }
};

int main() {
    // pair<int, int> data = { 3, 7 };
    // pair<int, int> data = { 2, 1 };
    pair<int, int> data = { 2, 0 };

    Solution s;
    auto v = s.numsSameConsecDiff(data.first, data.second);
    for(int d: v) cout << d << ", ";
    cout << endl;
}