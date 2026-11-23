#include <bits/stdc++.h> // in g++ compilers, this alone is sufficient

#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

// Custom struct for demonstrating custom heap comparators
struct Task {
    string name;
    int priority;
};

// Custom Comparator Functor for std::priority_queue
// IMPORTANT: Unlike std::sort(), priority_queue comparator returns TRUE if 'a' has LOWER priority than 'b'
// (i.e., 'a' should sink below 'b', meaning 'b' pops out FIRST).
struct CompareTask {
    bool operator()(const Task& a, const Task& b) {
        return a.priority < b.priority; // Max-Heap by priority (higher priority pops first)
    }
};

int main() {
    // =========================================================================
    // 1. MAX-HEAP (Default std::priority_queue)
    // =========================================================================
    // Stores elements in a Binary Heap (built on top of std::vector).
    // Largest element is ALWAYS at the top().
    // Note: priority_queue has NO iterators (begin/end do NOT exist) and NO clear() method!
    cout << "=== 1. Max-Heap (Default) ===\n";
    priority_queue<int> maxPQ;

    // empty() & size(): O(1) time
    cout << "Is empty initially? " << (maxPQ.empty() ? "Yes" : "No") << "\n";

    // push(val) & emplace(args...): Inserts element and bubbles it up in O(log N) time
    maxPQ.push(30);
    maxPQ.push(10);
    maxPQ.push(50);
    maxPQ.emplace(20);
    maxPQ.emplace(40);

    cout << "Size after insertions: " << maxPQ.size() << "\n";

    // top(): Returns const reference to the LARGEST element in O(1) time
    cout << "Current top (max): " << maxPQ.top() << "\n"; // 50

    // pop(): Removes the top (largest) element and re-heapifies in O(log N) time (returns void)
    maxPQ.pop();
    cout << "Top after one pop(): " << maxPQ.top() << "\n"; // 40

    // Traversing & emptying a priority_queue (destructively, since no iterators exist)
    cout << "Popping all remaining elements (descending): ";
    while (!maxPQ.empty()) {
        cout << maxPQ.top() << " ";
        maxPQ.pop();
    }
    cout << "\n\n";


    // =========================================================================
    // 2. MIN-HEAP (Smallest Element at top())
    // =========================================================================
    // Requires 3 template arguments: <Type, UnderlyingContainer, Comparator>
    cout << "=== 2. Min-Heap (greater<int>) ===\n";
    priority_queue<int, vector<int>, greater<int>> minPQ;

    minPQ.push(30);
    minPQ.push(10);
    minPQ.push(50);
    minPQ.emplace(20);

    cout << "Current top (min): " << minPQ.top() << "\n"; // 10

    cout << "Popping all elements (ascending): ";
    while (!minPQ.empty()) {
        cout << minPQ.top() << " ";
        minPQ.pop();
    }
    cout << "\n\n";


    // =========================================================================
    // 3. O(N) FAST HEAP CONSTRUCTION FROM AN EXISTING VECTOR
    // =========================================================================
    // Pushing N elements one-by-one takes O(N log N) time.
    // Passing iterators (v.begin(), v.end()) builds the heap in O(N) linear time!
    cout << "=== 3. O(N) Heap Initialization from Vector ===\n";
    vector<int> nums = {40, 15, 70, 10, 90, 25};

    // O(N) Max-Heap from vector
    priority_queue<int> fastMaxPQ(nums.begin(), nums.end());
    cout << "fastMaxPQ top: " << fastMaxPQ.top() << "\n"; // 90

    // O(N) Min-Heap from vector
    priority_queue<int, vector<int>, greater<int>> fastMinPQ(nums.begin(), nums.end());
    cout << "fastMinPQ top: " << fastMinPQ.top() << "\n\n"; // 10


    // =========================================================================
    // 4. SWAPPING & CLEARING A PRIORITY_QUEUE
    // =========================================================================
    cout << "=== 4. Swap & Clear Workaround ===\n";
    priority_queue<int> pqA, pqB;
    pqA.push(100);
    pqB.push(999);

    // swap(other): Exchanges contents of two priority_queues of the exact same type in O(1) time
    pqA.swap(pqB);
    cout << "pqA top after swap: " << pqA.top() << "\n"; // 999

    // Since priority_queue has NO .clear() method, reassigning an empty queue clears it cleanly:
    pqA = priority_queue<int>();
    cout << "pqA size after clearing: " << pqA.size() << "\n\n";


    // =========================================================================
    // 5. PRIORITY QUEUE OF PAIRS (Essential for Dijkstra & Graph Algorithms)
    // =========================================================================
    // Pairs compare by .first first, and break ties using .second
    cout << "=== 5. Pair Min-Heap (e.g., {distance, node}) ===\n";
    using PII = pair<int, int>;
    priority_queue<PII, vector<PII>, greater<PII>> dijkstraPQ;

    dijkstraPQ.push({10, 2}); // distance 10 to node 2
    dijkstraPQ.push({5, 4});  // distance 5 to node 4
    dijkstraPQ.push({5, 1});  // distance 5 to node 1 (tie broken by smaller node ID: 1 < 4)

    while (!dijkstraPQ.empty()) {
        auto [dist, node] = dijkstraPQ.top(); // C++17 structured binding
        dijkstraPQ.pop();
        cout << "Node " << node << " with distance " << dist << "\n";
    }
    cout << "\n";


    // =========================================================================
    // 6. CUSTOM STRUCT WITH CUSTOM COMPARATOR
    // =========================================================================
    cout << "=== 6. Custom Struct Priority Queue ===\n";
    priority_queue<Task, vector<Task>, CompareTask> taskPQ;

    taskPQ.push({"Low priority email", 1});
    taskPQ.push({"Critical server outage", 10});
    taskPQ.push({"Code review", 5});

    while (!taskPQ.empty()) {
        cout << "[Priority " << taskPQ.top().priority << "] " << taskPQ.top().name << "\n";
        taskPQ.pop();
    }

    return 0;
}
