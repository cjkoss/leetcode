#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<int> twoSumV1(vector<int>& nums, int target) {
        std::vector<int> ret(2);
        std::unordered_map<int32_t, int16_t> map;
        for (int16_t i = 0; i < nums.size(); ++i) {
            int32_t v = nums[i];
            const auto it = map.find(v);
            if (it != map.end()) {
                ret[0] = it->second;
                ret[1] = i;
                return ret;
            }
            map.emplace(target - v, i);
        }
        return ret;
    }

    vector<int> twoSumV2(vector<int>& nums, int target) { // slower, same memory
        int sz = nums.size();
        std::vector<int16_t> indices(sz);
        int begin = 0;
        for (begin = 0; begin < sz; ++begin) {
            indices[begin] = begin; 
        }
        sort(indices.begin(), indices.end(), [&nums](int16_t a, int16_t b) {
            return nums[a] < nums[b];
        });
        std::vector<int> ret(2);
        begin = 0;
        int end = sz - 1;
        int sum;
        int16_t indexBegin = indices[begin];
        int valueBegin = nums[indexBegin];
        int16_t indexEnd = indices[end];
        int valueEnd = nums[indexEnd];
        while (begin < end) {
            sum = valueBegin + valueEnd - target;
            if (sum == 0) {
                ret[0] = indexBegin;
                ret[1] = indexEnd;
                return ret;
            }
            if (sum < 0) {
                indexBegin = indices[++begin];
                valueBegin = nums[indexBegin];
            } else {
                indexEnd = indices[--end];
                valueEnd = nums[indexEnd];
            }
        }

        return ret;
    }
};

int main() {
    // auto data = make_pair<vector<int>, int>( { 2,7,11,15}, 9 );
    // auto data = make_pair<vector<int>, int>( { 3,3}, 6 );
    auto data = make_pair<vector<int>, int>( { 3,2,4}, 6 );

    Solution s;
    auto ret = s.twoSum(data.first, data.second);
    for (int pos : ret) {
        cout << pos << " ";
    }
    cout << endl;
}