# LRU Cache Simulator in C++

> An in-memory **Least Recently Used (LRU) Cache Simulator** built in modern C++, combining `std::unordered_map` and `std::list` to achieve **O(1)** time complexity for all cache operations.

---

## What is this project?

A cache is a small, fast storage area that holds frequently used data so programs don't have to fetch it from slow sources (databases, disk) every time. When the cache is full, it needs to decide what to remove — this project implements the **LRU eviction policy**: remove the item that hasn't been used for the longest time.

This simulator models real-world cache behavior by processing **10,000+ queries** with an 80/20 access pattern (80% of requests target 20% of the data — mimicking real usage like social media feeds, search engines, and CDNs), achieving a **89.97% cache hit ratio**.

---

## Project Structure

```
lru-cache-simulator/
├── src/
│   ├── LRUCache.h        ← Class blueprint (data structures + function declarations)
│   ├── LRUCache.cpp      ← Full implementation (get, put, eviction logic)
│   └── main.cpp          ← Simulation runner (10,000 queries + hit ratio report)
├── tests/
│   └── test_cache.cpp    ← Automated test suite (27 tests, 8 test cases)
├── Makefile              ← Build system
└── README.md
```

---

## Core Design: Why Two Data Structures?

This is the key insight of the project. A single data structure cannot achieve O(1) for everything:

| Structure alone | Find item | Track usage order | Evict LRU |
|---|---|---|---|
| `unordered_map` only | O(1) | ❌ No ordering | O(n) scan needed |
| `list` only | O(n) scan | O(1) | O(1) |
| **Both together** | **O(1)** | **O(1)** | **O(1)** |

### How they work together

```
unordered_map stores: key → direct pointer (iterator) to node in list
                      ↓
list stores: actual data ordered from Most → Least Recently Used

       unordered_map
      ┌──────────────────────────────────────┐
      │  key1 ──────────────────────────┐    │
      │  key3 ──────────────┐           │    │
      │  key7 ────┐         │           │    │
      └───────────┼─────────┼───────────┼────┘
                  ↓         ↓           ↓
  FRONT ←→ [key7] ←→ [key3] ←→ [key1] ←→ BACK
             MRU                   LRU
           (keep)               (evict when full)
```

- **Map** answers: *"Does this key exist? Where is it?"* → O(1)  
- **List** answers: *"What's the usage order? What to evict?"* → O(1)  
- **Together**: Get any item AND maintain perfect usage order → O(1)

---

## Time Complexity

| Operation | Complexity | How |
|---|---|---|
| `get(key)` | O(1) | HashMap lookup + list splice via direct pointer |
| `put(key, value)` | O(1) | HashMap insert + list push_front |
| Eviction | O(1) | list pop_back + HashMap erase |

---

## Key Implementation Details

### `get(key)` — Cache lookup
```cpp
int LRUCache::get(int key) {
    if (cacheMap.find(key) == cacheMap.end()) {
        ++misses;
        return -1;  // cache miss
    }
    ++hits;
    // Move accessed item to front (most recently used) in O(1)
    cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
    return cacheMap[key]->second;
}
```

### `put(key, value)` — Cache insert with eviction
```cpp
void LRUCache::put(int key, int value) {
    if (cacheMap.find(key) != cacheMap.end()) {
        cacheMap[key]->second = value;
        cacheList.splice(cacheList.begin(), cacheList, cacheMap[key]);
        return;
    }
    if ((int)cacheList.size() == capacity) {
        int lruKey = cacheList.back().first;  // LRU item is always at back
        cacheList.pop_back();
        cacheMap.erase(lruKey);               // must remove from both structures
    }
    cacheList.push_front({key, value});
    cacheMap[key] = cacheList.begin();        // store direct pointer in map
}
```

### Memory Safety — RAII
By using standard library containers (`std::list`, `std::unordered_map`), memory is automatically managed when objects go out of scope. No manual `malloc/free`, no memory leaks — this is the C++ RAII (Resource Acquisition Is Initialization) principle in practice.

---

## How to Build and Run

### Prerequisites
- g++ with C++17 support
- make

### Clone the repository
```bash
git clone https://github.com/SlingggShottt/lru-cache-simulator.git
cd lru-cache-simulator
```

### Build and run the simulator
```bash
make
./cache
```

### Run the automated test suite
```bash
make test
```

### Clean compiled files
```bash
make clean
```

---

## Simulation Results

The simulator runs 10,000 queries with an 80/20 access bias — 80% of requests target only 50 "hot" keys (out of 200 total), mimicking real-world access patterns.

```
─────────────────────────────────
         SIMULATION REPORT        
─────────────────────────────────
Total Queries      : 10000
Cache Hits         : 8997
Cache Misses       : 1003
Hit  Ratio         : 89.97%
Miss Ratio         : 10.03%
─────────────────────────────────
```

**89.97% hit ratio** means nearly 9 out of 10 requests were served directly from fast memory — no slow database fetch needed.

---

## Test Suite Results

8 test cases covering all core behaviors and edge cases:

```
═════════════════════════════════
     RESULTS                      
═════════════════════════════════
  Tests Passed : 27
  Tests Failed : 0
  Total Tests  : 27

  ✓ All tests passed!
═════════════════════════════════
```

| Test | What it verifies |
|---|---|
| Basic put and get | Core read/write functionality |
| Cache miss returns -1 | Correct handling of missing keys |
| LRU eviction order | Correct item evicted when cache is full |
| Update existing key | Value update moves item to front |
| Re-access protects from eviction | Accessing an item saves it from being evicted |
| Capacity 1 edge case | Correct behavior at minimum cache size |
| Hit and miss stats | Accurate hit/miss counter tracking |
| Update moves item to front | Updated items are protected from eviction |

---

## Real World Applications

This exact pattern is used in:

- **Web Browsers** — cache CSS, images, HTML for page revisits
- **Instagram / YouTube / Netflix** — feed posts and thumbnails cached so scrolling back is instant
- **Google Search** — popular query results served from cache, not recomputed
- **Redis** — a standalone LRU cache service used by Twitter, GitHub, Airbnb
- **Operating Systems** — recently accessed files kept in RAM
- **CDNs (Cloudflare, Akamai)** — website content cached on nearest servers globally

---

## Author

**Divyansh Pankaj Mishra**  
[GitHub](https://github.com/SlingggShottt/lru-cache-simulator)