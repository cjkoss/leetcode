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

std::pair<int64_t, int64_t> getNextForLine(const std::string &line) {
  int lineSize = line.size();
  int bufSize = 0;
  int buf1[lineSize];
  { // read strung numbers
    bool readNum = false;
    int bufNum = 0;
    bool negative = false;
    char ch;
    for (int i = 0; i <= lineSize; ++i) {
      ch = i == lineSize ? ' ' : line[i];
      if (ch >= '0' && ch <= '9') {
        bufNum = bufNum * 10 + (ch - '0');
        readNum = true;
        continue;
      }
      if (ch == '-') {
        negative = true;
        continue;
      }
      if (readNum) {
        if (negative) {
          bufNum *= -1;
        }
        buf1[bufSize++] = bufNum;
        bufNum = 0;
        negative = false;
        readNum = false;
      }
    }
  }
  int buf2[bufSize - 1];
  int lastNums[bufSize];
  int firstNums[bufSize];
  int *source, *dest;
  int last;
  bool allZero = false;
  int diff, s;
  int k = 0;
  for (k = 0; !allZero && k < bufSize; ++k) {
    allZero = true;
    source = (k & 1) == 0 ? buf1 : buf2;
    dest = (k & 1) == 0 ? buf2 : buf1;
    last = *source;
    firstNums[k] = last;
    cout << ((k & 1) == 0) << ": " << last << " ";
    for (int i = 0; i < bufSize - 1 - k; ++i) {
      s = source[i + 1];
      cout << s << " ";
      diff = s - last;
      dest[i] = diff;
      last = s;
      if (allZero && diff != 0)
        allZero = false;
    }
    lastNums[k] = last;
    cout << endl;
  }
  --k;
  cout << "k=" << k << endl;
  std::pair<int64_t, int64_t> result = std::make_pair(0, 0);
  for (; k >= 0; --k) {
    result.first += lastNums[k];
    result.second = firstNums[k] - result.second;
    cout << k << ": "
         << "+" << lastNums[k] << "=" << result.first << " " << firstNums[k]
         << "- =" << result.second << endl;
  }
  cout << endl;
  cout << "row next: " << result.first << " " << result.second << endl;
  return result;
}

int main(int argc, char *argv[]) {
  const char *inputFile = "/repo/aoc2023/09/input";
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
  while (getline(file, line)) {
    auto pair = getNextForLine(line);
    sum1 += pair.first;
    sum2 += pair.second;
  }
  file.close();

  cout << "result: " << sum1 << ", " << sum2 << endl;

  return 0;
}
