#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int removeElement(vector<int>& nums, int val) {
        int len = 0;
        int cur;
        int8_t sz = nums.size();
        for(int8_t i = 0; i < sz; ++i) {
            cur = nums[i];
            if (cur != val) {
                nums[len++] = cur;
            }
        }
        return len;
    }
};

int main() {
    // pair<vector<int>, int> data = {{ 3, 2, 2, 3 }, 3};
    pair<vector<int>, int> data = {{ 0,1,2,2,3,0,4,2 }, 2};
    

    Solution s;
    int sz = s.removeElement(data.first, data.second);
    for(int8_t i = 0; i < sz; ++i)  cout << data.first[i] << ",";
    cout << endl;
}