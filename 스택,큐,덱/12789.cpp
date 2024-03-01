#include <iostream>
#include <vector>
#include <stack>
using namespace std;
int main() {
    int n = 0;
    int count = 1;
    vector<int> v;
    stack<int> s;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int temp = 0;
        cin >> temp;
        v.push_back(temp);
    }
    int i = 0;
    while (i != n) {
        if (v[i] == count) {
            i++;
            count++;
        }
        else if (!s.empty() && s.top() == count) {
            s.pop();
            count++;
        }
        else {
            s.push(v[i]);
            i++;
        }
    }
    while (!s.empty()) {
        if (s.top() == count) {
            s.pop();
            count++;
        }
        else {
            cout << "Sad";
            return 0;
        }
    }
    cout << "Nice";
}