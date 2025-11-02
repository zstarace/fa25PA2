//
// Created by Manju Muralidharan on 10/19/25.
//
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include "heap.h"
using namespace std;

// Global arrays for node information
const int MAX_NODES = 64;
int weightArr[MAX_NODES];
int leftArr[MAX_NODES];
int rightArr[MAX_NODES];
char charArr[MAX_NODES];

// Function prototypes
void buildFrequencyTable(int freq[], const string& filename);
int createLeafNodes(int freq[]);
int buildEncodingTree(int nextFree);
void generateCodes(int root, string codes[]);
void encodeMessage(const string& filename, string codes[]);

int main() {
    int freq[26] = {0};

    // Read file and count letter frequencies
    buildFrequencyTable(freq, "input.txt");

    // Create leaf nodes for each character with nonzero frequency
    int nextFree = createLeafNodes(freq);

    // Build encoding tree using your heap
    int root = buildEncodingTree(nextFree);

    // Generate binary codes using an STL stack
    string codes[26];
    generateCodes(root, codes);

    // Encode the message and print output
    encodeMessage("input.txt", codes);

    return 0;
}

/*------------------------------------------------------
    Function Definitions (Students will complete logic)
  ------------------------------------------------------*/

// Read file and count frequencies
void buildFrequencyTable(int freq[], const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error: could not open " << filename << "\n";
        exit(1);
    }

    char ch;
    while (file.get(ch)) {
        // Convert uppercase to lowercase
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';

        // Count only lowercase letters
        if (ch >= 'a' && ch <= 'z')
            freq[ch - 'a']++;
    }
    file.close();

    cout << "Frequency table built successfully.\n";
}

// Create leaf nodes for each character
int createLeafNodes(int freq[]) {
    int nextFree = 0;
    for (int i = 0; i < 26; ++i) {
        if (freq[i] > 0) {
            //fill the parallel arrays for a new leaf node
            charArr[nextFree] = 'a' + i;
            weightArr[nextFree] = freq[i];
            leftArr[nextFree] = -1;
            rightArr[nextFree] = -1;
            nextFree++;
        }
    }
    cout << "Created " << nextFree << " leaf nodes.\n";
    return nextFree;
}

//Build the encoding tree using heap operations
int buildEncodingTree(int nextFree) {
    // Create a MinHeap object.
    MinHeap heap;

    // Push all leaf node indices into the heap.
    for (int i = 0; i <nextFree; i++) {
        heap.push (i, weightArr);
    }

    // 3. While the heap size is greater than 1:
    //    - Pop two smallest nodes
    //    - Create a new parent node with combined weight
    //    - Set left/right pointers
    //    - Push new parent index back into the heap
    while (heap.size>1) {
        int a = heap.pop(weightArr);
        int b = heap.pop(weightArr);

        // make a new internal parent node
        if (nextFree>= MAX_NODES) {
            cerr << "Error: too many nodes.\n";
            exit(1);
        }
        int p = nextFree ++;
        leftArr[p] = a;
        rightArr[p] = b;
        weightArr[p] = weightArr[a] + weightArr[b];
        charArr[p] = '\0';
        // Push the new parent back into the heap
        heap.push(p, weightArr);

    }

    // Return the index of the last remaining node (root)
    return heap.pop(weightArr);
}

// Use an STL stack to generate codes
void generateCodes(int root, string codes[]) {
    // Use stack<pair<int, string>> to simulate DFS traversal.
    // Left edge adds '0', right edge adds '1'.
    // Record code when a leaf node is reached.

    // checks to make sure tree isnt empty
    if (root<0) {
        return;
    }

    // Single-node tree
    if(leftArr[root] == -1 && rightArr[root] == -1) {
        if (charArr[root] >= 'a' && charArr[root] <= 'z')
            codes[charArr[root] - 'a'] = "0";
        return;

    }

    stack<pair<int, string>>  st;
    st.push({root, ""});

    while (!st.empty()) {
        auto[node, code] = st.top();
        st.pop();

        bool isLeaf = (leftArr[node] == -1 && rightArr[node] == -1);
        if (isLeaf) {
            // Store the final code for this character
            if (charArr[node] >= 'a' && charArr[node] <= 'z') {
                codes[charArr[node]- 'a'] = code.empty() ? "0" : code;
            }

        }
        else {
            // Push right first so left is processed later (LIFO)
            if (rightArr[node] != -1) {
                st.push({rightArr[node], code + "1"});
            }
            if (leftArr[node] != -1) {
                st.push({leftArr[node], code + "0"});
            }
        }
    }


}

// Print table and encoded message
void encodeMessage(const string& filename, string codes[]) {
    //print code table
    cout << "\nCharacter : Code\n";
    for (int i = 0; i < 26; ++i) {
        if (!codes[i].empty())
            cout << char('a' + i) << " : " << codes[i] << "\n";
    }

    cout << "\nEncoded message:\n";
    //Stream input again and print the codes for letters
    ifstream file(filename);
    char ch;
    while (file.get(ch)) {
        if (ch >= 'A' && ch <= 'Z')
            ch = ch - 'A' + 'a';
        if (ch >= 'a' && ch <= 'z')
            cout << codes[ch - 'a'];
    }
    cout << "\n";
    file.close();
}