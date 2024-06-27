#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    int leftSize; // 왼쪽 서브트리의 노드 개수
    struct Node* Left, * Right;
} Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->leftSize = 0;
    newNode->Left = NULL;
    newNode->Right = NULL;
    return newNode;
}

Node* Insert(Node* node, int data) {
    if (node == NULL) {
        return createNode(data);
    } else {
        if (data < node->data) {
            node->Left = Insert(node->Left, data);
            node->leftSize++; // 왼쪽 서브트리에 삽입할 때 leftSize 증가
        } else if (data > node->data) {
            node->Right = Insert(node->Right, data);
        }
        return node;
    }
}

Node* findKthSmallest(Node* node, int k) {
    if (node == NULL) {
        return NULL;
    }

    int leftSubtreeSize = node->leftSize;

    if (k < leftSubtreeSize) {
        return findKthSmallest(node->Left, k);
    } else if (k == leftSubtreeSize) {
        return node;
    } else {
        return findKthSmallest(node->Right, k - leftSubtreeSize - 1);
    }
}

Node* Delete(Node* node, int data) {
    if (node == NULL) return NULL;

    if (node->data == data) {
        Node* deleteNode = node;
        if (node->Left == NULL) {
            node = node->Right;
        } else if (node->Right == NULL) {
            node = node->Left;
        } else {
            Node* temp = node->Right;
            while (temp->Left != NULL) {
                temp = temp->Left;
            }
            node->data = temp->data;
            node->Right = Delete(node->Right, temp->data);
            return node;
        }
        free(deleteNode);
    } else {
        if (data < node->data) {
            node->Left = Delete(node->Left, data);
            node->leftSize--; // 왼쪽 서브트리에서 삭제할 때 leftSize 감소
        } else {
            node->Right = Delete(node->Right, data);
        }
    }
    return node;
}

Node* deleteKthSmallest(Node* root, int k) {
    Node* kthNode = findKthSmallest(root, k);
    if (kthNode != NULL) {
        root = Delete(root, kthNode->data);
    } else {
        printf("트리에 %d번째 작은 노드가 없습니다.\n", k + 1);
    }
    return root;
}

void inorder(Node* root) {
    if (root != NULL) {
        inorder(root->Left);
        printf("%d(%d) ", root->data, root->leftSize);
        inorder(root->Right);
    }
}

int main() {
    Node* root = NULL;
    root = Insert(root, 20);
    root = Insert(root, 10);
    root = Insert(root, 32);
    root = Insert(root, 4);
    root = Insert(root, 13);
    root = Insert(root, 25);
    root = Insert(root, 55);

    printf("Inorder traversal of the tree:\n");
    inorder(root);
    printf("\n");

    int k = 3; // 0부터 시작하여 4번째 작은 노드
    root = deleteKthSmallest(root, k);
    printf("\nAfter deleting %d-th smallest node:\n", k + 1);
    inorder(root);
    printf("\n");

    return 0;
}