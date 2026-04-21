from fastapi import FastAPI
from lruCache import LRUCache # self defined cache class


app = FastAPI() # app object that hold all the routes

cache = LRUCache(5) # creating a cache object


@app.get("/") # root url decorator
def root():
    return {"message": "LRU Cache API is running"}


@app.get("/state") # for getting current state of cache
def state():
    return cache.state()