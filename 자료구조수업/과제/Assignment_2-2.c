#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define ALPHABET_SIZE 26  // Assuming only lowercase English letters

typedef struct TrieNode {
    struct TrieNode* children[ALPHABET_SIZE];
    bool isEndOfWord;  // True if the node represents the end of a word
} TrieNode;

// Function to create a new trie node
TrieNode* createNode() {
    TrieNode* pNode = (TrieNode*)malloc(sizeof(TrieNode));
    if (pNode) {
        pNode->isEndOfWord = false;
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            pNode->children[i] = NULL;
        }
    }
    return pNode;
}

// Function to insert a word into the trie
void Insert(TrieNode* root, const char* key) {
    TrieNode* crawler = root;
    while (*key) {
        /* start */
        int index = *key - 'a';
        if (crawler->children[index] == NULL) {
            crawler->children[index] = createNode();
        }
        crawler = crawler->children[index];
        /* end */
        key++;
    }
    crawler->isEndOfWord = true;
}

// Function to search a word in the trie
bool search(TrieNode* root, const char* key) {
    TrieNode* crawler = root;
    while (*key) {
        /* start */
        int index = *key - 'a';
        if (crawler->children[index] == NULL) return false;
        crawler = crawler->children[index];
        /* end */
        key++;
    }
    return (crawler != NULL && crawler->isEndOfWord);
}
bool isEmpty(TrieNode* root) {
    for (int i = 0; i < ALPHABET_SIZE; i++)
        if (root->children[i])
            return false;
    return true;
}

bool deleteHelper(TrieNode* root, const char* key, int depth) {
    if (!root) {
        return false;
    }

    // If last character of key is being processed
    if (*key == '\0') {
        if (root->isEndOfWord) {
            root->isEndOfWord = false;
            // If root does not have any children (its not prefix of any other word)
            if (isEmpty(root)) {
                return true; // Delete the node
            }
            return false; // Do not delete the node
        }
    }
    else {
        int index = *key - 'a';
        if (root->children[index]) {
            /* start */
            if (deleteHelper(root->children[index], key + 1, depth + 1)) {
                root->children[index] = NULL;
                if (!root->isEndOfWord && isEmpty(root)) {
                    return true;
                }
            }
            /* end */
        }
    }
    return false;
}

void Delete(TrieNode* root, const char* key) {
    if (root != NULL && *key && search(root, key)) {
        deleteHelper(root, key, 0);
    }
    else {
        printf("Cannot delete '%s': Word not found in Trie.\n", key);
    }
}

void modify(TrieNode* root, const char* oldKey, const char* newKey) {
    Delete(root, oldKey);
    Insert(root, newKey);
}
void suggestions(TrieNode* root, const char* currentPrefix) {
    if (root->isEndOfWord) {
        printf("%s\n", currentPrefix);
    }

    if (isEmpty(root)) {
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        if (root->children[i]) {
            /* start */
            size_t len = strlen(currentPrefix);
            char* tempPrefix = (char*)malloc(len + 2);
            /* 실행 파일에서는 이 부분을 strcpy_s를 이용하여 구현하였습니다. 
               제가 mac os를 사용하여 vscode를 이용하여 과제를 하고 다른 컴퓨터를 이용하여 실행 파일을 만들었는데,
               vs에서 이 함수를 사용하려고 하니 문제가 발생하여 strcpy_s를 사용하였습니다.
               이 부분을 제외하고 다른 부분은 차이점이 없습니다. */
            strcpy(tempPrefix, currentPrefix);
            tempPrefix[len] = i + 'a';
            tempPrefix[len + 1] = '\0';
            
            suggestions(root->children[i], tempPrefix);

            free(tempPrefix);
            /* end */
        }
    }
}

void autoComplete(TrieNode* root, const char* prefix) {
    TrieNode* crawler = root;
    for (int i = 0; prefix[i] && crawler; i++) {
        int index = prefix[i] - 'a';
        crawler = crawler->children[index];
    }

    if (crawler) {
        suggestions(crawler, prefix);
    }
}
#include <stdio.h>
#include <stdlib.h>

int main() {
    TrieNode* root = createNode(); // Initialize the Trie

    // Predefined words to insert into the Trie
    char* wordsToInsert[] = { "apple", "app", "application", "apricot", "banana",
                             "berry", "blueberry", "blackberry", "banana", "balm", "ba"};
    int n = sizeof(wordsToInsert) / sizeof(wordsToInsert[0]);

    // Inserting words into the Trie
    for (int i = 0; i < n; i++) {
        Insert(root, wordsToInsert[i]);
        printf("Inserted: %s\n", wordsToInsert[i]);
    }
	/*
	Inserted: apple
	Inserted: app
	Inserted: application
	Inserted: apricot
	Inserted: banana
	Inserted: berry
	Inserted: blueberry
	Inserted: blackberry
	Inserted: banana
	Inserted: balm
	Inserted: ba
	*/
	
    // Perform an autocomplete on 'app'
    printf("Autocomplete results for 'app':\n");
    autoComplete(root, "app");
	/*
	Autocomplete results for 'app':
	app
	apple
	application
	*/
	
    // Perform an autocomplete on 'ba'
    printf("Autocomplete results for 'ba':\n");
    autoComplete(root, "ba");
	/*
	Autocomplete results for 'ba':
	ba
	balm
	banana
	*/
	
    // Modifying 'banana' to 'bandana'
    modify(root, "banana", "bandana");
    printf("Modified 'banana' to 'bandana'.\n");

    // Perform an autocomplete on 'ba'
    printf("Autocomplete results for 'ba':\n");
    autoComplete(root, "ba");
	/*
	Autocomplete results for 'ba':
	ba
	balm
	bandana
	*/
	
    // Cleaning up the Trie
    for (int i = 0; i < n; i++) {
        Delete(root, wordsToInsert[i]);
    }
    Delete(root, "bandana");  // Deleting the modified word
	/*
	Cannot delete 'banana': Word not found in Trie.
	Cannot delete 'banana': Word not found in Trie.
	*/


    return 0;
}
