#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <map>
#include <set>
#include <algorithm>
#include <unordered_set>

using namespace std;

class Solution {
public:
    bool reorderedPowerOf2(int n) {
        std::unordered_set<int32_t> vals = {1,2,4,8,32,61,64,521,652,821,4210,8420,9640,9821,66553,86431,87632,644221,732110,885422,8765410,8888630,9444310,9752210,55443332,77766211,88766410,866554432,877432211,987653210};
        
        int8_t vv[9];
        int8_t sz = 0;
        for (; n > 0; n /= 10) {
            vv[sz++] = n % 10;
        }
        sort(vv, vv + sz);
        int32_t sorted = 0;
        for (n = sz - 1; n >=0; --n) {
            sorted = sorted * 10 + vv[n];
        }

        return vals.find(sorted) != vals.end();
    }
};

int main() {
    // int data = 1;
    // int data = 10;
    int data = 1124;
    std::vector<vector<int8_t>> pows1;
    std::map<int8_t, vector<vector<int8_t>>> pows2;
    std::set<int32_t> st;
    for (int32_t i = 1; i < 1000000000; i *= 2) {
        vector<int8_t> v;
        for (int j = i; j > 0; j = j / 10) {
            v.push_back((j % 10));
        }
        sort(v.begin(), v.end(), greater<int8_t>());
        pows1.push_back(v);
        pows2[v.size()].emplace_back(v.begin(), v.end());

        int32_t val = 0;
        for (int8_t i: v) { 
            val = val * 10 + i;
        }
        st.emplace(val);
    }
    for (int32_t v : st) {
        cout << v << ",";
    }
    cout << endl;
    // for (const auto& pair: pows2) {
    //     cout << "{" << (int) pair.first << ",{" << endl;
    //     for (const auto& v: pair.second) {
    //         cout << "  {";
    //         for (const auto& d: v) {
    //             cout << (int) d << ",";
    //         }
    //         cout << "}," << endl;
    //     }
    //     cout << "}}," << endl;
    // }
    // cout << endl;


    Solution s;
    cout << s.reorderedPowerOf2(data) << endl;
}