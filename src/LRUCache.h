#pragma once // Include this file only once

// Data structures we need
#include<unordered_map>
#include<list>
using namespace std;

// Class definition
class LRUCache{

private:
    int capacity; // Size of our cache
    list<pair<int,int>> cacheList; // Each node holds a key-value pair
    unordered_map<int, list<pair<int,int>>::iterator> cacheMap; // Stores key and direct pointer to the value of the key in list

    // To track hits and misses
    int hits, misses;

public:
    LRUCache(int capacity); // Constructor

    int get(int key); // Look up a value. Returns -1 if not found (cache miss).       
    void put(int key, int value); // Insert into cache. Evicts LRU item if full.
    void printCache(); // Prints current cache state — for debugging and check ifsimulator working.
    
    // Getters for hits and misses
    int getHits();           
    int getMisses(); 
};