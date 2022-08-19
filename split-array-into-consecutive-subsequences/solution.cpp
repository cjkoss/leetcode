#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

class SolutionV1 {
public:
    int16_t cnt[2001];
    size_t i = 1, j = 0, k = 0;

    inline bool check(size_t j) {
        int16_t cnt1 = 0;
        int16_t cnt2 = 0;
        int16_t cnt3 = 0;
        int16_t val;
        for (k = 0; k < j; ++k) {
            val = cnt[k];
            if (val < cnt1 + cnt2) return false;
            if (val > cnt1 + cnt2 + cnt3) {
                cnt3 += cnt2;
                cnt2 = cnt1;
                cnt1 = val - cnt2 - cnt3;
            } else {
                cnt3 = val - cnt1;
                cnt2 = cnt1;
                cnt1 = 0;
            }
        }
        return cnt3 > 0 && cnt2 <= 0 && cnt1 <= 0;
    }

    bool isPossible(vector<int>& nums) {
        // size_t i = 1, j = 0;
        int lastInt = nums[0], curInt;
        int16_t count = 1;
        for (;i < nums.size(); ++i) {
            curInt = nums[i];
            if (curInt != lastInt) {
                cnt[j++] = count;
                if (curInt != lastInt + 1) {
                    if (!check(j)) return false;
                    j = 0;
                }
                count = 1;
                lastInt = curInt;
            } else {
                ++count;
            }
        }
        cnt[j++] = count;
        
        return check(j);
    }
};

class SolutionV2 {
public:
    // int16_t cnt[2001];
    
    int16_t cnt1 = 0;
    int16_t cnt2 = 0;
    int16_t cnt3 = 0;
    int16_t val;

    inline void append(int16_t val) {
        if (val > cnt1 + cnt2 + cnt3) {
            cnt3 += cnt2;
            cnt2 = cnt1;
            cnt1 = val - cnt2 - cnt3;
        } else {
            cnt3 = val - cnt1;
            cnt2 = cnt1;
            cnt1 = 0;
        }
    }

    bool isPossible(vector<int>& nums) {
        size_t i = 1;
        int lastInt = nums[0], curInt;
        int16_t count = 1;
        for (;i < nums.size(); ++i) {
            curInt = nums[i];
            if (curInt != lastInt) {
                if (count < cnt1 + cnt2) return false;
                append(count);
                if (curInt != lastInt + 1) {
                    if (!(cnt3 > 0 && cnt2 <= 0 && cnt1 <= 0)) return false;
                    cnt3 = 0;
                    cnt2 = 0;
                    cnt1 = 0;
                }
                count = 1;
                lastInt = curInt;
            } else {
                ++count;
            }
        }
        if (count < cnt1 + cnt2) return false;
        append(count);
        return cnt3 > 0 && cnt2 <= 0 && cnt1 <= 0;
    }
};


int main() {
    // vector<int> data = { 1,2,3,3,4,5 };
    vector<int> data = { 1,2,3,3,4,4,5,5 };
    // vector<int> data = { 1,2,3,4,4,5 };
    // vector<int> data = { 1,2,3 };
    // vector<int> data = { 1,2,3,4,6,7,8,9,10,11 };

    SolutionV2 s;
    cout << s.isPossible(data) << endl;
}