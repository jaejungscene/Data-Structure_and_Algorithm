"""
평범한 배낭
https://www.acmicpc.net/problem/12865

row: limit weight
column: items (item starts from 1, so 0 item means no item)
"""


import sys
def input():
    return sys.stdin.readline().rstrip()

N, K = map(int, input().split(" "))
dp = [[0 for _ in range(K+1)] for _ in range(N+1)]

stuff = {}
for i in range(1,N+1):
    weight, value = map(int, input().split(" "))
    stuff[i] = {"weight": weight, "value": value}

for i in range(1,N+1):
    for w in range(1,K+1):
        if stuff[i]["weight"] > w:
            dp[i][w] = dp[i-1][w]
        else:
            dp[i][w] = max(dp[i-1][w], stuff[i]["value"]+dp[i-1][w-stuff[i]["weight"]])

print(dp[-1][-1])