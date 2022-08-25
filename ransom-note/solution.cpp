#include <vector>
#include <string>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

class Solution {
public:
    bool canConstructV1(string ransomNote, string magazine) { // slow
        sort(ransomNote.begin(), ransomNote.end());
        sort(magazine.begin(), magazine.end());
        size_t sz1 = ransomNote.size();
        size_t sz2 = magazine.size();
        char c1, c2;
        size_t i1 = 0, i2 = 0;
        while (i1 < sz1 && i2 < sz2) {
            c1 = ransomNote[i1];
            c2 = magazine[i2];
            if (c1 < c2) {
                return false;
            }
            if (c1 == c2) {
                ++i1;
            }
            ++i2;
        }
        return i1 >= sz1;
    }
    bool canConstructV2(string ransomNote, string magazine) { // ok
        int32_t alphabet[26];
        memset(alphabet, 0, 26 * 4);
        for (char c : magazine) {
            ++alphabet[c - 'a'];
        }
        for (char c : ransomNote) {
            if (--alphabet[c - 'a'] < 0) return false;
        }
        return true;
    }
    bool canConstructV3(string ransomNote, string magazine) { // faster
        int32_t alphabet[26] = {0};
        for (char c : magazine) {
            ++alphabet[c - 'a'];
        }
        for (char c : ransomNote) {
            if (--alphabet[c - 'a'] < 0) return false;
        }
        return true;
    }
     bool canConstructV4(string ransomNote, string magazine) { // slower v3, faster v2
        int32_t alphabet[26] = {0};
        int32_t s1 = magazine.size();
        int32_t s2 = ransomNote.size();
        int32_t i;
        for (i = 0; i < s1; ++i) {
            ++alphabet[magazine[i] - 'a'];
        }
        for (i = 0; i < s2; ++i) {
            if (--alphabet[ransomNote[i] - 'a'] < 0) return false;
        }
        return true;
    }
    bool canConstructV5(string ransomNote, string magazine) { // slower v4
        int32_t alphabet[26] = {0};
        int32_t s1 = magazine.size();
        int32_t s2 = ransomNote.size();
        int32_t i;
        for (i = 0; i < s1; ++i) {
            ++alphabet[magazine[i] - 'a'];
        }
        for (i = 0; i < s2; ++i) {
            --alphabet[ransomNote[i] - 'a'];
        }
        for (i = 0; i < 26; ++i) {
            if (alphabet[i] < 0) return false;
        }
        return true;
    }
    bool canConstructV5(string ransomNote, string magazine) { // fastest
        int32_t alphabet[26] = {0};
        for (char c : magazine) {
            ++alphabet[c - 'a'];
        }
        for (char c : ransomNote) {
            --alphabet[c - 'a'];
        }
        for (int8_t i = 0; i < 26; ++i) {
            if (alphabet[i] < 0) return false;
        }
        return true;
    }
};

int main() {
    // pair<string, string> data = { "a", "b" };
    pair<string, string> data = { "aa", "ab" };
    // pair<string, string> data = { "aa", "aab" };

    Solution s;
    cout << s.canConstruct(data.first, data.second) << endl;
}