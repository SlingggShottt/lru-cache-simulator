#include "LRUCache.h"
#include <iostream>
#include <random> // for simulation - random number generation
#include <iomanip> // formatting the output

using namespace std;


// Simulating a fetch from database or api call
int fetchFromDatabase(int key) {
    return key * 10;
}


// Run the simulation
void runSimulation(){
    
    const int CACHE_CAPACITY = 100;   // cache capacity declaration
    const int TOTAL_QUERIES  = 10000; // total queries to be simulated
    const int KEY_RANGE      = 200;   // keys will be between 0-199
    const int HOT_KEY_RANGE  = 50;    // "popular" keys — between 0-49


    LRUCache cache(CACHE_CAPACITY); // initialize cache memory object


    // Random numbers setup for simulation
    mt19937 rng(42); // fix the random seed for predictable results
    uniform_int_distribution<int> hotKeys(0, HOT_KEY_RANGE - 1); // popular keys
    uniform_int_distribution<int> allKeys(0, KEY_RANGE - 1); // all keys
    uniform_int_distribution<int> bias(1, 100); // probability for simulating 80/20 split


    // Simulator formatting
    cout << "Starting LRU Cache Simulation..." << endl;
    cout << "Cache Capacity : " << CACHE_CAPACITY << endl;
    cout << "Total Queries to be simulated : " << TOTAL_QUERIES  << endl;
    cout << "─────────────────────────────────" << endl;


    // Pre-populate cache with some initial data
    cout << "\nPre-populating cache..." << endl;
    for(int i=0; i<CACHE_CAPACITY; i++){
        cache.put(i, fetchFromDatabase(i)); // key-value pair
    }
    cout << "Cache pre-populated with " << CACHE_CAPACITY << " items" << endl;
    cout << "─────────────────────────────────" << endl;


    // Run the specified queries
    cout << "\nRunning simulation..." << endl;
    for(int i=0; i<TOTAL_QUERIES; i++){
        int key;

        if(bias(rng) <= 80){ // 80% of the time access popular keys (0-49)
            key = hotKeys(rng);
        }
        else { // 20% of the time access any key (0-199)
            key = allKeys(rng);
        }

        int result = cache.get(key); // find the key specified in the cacheMap

        // If cache miss
        if (result == -1) {
            int value = fetchFromDatabase(key); // fetch from database
            cache.put(key, value); // store in cache
        }

        // Print cache state every 1000 queries for visual representation and understanding
        if ((i + 1) % 1000 == 0) { // i+1 as we started from i=0
            cout << "After " << setw(5) << (i + 1) << " queries → "; // setw() is for formatting - pads the number to 5 character wide so output aligns neatly
            cache.printCache();
        }
    }


    // Final Report
    int totalQueries = cache.getHits() + cache.getMisses(); // total ran queries
    double hitRatio  = (double)cache.getHits() / totalQueries * 100.0; // how many hits in percentage
    double missRatio = (double)cache.getMisses() / totalQueries * 100.0; // how many misses in percentage

    cout << "\n─────────────────────────────────" << endl;
    cout << "         SIMULATION REPORT        " << endl;
    cout << "─────────────────────────────────" << endl;
    cout << "Total Queries      : " << totalQueries        << endl;
    cout << "Cache Hits (%)     : " << cache.getHits()     << endl;
    cout << "Cache Misses (%)   : " << cache.getMisses()   << endl;
    cout << fixed << setprecision(2);
    cout << "Hit  Ratio        : " << hitRatio            << "%" << endl;
    cout << "Miss Ratio        : " << missRatio           << "%" << endl;
    cout << "─────────────────────────────────" << endl;
}


// main function from where the execution starts
int main() {
    runSimulation();
    return 0;
}