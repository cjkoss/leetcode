#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution {
public:
    string longestCommonPrefixV1(vector<string>& strs) { // 20:21
        std::vector<char> ret(200);
        size_t i;
        size_t j = 0;
        size_t cnt = strs.size();
        while (true) {
            const auto& s0 = strs[0];
            if (j + 1 > s0.size()) break;
            for (i = 1; i < cnt; ++i) {
                const auto& si = strs[i];
                if (j + 1 > si.size() || s0[j] != si[j]) break;
            }
            if (i < cnt) break;
            ret[j] = s0[j];
            ++j;
        }
        return std::string(&ret[0], j);
    }

    string longestCommonPrefixV2(vector<string>& strs) { // best
        const std::string& ret = strs[0];
        size_t sz = ret.size();
        for (int i = 1; i < strs.size(); ++i) sz = min(sz, strs[i].size());
        int j;
        for (int i = 1; i < strs.size(); ++i) {
            const std::string& s = strs[i];
            for (j = 0; j < sz; ++j) {
                if (ret[j] != s[j]) break;
            }
            sz = j;
        }
        return ret.substr(0, sz);
    }

    string longestCommonPrefix(vector<string>& strs) { 
        std::sort(strs.begin(), strs.end());
        const string first = strs[0];
        const string last = strs[strs.size() - 1];
        int i = 0;
        std::string ret;
        for (; i < first.size(); ++i) {
            if (first[i] != last[i]) {
                break;
            } else {
                ret.push_back(first[i]); // n * push_back is faster than substr??
            }
        }
        return ret; 
    }
};

int main() {
    vector<string> data = {"flower","flow","flight"};
    // vector<string> data = {"dog","racecar","car"};
    // vector<string> data = { "word" };
    // vector<string> data = { "" };

    Solution s;
    cout << "\"" << s.longestCommonPrefix(data) << "\"" << endl;
}