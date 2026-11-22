#include <bits/stdc++.h> // in g++ compilers, this alone is sufficient

#include <iostream>
#include <map>
#include <string>
using namespace std;

// Map is Ordered Red-Black Tree : O(log N))

// Helper function to print std::map contents (always sorted by key ascending)
void printMap(const string& label, const map<int, string>& m) {
    cout << label << " [Size: " << m.size() << "]: { ";
    for (const auto& [key, val] : m) { // C++17 structured bindings
        cout << "[" << key << ": " << val << "] ";
    }
    cout << "}\n";
}

int main() {
    // 1. INITIALIZATION & CAPACITY FUNCTIONS
    // std::map stores UNIQUE keys sorted in ascending order (implemented as a Red-Black Tree).
    // Most operations (insert, erase, find, count, lower_bound, upper_bound, []) take O(log N) time.
    map<int, string> m;

    // empty(): Checks if the map has 0 key-value pairs in O(1) time
    cout << "Is empty initially? " << (m.empty() ? "Yes" : "No") << "\n";

    // size() & max_size()
    cout << "Initial size: " << m.size() << "\n";
    cout << "Max possible size: " << m.max_size() << "\n\n";


    // 2. MODIFIER FUNCTIONS (Inserting, Updating & Removing)
    cout << "--- Modifiers ---\n";

    // operator[]: Inserts {key, default_val} if key doesn't exist, or updates value if it does
    m[30] = "Thirty";
    m[10] = "Ten";
    m[10] = "Ten Updated"; // Overwrites existing value

    // insert({key, val}): Inserts ONLY if key does NOT already exist (ignores duplicates).
    // Returns pair<iterator, bool> where .second is true if inserted, false if key existed.
    auto res1 = m.insert({20, "Twenty"});
    auto res2 = m.insert({20, "Ignored"}); // Key 20 already exists -> ignored!
    cout << "Was duplicate key 20 inserted? " << (res2.second ? "Yes" : "No") << "\n";

    // insert_or_assign(key, val) [C++17]: Inserts if missing, or overwrites if present (cleaner than [])
    m.insert_or_assign(40, "Forty");
    m.insert_or_assign(40, "Forty Updated");

    // emplace(key, val): Constructs pair in-place without temporary copy
    m.emplace(50, "Fifty");

    // try_emplace(key, val) [C++17]: Like emplace, but avoids constructing 'val' if key already exists
    m.try_emplace(50, "Won't Construct");
    printMap("After insertions (auto-sorted by key)", m);

    // erase(key): Removes entry by key in O(log N) time (returns 1 if removed, 0 if not found)
    size_t removed = m.erase(30);
    cout << "Removed key 30? " << (removed ? "Yes" : "No") << "\n";

    // erase(pos): Removes entry at iterator position in amortized O(1) time
    m.erase(m.begin()); // Removes smallest key (10)
    printMap("After erasing key 30 and smallest key (10)", m);

    // extract(key) [C++17]: Unlinks node so you can modify the const key without reallocating!
    auto nodeHandle = m.extract(40);
    if (!nodeHandle.empty()) {
        nodeHandle.key() = 45; // Change key 40 -> 45 in place
        m.insert(move(nodeHandle));
    }
    printMap("After C++17 extract & key rename (40 -> 45)", m);


    // 3. ELEMENT ACCESS & LOOKUP FUNCTIONS (All O(log N) time)
    cout << "\n--- Lookup & Bounds ---\n";
    m[10] = "Ten";
    m[30] = "Thirty";
    printMap("Current map", m); // Keys: 10, 20, 30, 45, 50

    // at(key): Returns reference to value WITH bounds checking (throws std::out_of_range if missing)
    // Unlike m[key], at() will NEVER accidentally insert a new key!
    cout << "m.at(20): " << m.at(20) << "\n";

    // CAUTION with m[missing_key]: Reading m[99] silently inserts {99, ""} into the map!
    // Always use find() or count() before reading unless you want default insertion.

    // find(key): Returns iterator to {key, val} if found, or m.end() if missing
    auto findIt = m.find(30);
    if (findIt != m.end()) {
        cout << "Found key 30 -> value: " << findIt->second << "\n";
    }

    // count(key): Returns 1 if key exists, 0 otherwise
    cout << "Count of key 45: " << m.count(45) << ", Count of key 99: " << m.count(99) << "\n";

    // contains(key) [C++20]: Cleaner boolean check
    // cout << "Contains 50? " << (m.contains(50) ? "Yes" : "No") << "\n";

    // lower_bound(key): Iterator to FIRST entry with key >= target
    auto lb = m.lower_bound(25);
    if (lb != m.end()) cout << "lower_bound(25) [>= 25]: " << lb->first << " -> " << lb->second << "\n";

    // upper_bound(key): Iterator to FIRST entry with key > target
    auto ub = m.upper_bound(30);
    if (ub != m.end()) cout << "upper_bound(30) [> 30]: " << ub->first << " -> " << ub->second << "\n";

    // equal_range(key): Returns pair {lower_bound(key), upper_bound(key)}
    auto eq = m.equal_range(30);
    cout << "equal_range(30) -> lower: " << eq.first->first << ", upper: " << eq.second->first << "\n";


    // 4. ITERATOR FUNCTIONS (Bidirectional: ++it and --it work)
    cout << "\n--- Iterators ---\n";

    // Accessing smallest and largest keys in O(1) time
    if (!m.empty()) {
        cout << "Smallest key: " << m.begin()->first << ", Largest key: " << m.rbegin()->first << "\n";
    }

    // Forward traversal
    cout << "Forward: ";
    for (auto it = m.begin(); it != m.end(); ++it) {
        cout << "(" << it->first << "," << it->second << ") ";
    }
    cout << "\n";

    // Reverse traversal (rbegin to rend)
    cout << "Reverse: ";
    for (auto rit = m.rbegin(); rit != m.rend(); ++rit) {
        cout << "(" << rit->first << "," << rit->second << ") ";
    }
    cout << "\n";


    // 5. MERGE, SWAP, CLEAR & DESCENDING MAP
    cout << "\n--- Merge, Swap, Clear & Descending Map ---\n";
    map<int, string> m2 = {{100, "Hundred"}, {20, "Duplicate Twenty"}};

    // merge(other) [C++17]: Moves unique keys from m2 into m; duplicate key 20 stays in m2
    m.merge(m2);
    printMap("m after merge(m2)", m);
    printMap("m2 after merge (duplicate 20 left)", m2);

    // swap(other) in O(1) time & clear() in O(N) time
    m.swap(m2);
    m.clear();
    printMap("m after swap and clear()", m);

    // Descending std::map using greater<int>
    map<int, string, greater<int>> descMap = {{1, "One"}, {3, "Three"}, {2, "Two"}};
    cout << "Descending map: { ";
    for (const auto& [k, v] : descMap) cout << "[" << k << ": " << v << "] ";
    cout << "}\n";

    return 0;
}
