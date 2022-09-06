#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights) {
        return heights;
    }
};

int main() {
    vector<vector<int>> data = {{1,2,2,3,5},{3,2,3,4,4},{2,4,5,3,1},{6,7,1,4,5},{5,1,1,2,4}};

    Solution s;
    auto v = s.pacificAtlantic(data);
    for(const auto& v2 : v) {
        for (int d: v2) cout << d << ",";
        cout << endl;
    }
}