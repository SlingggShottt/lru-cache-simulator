from collections import OrderedDict

class LRUCache:

    # constructor
    def __init__(self, capacity : int):
        self.capacity : int = capacity
        self.cache : OrderedDict = OrderedDict() # both hashmap and list in one
        self.hits : int = 0
        self.misses : int = 0


    # get() method for checking if key exists in map
    def get(self, key : int) -> int:

        # cache miss
        if key not in self.cache:
            self.misses += 1
            return -1

        # cache hit
        self.hits += 1
        self.cache.move_to_end(key, last=False) # moves to front as last = False
        return self.cache[key]
    

    # put() method to add to cache
    def put(self, key : int, value : int):

        # if key in cache - update and move to front
        if key in self.cache:
            self.cache.move_to_end(key, last=False)
            self.cache[key] = value
            return
        
        # if key not in cache and cache full
        if len(self.cache) >= capacity:
            self.cache.popitem(last=True) # pop the last item
        
        # add the key and value to cache
        self.cache[key] = value
        # move to front
        self.cache.move_to_end(key, last=False)


    # method to print the current state of cache for easy debugging and visualization
    def state(self):

        # storing items in a container from our cache
        items = [{"key" : k, "value" : v} for k, v in self.cache.items()]

        # total queries
        total : int = self.hits + self.misses

        return {
            "capacity" : self.capacity,
            "size" : (self.cache),
            "items" : items, 
            "hits" : self.hits,
            "misses" : self.misses,
            "hitRatio" : round((self.hits/total) *100, 2) if total > 0 else 0.0,
            "totalQueries" : total
        }
