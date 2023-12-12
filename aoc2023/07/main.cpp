#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <set>
#include <algorithm>

#define JOKER 1

using namespace std;

struct Cards {
    int nums[5];
    int val;
    int type;
};

bool cardLess(Cards c1, Cards c2)
{
    if (c1.type != c2.type) return c1.type < c2.type;
    int n1, n2;
    for (int i = 0; i < 5; ++i) {
        n1 = c1.nums[i];
        n2 = c2.nums[i];
        if (n1 != n2) return n1 < n2;
    }
    cout << "same" << endl;
    return false; 
}

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cout << "not enough arguments" << endl; 
    }

    std::unordered_map<char, int> cardMap;
#if JOKER
    cardMap.emplace('J', 1);
#endif
    cardMap.emplace('2', 2);
    cardMap.emplace('3', 3);
    cardMap.emplace('4', 4);
    cardMap.emplace('5', 5);
    cardMap.emplace('6', 6);
    cardMap.emplace('7', 7);
    cardMap.emplace('8', 8);
    cardMap.emplace('9', 9);
    cardMap.emplace('T', 10);
#if !JOKER    
    cardMap.emplace('J', 11);
#endif    
    cardMap.emplace('Q', 12);
    cardMap.emplace('K', 13);
    cardMap.emplace('A', 14);
    
    vector<Cards> cards;

    string line;
    ifstream file(argv[1]);
    if (!file.is_open()) {
        cout << "could not open file " << argv[1] << "." << endl;
        return 1;
    }
    unordered_map<int, int> lineCards;
    while (getline(file, line)) {
        // cout << line << "\n";
        Cards c;
        lineCards.clear();
        for (int i = 0; i < 5; ++i) {
            int v = cardMap[line[i]];
            c.nums[i] = v;
            lineCards[v]++;
        }
       
        int t1 = 0;
        int t2 = 0;
        int jokers = 0;
        for (const auto& pair : lineCards) {
            if (pair.first == 1) {
                jokers = pair.second;
                continue;
            }
            if (pair.second > t1) {
                t2 = t1;
                t1 = pair.second;
                continue;
            }
            if (pair.second > t2) {
                t2 = pair.second;
            }
        }

        t1 += jokers;
        c.type = t1 * 10;
        if (t2 >= 2) c.type += 5;

        c.val = 0;
        for (int i = 6; i < line.size(); ++i) {
            c.val = c.val * 10 + (line[i] - '0'); 
        }

        // cout << "val: " << c.val << " type: " << c.type << endl;
        cards.emplace_back(c);
    }
    file.close();

    sort(cards.begin(), cards.end(), cardLess);

    int64_t sum = 0; 
    for (int i = 0; i < cards.size(); ++i) {
        sum += (i+1) * cards[i].val;
        // cout << "l " << i+1 << "*" << cards[i].val << endl;
    }
    cout << "result: " << sum << endl;
    return 0;
}
