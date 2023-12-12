#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>
#include<bits/stdc++.h>

using namespace std;

struct Node {
    Node* left;
    Node* right;
    int pos;
    bool hasZ = false;
    int64_t foundSteps = 0;
};

Node* getNode(const std::string& str, int start, unordered_map<int, Node*>& nodeMap) {
    int pos = (str[start] - '0') * 10000 + (str[start+1] - '0') * 100 + str[start+2] - '0';
    // cout << pos << ' ';
    auto it = nodeMap.find(pos);
    if (it != nodeMap.end()) return it->second;
    Node* n = new Node();
    nodeMap.emplace(pos, n);
    n->pos = pos;
    return n;
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cout << "not enough arguments" << endl; 
    }

    string input;
    bool readNodes = false;
    unordered_map<int, Node*> nodeMap;
    int a = 'A' - '0';
    int z = 'Z' - '0';

    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "could not open file " << argv[1] << "." << endl;
        return 1;
    }
    string line;
    vector<Node*> starters;
    while (getline(file, line)) {
        if (line.size() <= 0) {
            readNodes = true;
            continue;
        }

        if (!readNodes) {
            input = line;
            continue;
        }
        
        auto node = getNode(line, 0, nodeMap);
        node->left = getNode(line, 7, nodeMap);
        node->right = getNode(line, 12, nodeMap);

        if (node->pos % 100 == a) {
            // cout << "pos " << node->pos << " ends with " << a << endl;
            starters.emplace_back(node);
        }
        node->hasZ = node->pos % 100 == z;
        // cout << ';' << endl;
    }
    file.close();

    int aaa = a * 10101;
    int zzz = z * 10101;

    // cout << "calc " << zzz << endl;

    Node* n = nodeMap[aaa];
    int input_len = input.size();
    char dir;
    int64_t steps1 = 0;
    int i = 0;
    while (n != nullptr && steps1 < 1000000) {
        if (n->pos == zzz) break;
        dir = input[i];
        n = dir == 'R' ? n->right : n->left;
        ++steps1;
        i = (i + 1) % input_len;
    }

    int64_t steps2 = 0;
    i = 0;
    int j;
    bool allZ, jZ;
    int starters_len = starters.size();
    if (starters_len > 0) {
        cout << "starters " << starters_len << endl;
        while (steps2 >= 0) { // TODO very slow
            dir = input[i];
            allZ = true;
            // cout << "step " << steps2; 
            for (int j = 0; j < starters_len; ++j) {
                n = starters[j];
                if (n->hasZ) { // looks incorrect
                    if (n->foundSteps <= 0) {
                        n->foundSteps = steps2;
                        cout << j << ": " << steps2 << endl;
                    }
                    // char c = n->foundSteps % steps2 == 0 ? ' ' : 'X';
                    // cout << j << ": " << steps2  << "vs" << n->foundSteps << "     " << c << endl;
                    continue;
                }
                allZ = allZ && n->hasZ;
                n = dir == 'R' ? n->right : n->left;
                starters[j] = n;
            }
            ++steps2;
            if (allZ) break;
            i = (i + 1) % input_len;
        }
        int64_t gcd, st;
        steps2 = starters[0]->foundSteps;
        for (j = 1; j < starters_len; ++j) {
            st = starters[j]->foundSteps;
            cout << steps2 << " and " << st;
            gcd = __gcd(steps2, st);
            steps2 = steps2 * st / gcd;
            cout << " -> " << steps2 << " with gcd=" << gcd << endl;
        }
    }

    cout << "result: " << steps1 << ", " << steps2 << endl;

    // cout << __gcd(12, 8) << "=gcd " << 12 * 8 / __gcd(12, 8) << "=lcm" << endl;
    return 0;
}
