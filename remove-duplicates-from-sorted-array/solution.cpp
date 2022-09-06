#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int removeDuplicates(vector<int>& nums) {
        int pos = 0;
        int last = nums[0];
        int cur;
        for (int i = 1; i < nums.size(); ++i) {
            cur = nums[i];
            if (last != cur) {
                last = cur;
                nums[++pos] = last;
            }
        }
        return pos + 1;
    }
};

int main() {
    // vector<int> data = {1,1,2};
    vector<int> data = {0,0,1,1,1,2,2,3,3,4};

    Solution s;
    int k = s.removeDuplicates(data);
    for (int i = 0; i < k; ++i) cout << data[i] << ",";
    cout << endl;
}