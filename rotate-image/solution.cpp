#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    void rotate(vector<vector<int>>& matrix) {
        int sz = matrix.size() - 1;
        int mid = sz / 2;
        int t;
        int i = mid;
        if ((sz & 1) == 0) {
            --mid;
        }
        for (;i >= 0; --i) {
            for (int j = mid; j >= 0; --j) {
                t = matrix[i][j]; // 0 1
                //0 1 <- 2 0 
                matrix[i][j] = matrix[sz - j][i];
                // 2 0 <- 3 2
                matrix[sz - j][i] = matrix[sz - i][sz - j];
                // 3 2 <- 1 3
                matrix[sz - i][sz - j] = matrix[j][sz - i];
                // 1 3 <- 0 1
                matrix[j][sz - i] = t;
            }
        }
    }
};

int main() {
    // vector<vector<int>> data = {{1,2,3},{4,5,6},{7,8,9}};
    vector<vector<int>> data = {{5,1,9,11},{2,4,8,10},{13,3,6,7},{15,14,12,16}};
    // 1 0 < 3 1 < 2 3 < 0 2 < 1 0

    Solution s;
    s.rotate(data);
    for (const auto& v: data) {
        for (int d : v) {
            cout << d << ",";
        }
        cout << endl;
    }
}