#include "LRUCache.h" // Gives reference to the class definiton
#include <iostream>
using namespace std;


// Initialize constructor function
LRUCache::LRUCache(int capacity) {
    this->capacity = capacity;
    hits = 0;
    misses = 0;
}


// get() function
// Gets the keys from the map
// Returns -1 if not found 
int LRUCache::get(int key){
    // Cache miss - key not found so return -1
    if(cacheMap.find(key) == cacheMap.end()){
        ++misses;
        return -1;
    }

    // Cache hit - key found 
    ++hits;
    // Now move the hit item to front
    // use the cacheMap to find the pointer to the key and move to begin() i.e. front position in our cacheList
    cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);

    return cacheMap[key] -> second; // As each node is a pair. "cacheMap[key] -> second" gives the value part only
}


// put() function
// Inserts into the cache
// Evict from last is full
void LRUCache::put(int key, int value){

    // If key already exists
    if(cacheMap.find(key) != cacheMap.end()){
        cacheMap[key] -> second = value; // update the value
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]); // move to front
        return;
    }

    // If cache is full
    if((int)cacheList.size() == capacity){
        int lruKey = cacheList.back().first; // least recently used item's key
        cacheList.pop_back(); // evict the last item
        cacheMap.erase(lruKey); // remove item from cache memory map also
    }

    // Insert the new item
    cacheList.push_front({key, value}); // insert new item in front
    cacheMap[key] = cacheList.begin(); // add it to cache memory map also
}


// printCache() function
// Print the cache map for easy debugging and checking the simulation works
// Loops through the list from front to back and prints each node
// Most recently used to least recently used (front to back)
void LRUCache::printCache(){
    cout << "Cache (MRU ---> LRU) : ";
    for(auto& pair : cacheList){
        cout << "[" << pair.first << ":" << pair.second << "] ";
    }
    cout << endl;
}


// Getter for hits
int LRUCache::getHits() {
    return hits;
}


// Getter for misses
int LRUCache::getMisses() {
    return misses;
}