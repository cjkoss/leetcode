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
    string s;
    //stringstream s; //slower

    void treestr(TreeNode* node) {
        s += std::to_string(node->val);
        if (node->left == nullptr && node->right == nullptr) return;
        s += "(";
        if (node->left != nullptr) treestr(node->left);
        s += ")";
        if (node->right != nullptr) {
            s += "(";
            treestr(node->right);
            s += ")";
        }
    }
    string tree2str(TreeNode* root) {
        treestr(root);
        return s;
    }
};

int main() {
    auto data = new TreeNode(1, 
        new TreeNode(2, new TreeNode(4), nullptr),
        new TreeNode(3)
    );
    // auto data = new TreeNode(1, 
    //     new TreeNode(2, nullptr, new TreeNode(4)),
    //     new TreeNode(3)
    // );

    Solution s;
    cout << s.tree2str(data) << endl;
}