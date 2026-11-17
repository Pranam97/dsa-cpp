#include <bits/stdc++.h> // in g++ compilers, this alone is sufficient

#include <iostream>
#include <vector>
#include <string>
#include <algorithm> // Required for sort, reverse, find, count, unique, min_element, max_element
#include <numeric>   // Required for accumulate
using namespace std;

// Helper function to print vector contents
void printVector(const string& label, const vector<int>& v) {
    cout << label << " [Size: " << v.size() << ", Cap: " << v.capacity() << "]: ";
    for (int x : v) {
        cout << x << " ";
    }
    cout << "\n";
}

int main() {
    // 1. INITIALIZATION & CAPACITY FUNCTIONS
    vector<int> v;

    // empty(): Checks if the vector has 0 elements (returns true/false)
    cout << "Is empty initially? " << (v.empty() ? "Yes" : "No") << "\n";

    // reserve(n): Pre-allocates memory for at least n elements to prevent reallocations
    // This is useful when we know the exact number of elements which will be added to the vector ex: 10
    // By doing this we can improve the efficiency(time complexity) of insertion 
    // Although the amortized insertion TC is O(1), the total TC for n elements insertions is improved
    // by a small margin.
    v.reserve(10);
    cout << "Capacity after reserve(10): " << v.capacity() << "\n";

    cout<< "Size of vector(number of elements present) " << v.size() <<endl;
    // max_size(): Returns the theoretical maximum number of elements the vector can hold
    cout << "Max possible size: " << v.max_size() << "\n\n";


    // 2. MODIFIER FUNCTIONS (Adding & Removing)
    // push_back(val): Adds a copy of val to the end of the vector
    v.push_back(10);
    v.push_back(20);

    // emplace_back(args): Constructs an element directly in-place at the end
    v.emplace_back(30);
    printVector("After push_back & emplace_back", v);

    // insert(pos, val): Inserts val before the specified iterator position
    v.insert(v.begin() + 1, 15); // Inserts 15 at index 1

    // emplace(pos, args): Constructs an element in-place before the iterator position
    v.emplace(v.end(), 40);      // Inserts 40 at the end
    printVector("After insert & emplace", v);

    // pop_back(): Removes the last element (does not return it)
    v.pop_back();
    printVector("After pop_back", v);

    // erase(pos): Removes the element at the specified iterator position
    v.erase(v.begin() + 1);      // Removes 15 at index 1
    printVector("After erase(index 1)", v);


    // 3. ELEMENT ACCESS FUNCTIONS
    cout << "\n--- Element Access ---\n";

    // at(i): Accesses element WITH bounds checking (throws out_of_range if invalid)
    cout << "v.at(1): " << v.at(1) << "\n";

    // front() & back(): Accesses the first and last elements directly
    cout << "front(): " << v.front() << ", back(): " << v.back() << "\n";

    // data(): Returns a raw pointer to the underlying C-style array in memory
    int* rawPtr = v.data();
    cout << "First element via data() pointer: " << *rawPtr << "\n\n";


    // 4. ITERATOR FUNCTIONS
    cout << "--- Iterators ---\n";
    // begin() & end(): Forward traversal from first element to past-the-end
    cout << "Forward (begin to end): ";
    for (auto it = v.begin(); it != v.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";

    // rbegin() & rend(): Reverse traversal from last element back to first
    cout << "Reverse (rbegin to rend): ";
    for (auto rit = v.rbegin(); rit != v.rend(); ++rit) {
        cout << *rit << " ";
    }
    cout << "\n";

    // cbegin() & cend(): Constant iterators (elements can be read, but not modified)
    cout << "Const forward (cbegin to cend): ";
    for (auto cit = v.cbegin(); cit != v.cend(); ++cit) {
        cout << *cit << " ";
    }
    cout << "\n\n";


    // 5. RESIZING, SWAPPING & CLEARING
    // resize(n, val): Changes size to n. Fills new slots with val (or 0 if omitted)
    v.resize(5, 99);
    printVector("After resize(5, 99)", v);

    // shrink_to_fit(): Requests the vector to reduce capacity() to match size()
    v.shrink_to_fit();
    printVector("After shrink_to_fit", v);

    // assign(count, val): Replaces all current contents with count copies of val
    vector<int> v2;
    v2.assign(3, 7); // {7, 7, 7}
    printVector("Vector v2 after assign(3, 7)", v2);

    // swap(other): Exchanges contents and capacity between two vectors in O(1) time
    v.swap(v2);
    printVector("Vector v after swap with v2", v);

    // clear(): Removes all elements, leaving size() as 0 (capacity remains unchanged)
    v.clear();
    printVector("Vector v after clear()", v);


    // 6. ALGORITHM & NUMERIC FUNCTIONS (<algorithm> & <numeric>)
    cout << "\n--- Algorithm Functions ---\n";
    vector<int> nums = {40, 10, 50, 20, 30, 20, 10};
    printVector("Initial nums", nums);

    // sort(): Sorts elements in ascending order in O(N log N) time
    sort(nums.begin(), nums.end());
    printVector("After sort() ascending", nums);

    // sort() with greater<int>(): Sorts elements in descending order
    sort(nums.begin(), nums.end(), greater<int>());
    printVector("After sort() descending", nums);

    // reverse(): Reverses the order of elements in place
    reverse(nums.begin(), nums.end());
    printVector("After reverse()", nums);

    // min_element() & max_element(): Return iterators to the smallest and largest values
    auto minIt = min_element(nums.begin(), nums.end());
    auto maxIt = max_element(nums.begin(), nums.end());
    cout << "Min element: " << *minIt << ", Max element: " << *maxIt << "\n";

    // count(): Counts how many times a specific value appears
    int count20 = count(nums.begin(), nums.end(), 20);
    cout << "Count of 20: " << count20 << "\n";

    // find(): Searches for a value and returns an iterator to its first occurrence (or end() if missing)
    auto findIt = find(nums.begin(), nums.end(), 30);
    if (findIt != nums.end()) {
        // distance() calculates the 0-based index from begin()
        cout << "Found 30 at index: " << distance(nums.begin(), findIt) << "\n";
    } else {
        cout << "30 not found\n";
    }

    // binary_search(): Fast O(log N) check if an element exists (vector MUST be sorted first)
    bool has40 = binary_search(nums.begin(), nums.end(), 40);
    cout << "Does 40 exist (binary_search)? " << (has40 ? "Yes" : "No") << "\n";

    // lower_bound() & upper_bound(): Return iterators to first element >= val and > val (requires sorted vector)
    auto lb = lower_bound(nums.begin(), nums.end(), 20);
    auto ub = upper_bound(nums.begin(), nums.end(), 20);
    cout << "First 20 at index: " << distance(nums.begin(), lb)
         << ", Element after last 20 at index: " << distance(nums.begin(), ub) << "\n";

    // unique() + erase(): Removes consecutive duplicates (sort first to remove ALL duplicates)
    auto lastUnique = unique(nums.begin(), nums.end());
    nums.erase(lastUnique, nums.end());
    printVector("After removing duplicates (unique + erase)", nums);

    // accumulate() from <numeric>: Calculates the sum of all elements starting from initial value 0
    int totalSum = accumulate(nums.begin(), nums.end(), 0);
    cout << "Sum of all elements (accumulate): " << totalSum << "\n";

    return 0;
}
