#include <vector>
#include <string>
#include <iostream>
#include <unordered_set>
#include <queue>

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
     vector<double> averageOfLevelsV1(TreeNode* root) {
        std::vector<double> ret;
        ret.reserve(10000);
        int16_t cnt[10000];
        std::pair<int16_t, TreeNode*> stack[10000];
        int16_t sp = 0;
        int16_t sz = -1;
        int16_t c;
        stack[0] = std::make_pair(0, root);
        std::pair<int16_t, TreeNode*> current;
        while (sp >= 0) {
            current = stack[sp--];  
            if (sz < current.first) {
                ret.push_back(current.second->val);
                cnt[current.first] = 1;
                ++sz;
            } else {
                ret[current.first] += current.second->val;
                cnt[current.first] += 1;
            }
            if(current.second->left) {
                stack[++sp] = std::make_pair(current.first + 1, current.second->left);
            }  
            if(current.second->right) {
                stack[++sp] = std::make_pair(current.first + 1, current.second->right);
            }  
        }
        for (sp = 0; sp <= sz; ++sp) {
            ret[sp] = (double) ret[sp] / (double) (cnt[sp]);
        }
        return ret;
    }

    std::vector<double> retV2;
    std::vector<int16_t> cntV2;

    void avgV2(TreeNode* node, int16_t level) {
        if (node == nullptr) return;
        if (level >= retV2.size()) {
            retV2.push_back(node->val);
            cntV2.push_back(1);
        } else {
            retV2[level] += node->val;
            cntV2[level] += 1;
        }
        ++level;
        avgV2(node->left, level);
        avgV2(node->right, level);
    } 

    vector<double> averageOfLevelsV2(TreeNode* root) { //slower
        retV2.reserve(10000);
        cntV2.reserve(10000);
        avgV2(root, 0);
        for (int16_t i = 0; i < retV2.size(); ++i) {
            retV2[i] = (double) retV2[i] / (double) (cntV2[i]);
        }
        return retV2;
    }

    vector<double> averageOfLevels(TreeNode* root) { // from site
        std::vector<double> ret;
        queue<TreeNode*> q;
        q.push(root);
        double sum;
        int16_t cnt;
        int16_t i;
        while (!q.empty()) {
            sum = 0;
            cnt = q.size();
            i = cnt;
            while (i--) {
                root = q.front();
                sum += root->val;
                if (root->left) q.push(root->left);
                if (root->right) q.push(root->right);
                q.pop();
            }
            ret.push_back(sum / (double) cnt);
        }
        return ret;
    }
};

int main() {
    // auto data = new TreeNode(3, 
    //     new TreeNode(9,
    //         new TreeNode(15),
    //         new TreeNode(7)
    //     ),
    //     new TreeNode(20)
    // );

    auto data = new TreeNode(3, 
        new TreeNode(9),
        new TreeNode(20,
            new TreeNode(15),
            new TreeNode(7)
        )
    );

    Solution s;
    std::string str;
    auto v = s.averageOfLevels(data);
    for (auto piece : v) cout << piece << ", ";
    cout << endl;
}