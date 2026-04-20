// Testing the simulation
#include "../src/LRUCache.h"
#include <iostream>
#include <string>

using namespace std;


// ─────────────────────────────────
// Test runner helpers
// ─────────────────────────────────

//counts of passes and fails
int testsPassed = 0;
int testsFailed = 0;

// check() function for our test cases
void check(const string& testName, bool condition){
    if(condition){ // if test passes
        cout << "  ✓ PASS : " << testName << endl;
        ++testsPassed;
    }
    else{ // if test fails
        cout << "  ✗ FAIL : " << testName << endl;
        ++testsFailed;
    }
}


// Formatting
void printSectionHeader(const string& title) {
    cout << "\n─────────────────────────────────" << endl;
    cout << "  " << title << endl;
    cout << "─────────────────────────────────" << endl;
}


// ─────────────────────────────────
// Test 1: Basic put and get
// ─────────────────────────────────

void testBasicPutAndGet(){
    printSectionHeader("Test 1 : Basic put and get");

    // Create a small cache to test on
    LRUCache cache(3);
    // Fake testing data
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    // Printing values for respective keys to check
    check("get key 1 returns 10", cache.get(1) == 10);
    check("get key 2 returns 20", cache.get(2) == 20);
    check("get key 3 returns 30", cache.get(3) == 30);
}


// ─────────────────────────────────
// Test 2: Cache miss returns -1
// ─────────────────────────────────
void testCacheMiss() {
    printSectionHeader("Test 2 : Cache miss returns -1");

    // Create a small cache to test on
    LRUCache cache(3);
    // Fake data for testing
    cache.put(1, 10);
    // Giving wrong keys
    check("get missing key 99 returns -1", cache.get(99) == -1);
    check("get missing key 0 returns -1",  cache.get(0)  == -1);
}


// ─────────────────────────────────
// Test 3: LRU eviction order
// ─────────────────────────────────
void testLRUEviction() {
    printSectionHeader("Test 2 : Cache miss returns -1");

    // Create a small cache to test on
    LRUCache cache(3);
    // Fake data for testing
    cache.put(1, 10); // cache: [1]
    cache.put(2, 20); // cache: [2,1]
    cache.put(3, 30); // cache: [3,2,1]
    cache.put(4, 40); // cache: [4,3,2] - 1 is evicted as cache is full
    // Checking if keys return correct value
    check("key 1 was evicted so it should return -1", cache.get(1) == -1);
    check("key 2 still exists", cache.get(2) == 20);
    check("key 3 still exists", cache.get(3) == 30);
    check("key 4 was inserted", cache.get(4) == 40);
}


// ─────────────────────────────────
// Test 4: Update existing key
// ─────────────────────────────────
void testUpdateExistingKey() {
    printSectionHeader("Test 4 : Update existing key");

    // Create a small cache to test on
    LRUCache cache(3);
    // Fake data for testing
    cache.put(1, 10);
    cache.put(2, 20);
    cache.put(3, 30);
    cache.put(1, 999);  // update key 1's value and moves to front
    // Checking if keys return correct value
    check("key 1 value updated to 999", cache.get(1) == 999);
    check("key 2 unchanged", cache.get(2) == 20);
    check("key 3 unchanged", cache.get(3) == 30);
}


// ─────────────────────────────────
// Test 5: Re-access protects from eviction
// ─────────────────────────────────
void testReAccessProtectsFromEviction() {
    printSectionHeader("Test 5 : Re-access protects item from eviction");

    LRUCache cache(3);
    cache.put(1, 10);   // cache: [1]
    cache.put(2, 20);   // cache: [2, 1]
    cache.put(3, 30);   // cache: [3, 2, 1]

    cache.get(1);       // access key 1 so it moves to front
                        // cache: [1, 3, 2]

    cache.put(4, 40);   // cache full — evicts 2; now cache: [4, 1, 3]

    check("key 1 protected by re-access", cache.get(1) == 10);
    check("key 2 evicted (was LRU)", cache.get(2) == -1);
    check("key 3 still exists", cache.get(3) == 30);
    check("key 4 inserted", cache.get(4) == 40);
}


// ─────────────────────────────────
// Test 6: Capacity 1 edge case
// ─────────────────────────────────
void testCapacityOne() {
    printSectionHeader("Test 6 : Capacity 1 edge case");

    LRUCache cache(1);
    cache.put(1, 10);
    check("key 1 inserted", cache.get(1) == 10);

    cache.put(2, 20); // evicts key 1 immediately
    check("key 1 evicted", cache.get(1) == -1);
    check("key 2 inserted", cache.get(2) == 20);

    cache.put(3, 30); // evicts key 2 immediately
    check("key 2 evicted", cache.get(2) == -1);
    check("key 3 inserted", cache.get(3) == 30);
}


// ─────────────────────────────────
// Test 7: Hit and miss stats
// ─────────────────────────────────
void testHitMissStats() {
    printSectionHeader("Test 7 : Hit and miss stats");

    LRUCache cache(3);
    cache.put(1, 10);
    cache.put(2, 20);

    cache.get(1); // hit
    cache.get(2); // hit
    cache.get(99); // miss
    cache.get(100); // miss
    cache.get(1); // hit

    check("3 hits recorded", cache.getHits()   == 3);
    check("2 misses recorded", cache.getMisses() == 2);
}


// ─────────────────────────────────
// Test 8: Update moves item to front
// (protects updated item from eviction)
// ─────────────────────────────────
void testUpdateMovesToFront() {
    printSectionHeader("Test 8 : Update moves item to front");

    LRUCache cache(3);
    cache.put(1, 10); // cache: [1]
    cache.put(2, 20); // cache: [2, 1]
    cache.put(3, 30); // cache: [3, 2, 1]

    cache.put(1, 100); // update key 1 — moves to front
                       // cache: [1, 3, 2]

    cache.put(4, 40); // evicts key 2 (LRU), cache: [4, 1, 3]

    check("key 1 updated and protected",  cache.get(1) == 100);
    check("key 2 evicted after update",   cache.get(2) == -1);
    check("key 3 still exists",           cache.get(3) == 30);
    check("key 4 inserted",               cache.get(4) == 40);
}


// ─────────────────────────────────
// Main — run all tests
// ─────────────────────────────────
int main() {
    cout << "\n═════════════════════════════════" << endl;
    cout << "     LRU CACHE TEST SUITE         " << endl;
    cout << "═════════════════════════════════" << endl;

    testBasicPutAndGet();
    testCacheMiss();
    testLRUEviction();
    testUpdateExistingKey();
    testReAccessProtectsFromEviction();
    testCapacityOne();
    testHitMissStats();
    testUpdateMovesToFront();

    // Final summary
    cout << "\n═════════════════════════════════" << endl;
    cout << "     RESULTS                      " << endl;
    cout << "═════════════════════════════════" << endl;
    cout << "  Tests Passed : " << testsPassed << endl;
    cout << "  Tests Failed : " << testsFailed << endl;
    cout << "  Total Tests  : " << testsPassed + testsFailed << endl;

    if (testsFailed == 0) {
        cout << "\n  ✓ All tests passed!" << endl;
    } else {
        cout << "\n  ✗ Some tests failed." << endl;
    }
    cout << "═════════════════════════════════\n" << endl;

    return testsFailed == 0 ? 0 : 1;
}