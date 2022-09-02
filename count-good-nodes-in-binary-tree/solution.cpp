#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>

using namespace std;

 struct TreeNode {
      int val;
      TreeNode *left;
      TreeNode *right;
      TreeNode() : val(0), left(nullptr), right(nullptr) {}
      TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 };
 
class Solution {
public:
    int goodNodesV1(TreeNode* root) { //slow
        return 1 + goodNodesBase(root->left, root->val) + goodNodesBase(root->right, root->val);
    }

    int goodNodesBase(TreeNode* root, int parentMax) {
        if (root == nullptr) return 0;
        int ret = 0;
        if (root->val >= parentMax) {
            ++ret;
            parentMax = root->val;
        }
        return ret + goodNodesBase(root->left, parentMax) + goodNodesBase(root->right, parentMax);
    }

    int goodNodes(TreeNode* root) { //same speed
        TreeNode* stack[100000]; // not balanced :(
        TreeNode* current;
        int8_t sp = 0;
        stack[0] = root;
        int ret = 1;
        while (sp >= 0) {
            current = stack[sp--];
            if (current->left) {
                if (current->left->val >= current->val) {
                    ret++;
                } else {
                    current->left->val = current->val;
                }
                stack[++sp] = current->left;
            }
            if (current->right) {
                if (current->right->val >= current->val) {
                    ret++;
                } else {
                    current->right->val = current->val;
                }
                stack[++sp] = current->right;
            }
        }
        return ret;
    }
};

int main() {
    auto data = new TreeNode(3, 
            new TreeNode(1, new TreeNode(3), nullptr),
            new TreeNode(4, new TreeNode(1), new TreeNode(5))
        );

    Solution s;
    cout << s.goodNodes(data) << endl;
}