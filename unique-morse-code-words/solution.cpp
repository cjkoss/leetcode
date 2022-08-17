#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

static string alphabet[26] = { ".-","-...","-.-.","-..",".","..-.","--.","....","..",".---","-.-",".-..","--","-.","---",".--.","--.-",".-.","...","-","..-","...-",".--","-..-","-.--","--.." };
static int8_t alphabet_bin[26] = { 10,68,84,35,1,20,51,4,2,60,43,36,26,18,59,52,108,19,3,9,11,12,27,76,92,100 };

class Solution {
public:
    int uniqueMorseRepresentations(vector<string>& words) {
        int count = 0;
        unordered_set<int64_t> set;
        size_t i;
        int64_t value;
        int8_t ch;
        for (const string& word: words) {
            value = 0;
            for (i = 0; i < word.length(); ++i) {
                ch = alphabet_bin[word[i] - 'a'];
                value <<= (ch & 7);
                value += (ch >> 3);
            }
            if (set.emplace(value).second) count++;
        }
        return count;
    }
};

int main() {
    vector<string> data1 = { "gin","zen","gig","msg" };
    vector<string> data2 = { "a" };

    for (int i = 0; i < 26; ++i) {
        int v = 0;
        string ch = alphabet[i];
        for (int j = 0; j < ch.length(); ++j) {
            if (ch[j] == '-') v |= 1;
            v <<= 1;
        }
        v <<= 2;
        v += ch.length();
        // cout << v << " = " << (v >> 3) << " shift " << (v & 7) << endl;
        cout << v << ",";
    }
    cout << endl;

    Solution s;
    cout << s.uniqueMorseRepresentations(data1) << endl;
}
