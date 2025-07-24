"""
첫번재 풀이
"""
import sys
from collections import defaultdict

if __name__ == "__main__":
    input = sys.stdin.readline
    N, K = map(int, input().split())

    medal_to_nation = defaultdict(set)
    for _ in range(N):
        nation, gold, silver, bronze = map(int, input().split())
        medal = (gold, silver, bronze)
        medal_to_nation[medal].add(nation)

    sorted_items = sorted(medal_to_nation.items(), reverse=True)

    rank = 1
    for _, nations in sorted_items:
        if K in nations:
            print(rank)
            break
        rank += len(nations)

"""
두번재 풀이
"""
import sys

if __name__ == "__main__":
    input = sys.stdin.readline
    N, K = map(int, input().split())

    countries = []
    for _ in range(N):
        nation, gold, silver, bronze = map(int, input().split())
        countries.append((gold, silver, bronze, nation))

    countries.sort(key=lambda x: (x[0], x[1], x[2]), reverse=True)

    k_medals = ()
    for g, s, b, n in countries:
        if n == K:
            k_medals = (g, s, b)
            break
    
    rank = 0
    for i in range(N):
        if (countries[i][0], countries[i][1], countries[i][2]) == k_medals:
            rank = i + 1
            break
            
    print(rank)
