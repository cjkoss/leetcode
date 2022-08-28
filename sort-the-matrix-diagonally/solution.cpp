#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution {
public:
    vector<vector<int>> diagonalSort(vector<vector<int>>& mat) {
        int8_t rows = mat.size();
        int8_t cols = mat[0].size();
        int8_t maxTemp = min<int8_t>(cols, rows);
        int8_t temp[maxTemp];
        int8_t i, pos, mx;
        for (int8_t i = 0; i < cols; ++i) {
            // fill temp
            mx = min<int8_t>(maxTemp, cols - i);
            for (pos = 0; pos < mx; ++pos) {
                temp[pos] = mat[pos][i + pos];
            }
            // sort temp
            sort(temp, temp + pos);
            // fill mat
            --pos;
            for (; pos >= 0; --pos) {
                mat[pos][i + pos] = temp[pos];
            }
        }
        for (int8_t i = 1; i < rows; ++i) {
            // fill temp
            mx = min<int8_t>(maxTemp, rows - i);
            for (pos = 0; pos < mx; ++pos) {
                temp[pos] = mat[i + pos][pos];
            }
            // sort temp
            sort(temp, temp + pos);
            // fill mat
            --pos;
            for (; pos >= 0; --pos) {
                mat[i + pos][pos] = temp[pos];
            }
        }
        return mat;
    }
};

int main() {
    // vector<vector<int>> data = {{3,3,1,1},{2,2,1,2},{1,1,1,2}};
    vector<vector<int>> data = {{11,25,66,1,69,7},{23,55,17,45,15,52},{75,31,36,44,58,8},{22,27,33,25,68,4},{84,28,14,11,5,50}};

    Solution s;
    auto arr = s.diagonalSort(data);
    for(auto a : arr) {
        cout << "[";
        for (auto b : a) cout << b << ",";
        cout << "],";
    }
}