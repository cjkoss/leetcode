#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int16_t rows = grid.size();
        int16_t cols = grid[0].size();
        vector<int16_t> islands;
        vector<int16_t> last(cols, -1);
        int16_t left; 
        int16_t top;
        int16_t val;
        for (int16_t i = 0; i < rows; ++i) {
            for (int16_t j = 0; j < cols; ++j) {
                if (grid[i][j] == '0') {
                    last[j] = -1;
                } else {
                    left = j <= 0 ? -1 : last[j - 1];
                    top = last[j];
                    if (top == -1) {
                        if (left == -1) {
                            left = islands.size();
                            islands.push_back(left);
                        } 
                        last[j] = left;
                    } else {
                        last[j] = top;
                        if (left != -1) {
                            while (islands[left] != left) {
                                left = islands[left];
                            }
                            while (islands[top] != top) {
                                top = islands[top];
                            }
                            islands[left] = top;
                        }
                    }
                }
            }
        }

        rows = 0;
        for (cols = 0; cols < islands.size(); ++cols) {
            if (islands[cols] == cols) ++rows;
        }
        return rows;
}
};

int main() {
    // vector<vector<char>> data = {
    //     {'1','1','1','1','0'},
    //     {'1','1','0','1','0'},
    //     {'1','1','0','0','0'},
    //     {'0','0','0','0','0'}
    // };

    // vector<vector<char>> data = {
    //     {'1','1','0','0','0'},
    //     {'1','1','0','0','0'},
    //     {'0','0','1','0','0'},
    //     {'0','0','0','1','1'}
    // };

    vector<vector<char>> data = {
        {'1','1','1','1','1','0','1','1','1','1'},
        {'1','0','1','0','1','1','1','1','1','1'},
        {'0','1','1','1','0','1','1','1','1','1'},
        {'1','1','0','1','1','0','0','0','0','1'},
        {'1','0','1','0','1','0','0','1','0','1'},
        {'1','0','0','1','1','1','0','1','0','0'},
        {'0','0','1','0','0','1','1','1','1','0'},
        {'1','0','1','1','1','0','0','1','1','1'},
        {'1','1','1','1','1','1','1','1','0','1'},
        {'1','0','1','1','1','1','1','1','1','0'}
    };

    Solution s;
    cout << s.numIslands(data) << endl;
}