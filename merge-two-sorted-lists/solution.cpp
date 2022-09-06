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
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        if (list1 == nullptr) return list2;
        if (list2 == nullptr) return list1;
        if (list1->val > list2->val) swap(list1, list2);
        auto ret = list1;
        while (list1->next) {
            if (list1->next->val > list2->val) {
                swap(list1->next, list2);
            }
            list1 = list1->next;
        }
        if (list2) {
            list1->next = list2;
        }
        return ret;
    }
};

int main() {
    // auto data = make_pair<ListNode*, ListNode*>(
    //     new ListNode(1, new ListNode(3, new ListNode(4))),
    //     new ListNode(1, new ListNode(2, new ListNode(4)))
    // );
    auto data = make_pair<ListNode*, ListNode*>(
        nullptr,
        nullptr
    );

    Solution s;
    auto l = s.mergeTwoLists(data.first, data.second);
    while (l) {
        cout << l->val << ", ";
        l = l->next;
    }
    cout << endl;
}