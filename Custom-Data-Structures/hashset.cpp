#include <iostream>
#include <vector>
using namespace std;

// Node only needs 'key' and 'next' (no 'value' needed for a Set!)
struct Node {
    int key;
    Node* next;

    Node(int k) {
        key = k;
        next = nullptr;
    }
};

class MyHashSet {
private:
    int bucketCount;
    int numElements;
    vector<Node*> buckets;

    // Hash Function: Maps any integer key (including negative numbers) to [0, bucketCount - 1]
    int hashFunction(int key) {
        return ((key % bucketCount) + bucketCount) % bucketCount;
    }

    // Rehash: Doubles the bucket array and redistributes all existing nodes when load factor > 0.75
    void rehash() {
        int oldBucketCount = bucketCount;
        vector<Node*> oldBuckets = buckets;

        bucketCount *= 2;
        buckets.assign(bucketCount, nullptr);

        // resize(n, val) keeps your existing elements and only fills newly added slots with val,
        // whereas assign(n, val) wipes out the entire vector and overwrites every single slot with val.
        for (int i = 0; i < oldBucketCount; i++) {
            Node* curr = oldBuckets[i];
            while (curr != nullptr) {
                Node* nextNode = curr->next;
                int newIdx = hashFunction(curr->key);

                curr->next = buckets[newIdx];
                buckets[newIdx] = curr;

                curr = nextNode;
            }
        }
    }

public:
    // Constructor: Initializes an empty HashSet with 4 buckets
    MyHashSet() {
        bucketCount = 4;
        numElements = 0;
        buckets.resize(bucketCount, nullptr);
    }

    // Destructor: Frees all heap-allocated nodes when MyHashSet goes out of scope
    ~MyHashSet() {
        for (int i = 0; i < bucketCount; i++) {
            Node* curr = buckets[i];
            while (curr != nullptr) {
                Node* nextNode = curr->next;
                delete curr;
                curr = nextNode;
            }
            buckets[i] = nullptr;
        }
    }

    // 1. ADD: Inserts 'key' ONLY if it is not already in the set
    void add(int key) {
        int idx = hashFunction(key);
        Node* curr = buckets[idx];

        // Check if key already exists -> sets ignore duplicates
        while (curr != nullptr) {
            if (curr->key == key) {
                return; // Already exists, do nothing
            }
            curr = curr->next;
        }

        // Not found -> insert new node at the HEAD of the bucket
        Node* newNode = new Node(key);
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
        numElements++;

        // Double buckets if load factor > 0.75
        if ((double)numElements / bucketCount > 0.75) {
            rehash();
        }
    }

    // 2. CONTAINS: Returns true if 'key' exists in the set, false otherwise
    bool contains(int key) {
        int idx = hashFunction(key);
        Node* curr = buckets[idx];

        while (curr != nullptr) {
            if (curr->key == key) {
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    // 3. REMOVE: Deletes 'key' from the set if present
    void remove(int key) {
        int idx = hashFunction(key);
        Node* curr = buckets[idx];
        Node* prev = nullptr;

        while (curr != nullptr) {
            if (curr->key == key) {
                if (prev == nullptr) {
                    buckets[idx] = curr->next; // Removing head node
                } else {
                    prev->next = curr->next;   // Bypassing middle/tail node
                }
                delete curr;
                numElements--;
                return;
            }
            prev = curr;
            curr = curr->next;
        }
    }

    // 4. DISPLAY: Prints all buckets and their linked lists
    void display() {
        cout << "Buckets: " << bucketCount << " | Unique Elements: " << numElements << "\n";
        for (int i = 0; i < bucketCount; i++) {
            cout << "  Bucket " << i << ": ";
            Node* curr = buckets[i];
            while (curr != nullptr) {
                cout << "[" << curr->key << "] -> ";
                curr = curr->next;
            }
            cout << "NULL\n";
        }
    }
};

int main() {
    // 1. Constructor MyHashSet() runs here
    MyHashSet set;
    cout << "=== 1. Initial Empty Set ===\n";
    set.display();

    // 2. Calling add() (including duplicate test & negative key test)
    cout << "\n=== 2. Adding Elements (1, 5, 9, 1 [duplicate], -3) ===\n";
    set.add(1);
    set.add(5);
    set.add(9);
    set.add(1);   // Duplicate -> ignored
    // Note: 3 elements in 4 buckets -> load factor = 3/4 = 0.75 (no rehash yet)
    set.display();

    // 3. Triggering private rehash() automatically via add()
    cout << "\n=== 3. Adding 13 and -3 (Load factor > 0.75 -> triggers rehash() to 8 buckets) ===\n";
    set.add(13);  // 4th unique element -> 4/4 = 1.0 > 0.75 -> doubles buckets to 8!
    set.add(-3);  // Tests negative key handling in hashFunction()
    set.display();

    // 4. Calling contains() for both present and missing keys
    cout << "\n=== 4. Checking contains() ===\n";
    cout << "Contains 5?   " << (set.contains(5) ? "Yes" : "No") << "\n";
    cout << "Contains -3?  " << (set.contains(-3) ? "Yes" : "No") << "\n";
    cout << "Contains 99?  " << (set.contains(99) ? "Yes" : "No") << "\n";

    // 5. Calling remove() on head node, middle/tail node, and non-existent key
    cout << "\n=== 5. Removing Elements (5, 1, and non-existent 99) ===\n";
    set.remove(5);   // Removes existing element
    set.remove(1);   // Removes existing element
    set.remove(99);  // Key not found -> safely does nothing
    cout << "Contains 5 after remove? " << (set.contains(5) ? "Yes" : "No") << "\n";
    set.display();

    // 6. Destructor ~MyHashSet() runs automatically here to free all remaining heap memory
    return 0;
}
