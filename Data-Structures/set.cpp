#include <bits/stdc++.h> // in g++ compilers, this alone is sufficient

#include <iostream>
#include <set>
#include <vector>
#include <string>
#include <algorithm> // Required for set_union, set_intersection, set_difference, set_symmetric_difference
#include <iterator>  // Required for inserter
using namespace std;

// Helper function to print set contents (ascending)
void printSet(const string& label, const set<int>& s) {
    cout << label << " [Size: " << s.size() << "]: { ";
    for (int x : s) {
        cout << x << " ";
    }
    cout << "}\n";
}

// Helper function to print descending set contents
void printDescSet(const string& label, const set<int, greater<int>>& s) {
    cout << label << " [Size: " << s.size() << "]: { ";
    for (int x : s) {
        cout << x << " ";
    }
    cout << "}\n";
}

int main() {
    // 1. INITIALIZATION & CAPACITY FUNCTIONS
    // std::set stores UNIQUE elements in sorted order (implemented as a Red-Black Tree).
    // Most operations (insert, erase, find, count, lower_bound, upper_bound) take O(log N) time.
    set<int> s;

    // empty(): Checks if the set has 0 elements (returns true/false) in O(1) time
    cout << "Is empty initially? " << (s.empty() ? "Yes" : "No") << "\n";

    // size(): Returns the number of elements currently in the set in O(1) time
    cout << "Initial size: " << s.size() << "\n";

    // max_size(): Returns the theoretical maximum number of elements the set can hold
    cout << "Max possible size: " << s.max_size() << "\n\n";


    // 2. MODIFIER FUNCTIONS (Inserting & Removing)
    // insert(val): Inserts val if not already present in O(log N) time.
    // Returns a pair<iterator, bool> where .second is true if inserted, false if duplicate.
    s.insert(40);
    s.insert(10);
    s.insert(30);
    auto res = s.insert(10); // Duplicate 10 is ignored
    cout << "Was duplicate 10 inserted? " << (res.second ? "Yes" : "No") << "\n";

    // emplace(args...): Constructs element directly in-place in O(log N) time (avoids extra copy)
    s.emplace(20);
    s.emplace(50);
    printSet("After insert & emplace (auto-sorted)", s); // { 10 20 30 40 50 }

    // emplace_hint(pos, args...): Inserts in amortized O(1) time IF the hint iterator is right before the spot
    s.emplace_hint(s.end(), 60);
    printSet("After emplace_hint(s.end(), 60)", s); // { 10 20 30 40 50 60 }

    // erase(val): Removes element by value in O(log N) time (returns 1 if removed, 0 if not found)
    size_t removedCount = s.erase(30);
    cout << "Removed 30? " << (removedCount ? "Yes" : "No") << "\n";

    // erase(pos): Removes element at a specific iterator position in amortized O(1) time
    auto itFirst = s.begin();
    s.erase(itFirst); // Removes 10
    printSet("After erasing 30 and first element (10)", s); // { 20 40 50 60 }

    // erase(first, last): Removes a range of elements [first, last)
    // Example: erase everything from 50 to end()
    s.erase(s.find(50), s.end());
    printSet("After range erase [50, end)", s); // { 20 40 }

    // extract(val) [C++17]: Unlinks a node from the set WITHOUT deallocating memory (can modify & re-insert)
    s.insert(70);
    auto nodeHandle = s.extract(70);
    if (!nodeHandle.empty()) {
        nodeHandle.value() = 75; // Safely modify key without reallocating node
        s.insert(move(nodeHandle));
    }
    printSet("After C++17 extract & re-insert (70 -> 75)", s); // { 20 40 75 }


    // 3. LOOKUP & BOUNDS FUNCTIONS (All O(log N) time)
    // Note: std::set has NO random access ([] or .at() do NOT exist).
    cout << "\n--- Lookup & Bounds ---\n";
    s.insert({10, 30, 50}); // Set is now { 10 20 30 40 50 75 }
    printSet("Current set for lookups", s);

    // find(val): Returns iterator to val if found, otherwise returns s.end()
    auto findIt = s.find(30);
    if (findIt != s.end()) {
        cout << "Found element: " << *findIt << "\n";
    } else {
        cout << "30 not found\n";
    }

    // count(val): Returns 1 if val exists in the set, 0 otherwise (since all elements are unique)
    cout << "Count of 40: " << s.count(40) << ", Count of 99: " << s.count(99) << "\n";

    // contains(val) [C++20]: Cleaner boolean check returning true if val exists, false otherwise
    // cout << "Contains 50? " << (s.contains(50) ? "Yes" : "No") << "\n";

    // lower_bound(val): Returns iterator to the FIRST element >= val (or s.end() if none)
    auto lb = s.lower_bound(30);
    if (lb != s.end()) cout << "lower_bound(30) [>= 30]: " << *lb << "\n"; // 30

    // upper_bound(val): Returns iterator to the FIRST element > val (or s.end() if none)
    auto ub = s.upper_bound(30);
    if (ub != s.end()) cout << "upper_bound(30) [> 30]: " << *ub << "\n";  // 40

    // equal_range(val): Returns pair<iterator, iterator> = {lower_bound(val), upper_bound(val)}
    auto eqRange = s.equal_range(40);
    cout << "equal_range(40) -> lower: " << *eqRange.first << ", upper: " << *eqRange.second << "\n";


    // 4. ITERATOR FUNCTIONS
    // Note: Set iterators are bidirectional (++it and --it work, but it + 2 does NOT work).
    // All set iterators are implicitly const (you cannot modify *it directly because it would break tree order).
    cout << "\n--- Iterators ---\n";

    // begin() & end(): Forward traversal in sorted ascending order
    cout << "Forward (begin to end): ";
    for (auto it = s.begin(); it != s.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    // Accessing smallest (front) and largest (back) elements using iterators
    if (!s.empty()) {
        cout << "Smallest element (*s.begin()): " << *s.begin() << "\n";
        cout << "Largest element (*s.rbegin()): " << *s.rbegin() << "\n";
    }

    // rbegin() & rend(): Reverse traversal from largest to smallest
    cout << "Reverse (rbegin to rend): ";
    for (auto rit = s.rbegin(); rit != s.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << "\n";

    // cbegin() & cend(): Explicitly constant iterators
    cout << "Const forward (cbegin to cend): ";
    for (auto cit = s.cbegin(); cit != s.cend(); ++cit) {
        cout << *cit << " ";
    }
    cout << "\n";


    // 5. SWAPPING, MERGING & CLEARING
    cout << "\n--- Swap, Merge & Clear ---\n";
    set<int> s2 = {100, 200, 30}; // Shares 30 with s

    // merge(other) [C++17]: Splices unique elements from s2 into s without copying/allocating.
    // Duplicates (like 30) remain inside s2.
    s.merge(s2);
    printSet("Set s after s.merge(s2)", s);
    printSet("Set s2 after merge (only duplicate 30 left)", s2);

    // swap(other): Exchanges contents between two sets of the same type in O(1) time
    s.swap(s2);
    printSet("Set s after swap with s2", s);
    printSet("Set s2 after swap with s", s2);

    // clear(): Destroys all elements in O(N) time, leaving size() as 0
    s.clear();
    printSet("Set s after clear()", s);


    // 6. DESCENDING SET WITH greater<int>
    cout << "\n--- Descending Set (greater<int>) ---\n";
    set<int, greater<int>> descSet = {10, 50, 20, 40, 30};
    printDescSet("descSet", descSet); // { 50 40 30 20 10 }

    // Note: In a greater<int> set, lower_bound(val) finds first element <= val,
    // and upper_bound(val) finds first element < val!
    auto descLb = descSet.lower_bound(35); // First element <= 35 -> 30
    auto descUb = descSet.upper_bound(30); // First element < 30  -> 20
    if (descLb != descSet.end()) cout << "descSet.lower_bound(35) [<= 35]: " << *descLb << "\n";
    if (descUb != descSet.end()) cout << "descSet.upper_bound(30) [< 30]: " << *descUb << "\n";


    // 7. SET ALGORITHMS (<algorithm>)
    // Works on any sorted containers in O(N + M) time
    cout << "\n--- Set Math Operations (<algorithm>) ---\n";
    set<int> setA = {1, 2, 3, 4, 5};
    set<int> setB = {4, 5, 6, 7, 8};
    set<int> unionRes, interRes, diffRes, symDiffRes;

    // set_union(): Elements present in setA OR setB
    set_union(setA.begin(), setA.end(), setB.begin(), setB.end(), inserter(unionRes, unionRes.begin()));
    printSet("Union (A U B)", unionRes); // { 1 2 3 4 5 6 7 8 }

    // set_intersection(): Elements present in BOTH setA AND setB
    set_intersection(setA.begin(), setA.end(), setB.begin(), setB.end(), inserter(interRes, interRes.begin()));
    printSet("Intersection (A n B)", interRes); // { 4 5 }

    // set_difference(): Elements present in setA but NOT in setB
    set_difference(setA.begin(), setA.end(), setB.begin(), setB.end(), inserter(diffRes, diffRes.begin()));
    printSet("Difference (A - B)", diffRes); // { 1 2 3 }

    // set_symmetric_difference(): Elements in setA or setB, but NOT both
    set_symmetric_difference(setA.begin(), setA.end(), setB.begin(), setB.end(), inserter(symDiffRes, symDiffRes.begin()));
    printSet("Symmetric Difference (A ^ B)", symDiffRes); // { 1 2 3 6 7 8 }

    return 0;
}
