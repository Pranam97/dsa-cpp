#include <bits/stdc++.h> // in g++ compilers, this alone is sufficient

#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <chrono> // Required for custom anti-hack hash seed
using namespace std;

// Helper function to print unordered_set contents (order is arbitrary/unspecified)
void printUnorderedSet(const string& label, const unordered_set<int>& us) {
    cout << label << " [Size: " << us.size() << ", Buckets: " << us.bucket_count() << "]: { ";
    for (int x : us) {
        cout << x << " ";
    }
    cout << "}\n";
}

// Custom Hash Functor (splitmix64) to prevent O(N^2) anti-hash test blowups in competitive programming
struct CustomHash {
    static uint64_t splitmix64(uint64_t x) {
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

int main() {
    // 1. INITIALIZATION & CAPACITY FUNCTIONS
    // std::unordered_set stores UNIQUE elements in NO particular order using a Hash Table.
    // Average time complexity for insert, erase, find, and count is O(1); worst-case is O(N).
    unordered_set<int> us;

    // empty(): Checks if the unordered_set has 0 elements (returns true/false) in O(1) time
    cout << "Is empty initially? " << (us.empty() ? "Yes" : "No") << "\n";

    // size(): Returns the number of elements currently stored in O(1) time
    cout << "Initial size: " << us.size() << "\n";

    // max_size(): Returns the theoretical maximum number of elements the container can hold
    cout << "Max possible size: " << us.max_size() << "\n\n";


    // 2. HASH POLICY & BUCKET MANAGEMENT (Crucial for O(1) performance)
    cout << "--- Hash Policy & Buckets ---\n";

    // max_load_factor(): Returns/sets the max average elements per bucket before automatic rehashing (default ~1.0)
    cout << "Default max_load_factor: " << us.max_load_factor() << "\n";
    us.max_load_factor(0.75f); // Lowering load factor reduces collisions at the cost of extra memory

    // reserve(n): Pre-allocates enough buckets to hold at least n elements without rehashing
    // Always call reserve(N) when you know the approximate input size N to avoid costly rehashes!
    us.reserve(16);
    cout << "Bucket count after reserve(16): " << us.bucket_count() << "\n";

    // rehash(n): Explicitly sets the number of buckets to at least n and re-hashes all elements
    us.rehash(32);
    cout << "Bucket count after rehash(32): " << us.bucket_count() << "\n\n";


    // 3. MODIFIER FUNCTIONS (Inserting & Removing)
    cout << "--- Modifiers ---\n";

    // insert(val): Inserts val if not already present in O(1) average time.
    // Returns pair<iterator, bool> where .second is true if inserted, false if duplicate.
    us.insert(40);
    us.insert(10);
    us.insert(30);
    auto res = us.insert(10); // Duplicate 10 is ignored
    cout << "Was duplicate 10 inserted? " << (res.second ? "Yes" : "No") << "\n";

    // emplace(args...): Constructs element directly in-place in O(1) average time
    us.emplace(20);
    us.emplace(50);
    printUnorderedSet("After insert & emplace", us);

    // emplace_hint(pos, args...): Inserts element with an iterator hint (largely ignored in hash tables, O(1) avg)
    us.emplace_hint(us.begin(), 60);
    printUnorderedSet("After emplace_hint", us);

    // erase(val): Removes element by value in O(1) average time (returns 1 if removed, 0 if not found)
    size_t removed = us.erase(30);
    cout << "Removed 30? " << (removed ? "Yes" : "No") << "\n";

    // erase(pos): Removes element at a specific iterator position in O(1) average time
    auto firstIt = us.begin();
    us.erase(firstIt);
    printUnorderedSet("After erasing 30 and first iterator element", us);

    // extract(val) [C++17]: Unlinks a node from the hash table without freeing memory
    us.insert(70);
    auto nodeHandle = us.extract(70);
    if (!nodeHandle.empty()) {
        nodeHandle.value() = 75;
        us.insert(move(nodeHandle));
    }
    printUnorderedSet("After C++17 extract & re-insert (70 -> 75)", us);


    // 4. LOOKUP FUNCTIONS (All O(1) average time)
    // Note: Unlike std::set, unordered_set does NOT have lower_bound() or upper_bound().
    cout << "\n--- Lookup Functions ---\n";
    us.insert({10, 20, 40});
    printUnorderedSet("Current unordered_set", us);

    // find(val): Returns iterator to val if found, otherwise returns us.end()
    auto findIt = us.find(40);
    if (findIt != us.end()) {
        cout << "Found element: " << *findIt << "\n";
    } else {
        cout << "40 not found\n";
    }

    // count(val): Returns 1 if val exists, 0 otherwise
    cout << "Count of 20: " << us.count(20) << ", Count of 99: " << us.count(99) << "\n";

    // contains(val) [C++20]: Cleaner boolean check returning true if val exists, false otherwise
    // cout << "Contains 50? " << (us.contains(50) ? "Yes" : "No") << "\n";

    // equal_range(val): Returns pair<iterator, iterator> bounding elements equal to val (0 or 1 element)
    auto range = us.equal_range(40);
    if (range.first != range.second) {
        cout << "equal_range(40) found: " << *range.first << "\n";
    }


    // 5. BUCKET INSPECTION FUNCTIONS
    cout << "\n--- Bucket Inspection ---\n";

    // load_factor(): Current average number of elements per bucket (size() / bucket_count())
    cout << "Current load_factor: " << us.load_factor() << "\n";
    cout << "Max bucket count: " << us.max_bucket_count() << "\n";

    // bucket(val): Returns the 0-based bucket index where val is (or would be) stored
    size_t bIdx = us.bucket(40);
    cout << "Bucket index for value 40: " << bIdx << "\n";

    // bucket_size(n): Returns the number of elements colliding inside bucket index n
    cout << "Number of elements in bucket " << bIdx << ": " << us.bucket_size(bIdx) << "\n";

    // begin(n) & end(n): Iterate through all elements inside a specific bucket index n
    cout << "Elements inside bucket " << bIdx << ": ";
    for (auto bIt = us.begin(bIdx); bIt != us.end(bIdx); ++bIt) {
        cout << *bIt << " ";
    }
    cout << "\n";


    // 6. ITERATOR FUNCTIONS
    // Note: unordered_set only supports FORWARD iterators (++it).
    // Reverse iterators (rbegin, rend) and decrementing (--it) do NOT exist!
    cout << "\n--- Forward Iterators ---\n";

    // begin() & end(): Forward traversal in arbitrary bucket order
    cout << "Forward (begin to end): ";
    for (auto it = us.begin(); it != us.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    // cbegin() & cend(): Explicitly constant forward iterators
    cout << "Const forward (cbegin to cend): ";
    for (auto cit = us.cbegin(); cit != us.cend(); ++cit) {
        cout << *cit << " ";
    }
    cout << "\n";


    // 7. SWAPPING, MERGING & CLEARING
    cout << "\n--- Swap, Merge & Clear ---\n";
    unordered_set<int> us2 = {100, 200, 40}; // Shares 40 with us

    // merge(other) [C++17]: Splices unique elements from us2 into us without copying/allocating.
    // Duplicates (like 40) remain inside us2.
    us.merge(us2);
    printUnorderedSet("us after us.merge(us2)", us);
    printUnorderedSet("us2 after merge (duplicate 40 remains)", us2);

    // swap(other): Exchanges contents between two unordered_sets in O(1) time
    us.swap(us2);
    printUnorderedSet("us after swap with us2", us);

    // clear(): Removes all elements in O(N) time, leaving size() as 0
    us.clear();
    printUnorderedSet("us after clear()", us);


    // 8. SAFE ANTI-HACK UNORDERED_SET (Recommended for Competitive Programming)
    cout << "\n--- Safe Custom-Hashed Unordered Set ---\n";
    unordered_set<int, CustomHash> safeSet;
    safeSet.reserve(10);
    safeSet.insert({5, 15, 25, 35});
    cout << "safeSet size: " << safeSet.size() << ", contains 25: " << (safeSet.count(25) ? "Yes" : "No") << "\n";

    return 0;
}
