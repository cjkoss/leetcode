#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <cstring>
#include <set>

using namespace std;

class Solution {
public:
    int maxSumSubmatrixV1(vector<vector<int>>& matrix, int k) {
        int8_t rows = matrix.size();
        int8_t cols = matrix[0].size();
        int32_t mx = numeric_limits<int32_t>::min(), last, rowSum;
        int32_t sum[5050];
        int16_t i;
        for (int8_t upRow = 0; upRow < rows; ++upRow) {
            memset(sum, 0, sizeof(sum));
            for (int8_t bottomRow = upRow; bottomRow < rows; ++bottomRow) {
                i = 0;
                for (int8_t left = 0; left < cols; ++left) {
                    rowSum = 0;
                    for (int8_t right = left; right < cols; ++right) {
                        rowSum += matrix[bottomRow][right];
                        last = (sum[i++] += rowSum);
                        if (last == k) return k;
                        if (last > mx && last < k) mx = last;
                    }
                }
            }
        }
        return mx;
    }

    int maxSumSubmatrix(vector<vector<int>>& matrix, int k) { 
        // from solution. 
        // looks like O(n * n * m * logm), but works for same time as V1 O(nnmm).
        // early return is efficient

        int8_t rows = matrix.size();
        int8_t cols = matrix[0].size();
        int32_t mx = numeric_limits<int32_t>::min(), prefix, last;
        int32_t colSums[cols];
        set<int32_t> accumulate;
        for (int8_t upRow = 0; upRow < rows; ++upRow) {
            memset(colSums, 0, sizeof(colSums));
            for (int8_t bottomRow = upRow; bottomRow < rows; ++bottomRow) {
                accumulate.clear();
                accumulate.insert(0);
                prefix = 0;
                for (int8_t col = 0; col < cols; ++col) {
                    prefix += (colSums[col] += matrix[bottomRow][col]);
                    const auto it = accumulate.lower_bound(prefix - k);
                    if (it != cend(accumulate)) {
                        last = prefix - *it;
                        if (last == k) return k;
                        if (last > mx && last < k) mx = last;
                    }
                    accumulate.insert(prefix);
                }
            }
        }
        return mx;
    }
};

int main() {
    // std::pair<vector<vector<int>>, int> data = {{{1,0,1},{0,-2,3}}, 2};
    // std::pair<vector<vector<int>>, int> data = {{{2,2,-1}}, 3};
    std::pair<vector<vector<int>>, int> data = {{{2, 4, -2}}, 3};

    int i = 0;
    for (int8_t left = 0; left < 100; ++left) {
        for (int8_t right = left; right < 100; ++right) {
            ++i;
        }
    }

    cout << i << endl;

    Solution s;
    cout << s.maxSumSubmatrix(data.first, data.second) << endl;
}