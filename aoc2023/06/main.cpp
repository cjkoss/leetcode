#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        cout << "not enough arguments" << endl; 
    }
    
    vector<int> times;
    vector<int> distances;

    int64_t time2 = 0;
    int64_t distance2 = 0;

    string line;
    ifstream file(argv[1]);
    if (file.is_open()) {
        while (getline(file, line)) {
            cout << line << "\n";
            bool readTimes = times.size() < 1;
            auto& v = readTimes ? times : distances; 
            int numBuffer = 0;
            int64_t numBuffer2 = 0;
            bool hasSpace = false;
            bool hasNum = false;
            for(int i = 0; i < line.size(); ++i) {
              char ch = line[i];
              if (!hasSpace) {
                  if (ch == ' ') hasSpace = true;
                  continue;
              }
              if (ch >= '0' && ch <= '9') {
                  hasNum = true;
                  numBuffer = numBuffer * 10 + ch - '0';
                  numBuffer2 = numBuffer2 * 10 + ch - '0';
                  cout << "b " << numBuffer << endl; 
                  continue;
              }
              if (hasNum) {
                  cout << "drop " << numBuffer << endl;
                  hasNum = false;
                  v.emplace_back(numBuffer);
                  numBuffer = 0;
              }
            }
            if (hasNum) v.emplace_back(numBuffer);
            if (readTimes) {
                time2 = numBuffer2;
            } else {
                distance2 = numBuffer2;
            }
        }
        file.close();

        cout << "times: ";
        for (int n : times) {
           cout << n << " ";
        }
        cout << "times2=" << time2 << endl;
        cout << "distances: ";
        for (int n : distances) {
            cout << n << " ";
        }
        cout << "distance2=" << distance2 << endl;

        int result1 = 1;
        for (int i = 0; i < times.size(); ++i) {
           int d = distances[i];
           int t = times[i];
           int overRecord = 0;
           for (int j = 1; j < t; ++j) {
              int myD = (t - j) * j;
              if (myD > d) {
                  ++overRecord;
              }
           }
           result1 *= overRecord;
        }

        int64_t overRecord = 0;
        for (int64_t j = 1; j < time2; ++j) {
            int64_t myD = (time2 - j) * j;
            if (myD > distance2) {
                ++overRecord;
            }
        }

        cout << "result: " << result1 << ", " << overRecord << endl;
    } else {
      cout << "could not open file " << argv[1] << "." << endl;
    }
    return 0;
}
