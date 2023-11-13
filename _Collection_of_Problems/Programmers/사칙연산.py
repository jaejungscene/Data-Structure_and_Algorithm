from collections import defaultdict
from itertools import combinations

store = defaultdict(int)
store["hello"] += 1
store["world"] += 1
store["world"] += 1
store["jaejung"] += 1
print(store)
print(list(store.keys()))
print(list(store.values()))

comb = combinations(list(store.keys()), 1)
print(list(comb))
comb = combinations(list(store.keys()), 2)
print(list(comb))
