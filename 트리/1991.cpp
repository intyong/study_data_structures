#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
vector<pair<char, char>> tree(26);
void preorder(char temp) {
    if (temp != '.') {
        cout << temp;
        preorder(tree[temp - 'A'].first);
        preorder(tree[temp - 'A'].second);
    }
}
void inorder(char temp) {
    if (temp != '.') {
        inorder(tree[temp - 'A'].first);
        cout << temp;
        inorder(tree[temp - 'A'].second);
    }
}
void postorder(char temp) {
    if (temp != '.') {
        postorder(tree[temp - 'A'].first);
        postorder(tree[temp - 'A'].second);
        cout << temp;
    }
}
int main() {
    int n = 0;
    cin >> n;
    char value, left, right;
    for (int i = 0; i < n; i++) {
        cin >> value >> left >> right;
        tree[value - 'A'].first = left;
        tree[value - 'A'].second = right;
    }
    preorder('A');
    cout << endl;
    inorder('A');
    cout << endl;
    postorder('A');
}