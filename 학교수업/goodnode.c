#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode{
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
int traversal(TreeNode* root, int prevMax) {
    if (root == NULL) return 0;
    int GoodNode = 0;
    
    if (root->val >= prevMax) {
        GoodNode = 1;
        prevMax = root->val;
    }
    int left = traversal(root->left, prevMax);
    int right = traversal(root->right, prevMax);

    return left + right + GoodNode;
}
int goodNodes(TreeNode* root) {
    if (root == NULL) return 0;
    int maxVal = root->val;
    return traversal(root, maxVal);
}
int main() {
    TreeNode n1 = {1, NULL, NULL};
    TreeNode n4 = {4, NULL, NULL};
    TreeNode n3 = {3, &n1, &n4};

    int result = goodNodes(&n3);
    printf("Number of good nodes: %d\n", result);

    return 0;
}