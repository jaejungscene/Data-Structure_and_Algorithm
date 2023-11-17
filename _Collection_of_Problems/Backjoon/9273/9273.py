"""
정제헌을 팔자!
https://www.acmicpc.net/problem/9273
"""
import sys
def input():
    return sys.stdin.readline().rstrip()


cntList = []
for _ in range(4):
    N = int(input().split("/")[-1])
    squareN = N**2
    cnt = 0
    for i in range(1, squareN+1):
        if squareN % i == 0:
            cnt += 1
    if cnt%2 == 0:
        cntList.append(cnt//2)
    else:
        cntList.append(cnt//2 + 1)

for elem in cntList:
    print(elem)