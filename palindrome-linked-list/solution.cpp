#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

 struct ListNode {
      int val;
      ListNode *next;
      ListNode() : val(0), next(nullptr) {}
      ListNode(int x) : val(x), next(nullptr) {}
      ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    bool isPalindromeV1(ListNode* head) { // memory o1
        int cnt = 0;
        auto pos = head;
        while (pos != nullptr) {
            pos = pos->next;
            ++cnt;
        }

        int mid = cnt % 2;
        cnt = cnt / 2;

        ListNode* next;
        pos = head->next;
        head->next = nullptr;
        --cnt;
        while (cnt-- > 0) {
            next = pos->next;
            pos->next = head;
            head = pos;
            pos = next;
        }
        if (mid > 0 && pos != nullptr) pos = pos->next;
        while (pos != nullptr) {
            if (pos->val != head->val) return false;
            pos = pos->next;
            head = head->next;
        }
        return true;
    }

    bool isPalindrome(ListNode* head) { //slow
        int8_t vals[100000];
        int32_t cnt = 0;
        while (head != nullptr) {
            vals[cnt] = head->val;
            head = head->next;
            ++cnt;
        }
        int32_t mid = cnt / 2;
        for (int32_t i = 0; i < mid; ++i) {
            if (vals[i] != vals[cnt - 1 - i]) return false;
        }
        return true;
    }
};

int main() {
    // vector<int> data = { 1, 2, 2, 1 };
    vector<int> data = { 1, 2 };
    // vector<int> data = { 1, 2, 3 };
    // vector<int> data = { 1, 2, 1 };
    // vector<int> data = { 1 };

    ListNode* head = new ListNode(data[0]);
    ListNode* pos = head;
    for (int i = 1; i < data.size(); ++i) {
        pos->next = new ListNode(data[i]);
        pos = pos->next;
    }
    pos->next = nullptr;

    Solution s;
    cout << s.isPalindrome(head) << endl;
}