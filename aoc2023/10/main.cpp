#include <algorithm>
#include <bits/stdc++.h>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

struct Node {
  const Node *way1 = nullptr;
  const Node *way2 = nullptr;
  int pos = -1;
};

bool findNext(const std::vector<std::string> &lines, int &l, int &c, int &dir) {
  char ch = lines[l][c];
  switch (ch) {
  case '|': {
    if (dir == 0) {
      --l;
    } else {
      ++l;
    }
    return true;
  }
  case '-': {
    if (dir == 3) {
      ++c;
    } else {
      --c;
    }
    return true;
  }
  case 'F': {
    if (dir == 0) {
      dir = 3;
      ++c;
    } else {
      dir = 6;
      ++l;
    }
    return true;
  }
  case '7': {
    if (dir == 0) {
      dir = 9;
      --c;
    } else {
      dir = 6;
      ++l;
    }
    return true;
  }
  case 'L': {
    if (dir == 6) {
      dir = 3;
      ++c;
    } else {
      dir = 0;
      --l;
    }
    return true;
  }
  case 'J': {
    if (dir == 6) {
      dir = 9;
      --c;
    } else {
      dir = 0;
      --l;
    }
    return true;
  }
  }
  return false;
}

int main(int argc, char *argv[]) {
  const char *inputFile = "/repo/aoc2023/10/input";
  if (argc > 1) {
    inputFile = argv[1];
  }

  int64_t sum1 = 0;
  int64_t sum2 = 0;

  string input;
  ifstream file(inputFile);
  if (!file.is_open()) {
    cout << "could not open file " << argv[1] << "." << endl;
    return 1;
  }
  string line;
  std::vector<std::string> lines;
  int sl = -1;
  int sc = -1;
  int len = 0;
  int l = 0;
  int c;
  while (getline(file, line)) {
    if (len <= 0)
      len = line.size();
    lines.emplace_back(line);
    if (sl < 0) {
      for (c = 0; c < len; ++c) {
        if (line[c] == 'S') {
          sl = l;
          sc = c;
          break;
        }
      }
    }
    ++l;
  }
  file.close();

  char ch;
  int dir = -1; // 0 - top / 3 - right / 6 - down / 9 - right;
  int firstDir = 0;
  // find any route from S
  int count = 0;
  if (sl > 0) {
    c = sc;
    l = sl - 1;
    dir = 0;
    firstDir = 0;
    ch = lines[l][c];
    if (ch == '|' || ch == '7' || ch == 'F') {
      ++count;
    }
  }
  if (count <= 0 && sc < len) {
    c = sc + 1;
    l = sl;
    dir = 3;
    firstDir = 3;
    ch = lines[l][c];
    cout << "test 3 " << ch << endl;
    if (ch == '-' || ch == '7' || ch == 'J') {
      ++count;
    }
  }
  if (count <= 0 && sl < lines.size()) {
    c = sc;
    l = sl + 1;
    dir = 6;
    firstDir = 6;
    ch = lines[l][c];
    if (ch == '|' || ch == 'L' || ch == 'J') {
      ++count;
    }
  }
  if (count <= 0 && sc > 0) {
    c = sc - 1;
    l = sl;
    dir = 9;
    firstDir = 9;
    ch = lines[l][c];
    if (ch == '-' || ch == 'L' || ch == 'F') {
      ++count;
    }
  }
  cout << sl << ":" << sc << " " << firstDir << endl;

  std::unordered_set<int> routeNodes;
  routeNodes.emplace(sl * len + sc);

  // go through route
  int minC = len;
  int maxC = 0;
  int minL = lines.size();
  int maxL = 0;

  bool hasNext = true;
  while (hasNext) {
    routeNodes.emplace(l * len + c);
    if (minC > c)
      minC = c;
    if (maxC < c)
      maxC = c;
    if (minL > l)
      minL = l;
    if (maxL < l)
      maxL = l;
    hasNext = findNext(lines, l, c, dir);
    // cout << dir;
    ++count;
  }
  cout << endl;

  // get s char
  char sChar = '-';
  if ((firstDir == 0 && dir == 3) || (firstDir == 9 && dir == 6)) {
    sChar = 'J';
  } else if ((firstDir == 0 && dir == 0) || (firstDir == 6 && dir == 6)) {
    sChar = '|';
  } else if ((firstDir == 0 && dir == 9) || (firstDir == 3 && dir == 6)) {
    sChar = 'L';
  } else if ((firstDir == 6 && dir == 3) || (firstDir == 9 && dir == 0)) {
    sChar = '7';
  } else if ((firstDir == 6 && dir == 9) || (firstDir == 3 && dir == 0)) {
    sChar = 'F';
  }
  cout << "sChar = " << sChar << endl;

  // calc
  int lShift = 0;
  for (int l = minL; l <= maxL; ++l) {
    lShift = l * len;
    int myLines = 0;
    bool skipNextMy = false;
    bool fromTop = false;
    for (int c = minC; c <= maxC; ++c) {
      ch = lines[l][c];
      if (routeNodes.find(lShift + c) != routeNodes.end()) {
        if (ch == 'S')
          ch = sChar;

        if (ch == '|') {
          ++myLines;
          skipNextMy = false;
          continue;
        }
        if (ch == '-')
          continue;
        if (!skipNextMy) {
          // myLines = 1 - myLines;
          fromTop = ch == 'L';
          skipNextMy = true;
          continue;
        }

        skipNextMy = false;
        if ((fromTop && ch == '7') || (!fromTop && ch == 'J')) {
          ++myLines;
        }
        continue;
      }
      if (ch != 'Z') {
        // cout << "dot at " << l << ":" << c << " lines before = " << myLines
        // << endl;
        if (myLines % 2 == 1) {
          ++sum2;
        }
      }
    }
  }

  sum1 = count / 2;

  cout << "result: " << sum1 << ", " << sum2 << endl;

  return 0;
}
