#include <stdio.h>
#include <stdlib.h>
typedef struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
} TreeNode;
int isBSTNode(TreeNode *root) {
    if (root == NULL) return 1;
    if ((root->left == NULL || root->val > root->left->val) && 
        (root->right == NULL || root->val < root->right->val))
        return 1;
    return 0;
}
int traversal(TreeNode* root) {
    if (root == NULL) return 1;
    if (isBSTNode(root) == 0) return 0;
    return traversal(root->left) && traversal(root->right);
}
int main() {
    TreeNode n1 = {1, NULL, NULL};
    TreeNode n4 = {4, NULL, NULL};
    TreeNode n3 = {3, &n1, &n4};

    int result = traversal(&n3);
    if (result) printf("It is BST\n");
    else printf("It isn't BST\n");

    return 0;
}