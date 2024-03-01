#include <iostream>
#include <deque>
using namespace std;
int main() {
    int n = 0;
    cin >> n;
    deque<pair<int, int>> dq;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        dq.push_back(make_pair(i + 1, temp));
    }
    int cur = 0;
    while (!dq.empty()) {
        cout << dq.front().first << ' ';
        cur = dq.front().second;
        dq.pop_front();
        if (dq.empty()) break;
        if (cur > 0) {
            for (int i = 0; i < cur - 1; i++) {
                dq.push_back(dq.front());
                dq.pop_front();
            }
        }
        else {
            for (int i = 0; i < (cur * -1); i++) {
                dq.push_front(dq.back());
                dq.pop_back();
            }
        }
    }
}