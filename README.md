# LRU Cache Simulator in C++

An in-memory LRU (Least Recently Used) Cache Simulator built in modern C++.

## Data Structures Used
- `std::unordered_map` for O(1) key lookup
- `std::list` (doubly linked list) for O(1) order tracking

## Time Complexity
| Operation | Complexity |
|-----------|------------|
| get(key)  | O(1)       |
| put(key)  | O(1)       |
| evict     | O(1)       |

## How to Run
```bash
g++ -o cache src/main.cpp src/LRUCache.cpp
./cache
```

## Features
- Automatic LRU eviction when cache is full
- Configurable cache capacity
- Cache hit/miss ratio tracking
- Simulates 10,000+ data queries