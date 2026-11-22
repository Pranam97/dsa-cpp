#include <iostream>
#include <vector>
using namespace std;

// Represents a single {key, value} entry in our HashMap (a node in a singly linked list)
struct Node {
    int key;
    int value;
    Node* next;

    Node(int k, int v) {
        key = k;
        value = v;
        next = nullptr;
    }
};

class MyHashMap {
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
    // Constructor: Initializes an empty HashMap with 4 buckets
    MyHashMap() {
        bucketCount = 4;
        numElements = 0;
        buckets.resize(bucketCount, nullptr);
    }

    // Destructor: Frees all heap-allocated nodes when MyHashMap goes out of scope
    ~MyHashMap() {
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

    // 1. PUT: Inserts a new {key, value} pair, or updates the value if key already exists
    void put(int key, int value) {
        int idx = hashFunction(key);
        Node* curr = buckets[idx];

        // Step A: Update value if key already exists
        while (curr != nullptr) {
            if (curr->key == key) {
                curr->value = value;
                return;
            }
            curr = curr->next;
        }

        // Step B: Insert new node at the HEAD of the bucket's linked list
        Node* newNode = new Node(key, value);
        newNode->next = buckets[idx];
        buckets[idx] = newNode;
        numElements++;

        // Step C: Double buckets if load factor > 0.75
        if ((double)numElements / bucketCount > 0.75) {
            rehash();
        }
    }

    // 2. GET: Returns the value mapped to 'key', or -1 if not found
    int get(int key) {
        int idx = hashFunction(key);
        Node* curr = buckets[idx];

        while (curr != nullptr) {
            if (curr->key == key) {
                return curr->value;
            }
            curr = curr->next;
        }
        return -1;
    }

    // 3. REMOVE: Deletes the node matching 'key' from the HashMap
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
        cout << "Buckets: " << bucketCount << " | Elements: " << numElements << "\n";
        for (int i = 0; i < bucketCount; i++) {
            cout << "  Bucket " << i << ": ";
            Node* curr = buckets[i];
            while (curr != nullptr) {
                cout << "[" << curr->key << " -> " << curr->value << "] -> ";
                curr = curr->next;
            }
            cout << "NULL\n";
        }
    }
};

int main() {
    // 1. Constructor MyHashMap() runs here
    MyHashMap map;
    cout << "=== 1. Initial Empty Map ===\n";
    map.display();

    // 2. Calling put() for new keys and updating an existing key
    cout << "\n=== 2. Inserting Keys (1, 5, 9) & Updating Key 5 ===\n";
    map.put(1, 100);
    map.put(5, 500);
    map.put(9, 900);
    map.put(5, 555); // Key 5 already exists -> updates value from 500 to 555
    // Note: 3 elements in 4 buckets -> load factor = 3/4 = 0.75 (no rehash yet)
    map.display();

    // 3. Triggering private rehash() automatically via put() & testing negative key
    cout << "\n=== 3. Inserting Key 13 & -3 (Triggers rehash() to 8 buckets) ===\n";
    map.put(13, 1300); // 4th element -> 4/4 = 1.0 > 0.75 -> doubles buckets to 8!
    map.put(-3, -300); // Tests negative key handling in hashFunction()
    map.display();

    // 4. Calling get() for existing, updated, negative, and missing keys
    cout << "\n=== 4. Calling get() ===\n";
    cout << "Get key 5 (updated): " << map.get(5) << "\n";   // 555
    cout << "Get key -3:          " << map.get(-3) << "\n";  // -300
    cout << "Get key 99 (missing):" << map.get(99) << "\n";  // -1

    // 5. Calling remove() on head node, middle/tail node, and non-existent key
    cout << "\n=== 5. Removing Keys (5, 1, and non-existent 99) ===\n";
    map.remove(5);   // Removes existing key
    map.remove(1);   // Removes existing key
    map.remove(99);  // Key not found -> safely does nothing
    cout << "Get key 5 after remove: " << map.get(5) << "\n"; // -1
    map.display();

    // 6. Destructor ~MyHashMap() runs automatically here to free all remaining nodes
    return 0;
}
