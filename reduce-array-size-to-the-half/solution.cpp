#include <vector>
#include <string>
#include <iostream>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution {
public:
    int minSetSizeV1(vector<int>& arr) {
        unordered_map<int32_t, int32_t> map;
        for (int val: arr) {
            auto it = map.find(val);
            if (it == map.end()) {
                map.emplace(val, 1);
            } else {
                ++it->second;
            }
        }
        int sz = map.size();
        std::vector<int32_t> counters(sz);
        const auto& end = map.end();
        size_t pos = 0;
        for (auto it = map.begin(); it != end; ++it) {
            counters[pos++] = it->second;
        }
        std::sort(counters.begin(), counters.end(), greater<int>());
        int32_t sum = arr.size() / 2;
        int ret = 0;
        while (ret < sz) {
            sum -= counters[ret++];
            if (sum <= 0) {
                break;
            }
        }
        return ret;
    }

    int minSetSizeV2(vector<int>& arr) { // best
        sort(arr.begin(), arr.end());
        std::vector<int32_t> counters;
        int prevInt = arr[0];
        int32_t counter = 1;
        int curInt;
        for (int i = 1; i < arr.size(); ++i) {
            curInt = arr[i];
            if (curInt == prevInt) {
                ++counter;
            } else {
                prevInt = curInt;
                counters.push_back(counter);
                counter = 1;
            }
        }
        counters.push_back(counter);
        std::sort(counters.begin(), counters.end(), greater<int>());
        int32_t sum = arr.size() / 2;
        int ret = 0;
        int sz = counters.size();
        while (ret < sz) {
            sum -= counters[ret++];
            if (sum <= 0) {
                break;
            }
        }
        return ret;
    }

    int32_t targetSum;
    greater<int32_t> comparer;
    int32_t lastSum = 0;
    int32_t smallestCounter = 0;

    std::vector<int32_t> counters;

    inline void addCounter(int32_t counter) {
        if (counter > smallestCounter) {
            auto it = std::lower_bound(counters.begin(), counters.end(), counter,  comparer);
            counters.emplace(it, counter);
            lastSum += counter;
            if (lastSum > targetSum) {
                //clean tail elements
                it = counters.end();
                --it;
                while (it != counters.begin()) {
                    if (lastSum - *it >= targetSum) {
                        lastSum -= *it;
                        --it;
                    } else {
                        break;
                    }
                }
                smallestCounter = *it;
                counters.erase(++it, counters.end());
            }
        }
    }
    int32_t counters2[100001]; 
    int counter2Size = 0;
    int32_t tempVal;

    inline void addCounter2(int32_t counter) {
        if (counter > smallestCounter) {
            int pos = lower_bound(counters2, counters2 + counter2Size, counter, comparer) - counters2;
            int i = counter2Size++; 
            while (i > pos) {
                counters2[i] = counters2[i-1];
                --i;
            }
            counters2[pos] = counter;
            lastSum += counter;
            if (lastSum > targetSum) {
                //clean tail elements
                i = counter2Size - 1;
                while (i > 0) {
                    tempVal = counters2[i];
                    if (lastSum - tempVal >= targetSum) {
                        lastSum -= tempVal;
                        --i;
                    } else {
                        break;
                    }
                }
                smallestCounter = counters2[i];
                counter2Size = i + 1;
            }
        }
    }
    
    int minSetSize(vector<int>& arr) { // slow :(
        targetSum = arr.size() / 2;
        sort(arr.begin(), arr.end());
        int prevInt = arr[0];
        int32_t counter = 1;
        int curInt;
        for (int i = 1; i < arr.size(); ++i) {
            curInt = arr[i];
            if (curInt == prevInt) {
                ++counter;
            } else {
                prevInt = curInt;
                addCounter2(counter);
                counter = 1;
            }
        }
        addCounter2(counter);
        
        return counter2Size;
    }
};

int main() {
    // vector<int> data = { 3,3,3,3,5,5,5,2,2,7 };
    // vector<int> data = { 7,7,7,7,7,7 };
    vector<int> data = { 1,9 };
    
    Solution s;
    cout << s.minSetSize(data) << endl;
}