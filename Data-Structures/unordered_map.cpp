#include <bits/stdc++.h> // in g++ compilers, this alone is sufficient

#include <iostream>
#include <unordered_map>
#include <string>
#include <chrono> // Required for custom anti-hack hash seed
using namespace std;

// Unordered map is Hash Table, O(1) Average

// Helper function to print std::unordered_map contents (arbitrary bucket order)
void printUnorderedMap(const string& label, const unordered_map<int, string>& um) {
    cout << label << " [Size: " << um.size() << ", Buckets: " << um.bucket_count() << "]: { ";
    for (const auto& [key, val] : um) {
        cout << "[" << key << ": " << val << "] ";
    }
    cout << "}\n";
}

// Custom Hash Functor (splitmix64) to prevent O(N^2) anti-hash blowups on online judges
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

// Custom Hash for std::pair<int, int> (STL does NOT provide a default hash for std::pair!)
struct PairHash {
    size_t operator()(const pair<int, int>& p) const {
        auto h1 = hash<int>{}(p.first);
        auto h2 = hash<int>{}(p.second);
        return h1 ^ (h2 + 0x9e3779b9 + (h1 << 6) + (h1 >> 2));
    }
};

int main() {
    // 1. INITIALIZATION & CAPACITY FUNCTIONS
    // std::unordered_map stores UNIQUE keys in NO particular order using a Hash Table.
    // Average time complexity is O(1); worst-case is O(N) on hash collisions.
    unordered_map<int, string> um;

    cout << "Is empty initially? " << (um.empty() ? "Yes" : "No") << "\n";
    cout << "Initial size: " << um.size() << "\n\n";


    // 2. HASH POLICY & BUCKET RESERVATION (Crucial for O(1) speed)
    cout << "--- Hash Policy ---\n";
    um.max_load_factor(0.75f); // Rehash if size / bucket_count > 0.75
    um.reserve(16);            // Pre-allocates buckets for at least 16 elements to prevent rehashing
    cout << "Bucket count after reserve(16): " << um.bucket_count() << "\n\n";


    // 3. MODIFIER FUNCTIONS (Inserting, Updating & Removing)
    cout << "--- Modifiers ---\n";

    // operator[]: Inserts or updates in O(1) average time
    um[10] = "Ten";
    um[30] = "Thirty";
    um[10] = "Ten Updated";

    // insert({key, val}): Inserts ONLY if key does not exist
    auto res = um.insert({20, "Twenty"});
    cout << "Inserted key 20? " << (res.second ? "Yes" : "No") << "\n";

    // insert_or_assign(key, val) [C++17] & try_emplace(key, val) [C++17]
    um.insert_or_assign(40, "Forty");
    um.try_emplace(50, "Fifty");
    printUnorderedMap("After insertions", um);

    // erase(key) & erase(iterator)
    um.erase(30);
    um.erase(um.begin());
    printUnorderedMap("After erasing key 30 and first element", um);

    // extract(key) [C++17]: Unlinks node to rename key without reallocating memory
    auto nodeHandle = um.extract(40);
    if (!nodeHandle.empty()) {
        nodeHandle.key() = 45;
        um.insert(move(nodeHandle));
    }
    printUnorderedMap("After C++17 extract & rename (40 -> 45)", um);


    // 4. LOOKUP FUNCTIONS (All O(1) average time)
    // Note: unordered_map does NOT have lower_bound() or upper_bound().
    cout << "\n--- Lookup Functions ---\n";
    um[10] = "Ten";
    um[20] = "Twenty";

    // at(key): Bounds-checked read (throws out_of_range if missing; does NOT insert)
    cout << "um.at(20): " << um.at(20) << "\n";

    // find(key): Best way to check existence AND read value in one single hash lookup
    auto it = um.find(45);
    if (it != um.end()) {
        cout << "Found 45 -> " << it->second << "\n";
    }

    // count(key) & equal_range(key)
    cout << "Count of 10: " << um.count(10) << ", Count of 99: " << um.count(99) << "\n";
    auto range = um.equal_range(20);
    if (range.first != range.second) {
        cout << "equal_range(20) -> " << range.first->second << "\n";
    }


    // 5. BUCKET INSPECTION & FORWARD ITERATORS
    // Note: Only forward iterators (++it) exist; rbegin()/rend() do NOT exist.
    cout << "\n--- Buckets & Forward Iterators ---\n";
    cout << "Load factor: " << um.load_factor() << "\n";
    size_t bIdx = um.bucket(20);
    cout << "Key 20 is in bucket " << bIdx << " (bucket size: " << um.bucket_size(bIdx) << ")\n";

    cout << "Forward traversal: ";
    for (auto fit = um.begin(); fit != um.end(); ++fit) {
        cout << "[" << fit->first << ":" << fit->second << "] ";
    }
    cout << "\n";


    // 6. MERGE, SWAP & CLEAR
    cout << "\n--- Merge, Swap & Clear ---\n";
    unordered_map<int, string> um2 = {{100, "Hundred"}, {20, "Duplicate Twenty"}};
    um.merge(um2); // Moves unique keys from um2 into um; duplicate 20 stays in um2
    printUnorderedMap("um after merge(um2)", um);
    um.swap(um2);
    um.clear();
    printUnorderedMap("um after swap and clear()", um);


    // 7. SAFE ANTI-HACK MAP & PAIR-KEYED MAP
    cout << "\n--- Custom Hash Maps ---\n";
    unordered_map<int, int, CustomHash> freqMap;
    freqMap.reserve(10);
    freqMap[42]++;
    cout << "freqMap[42]: " << freqMap[42] << "\n";

    // Using pair<int, int> as key (e.g., grid coordinates {row, col})
    unordered_map<pair<int, int>, string, PairHash> gridMap;
    gridMap[{2, 3}] = "Player";
    cout << "gridMap[{2, 3}]: " << gridMap[{2, 3}] << "\n";

    return 0;
}
