"""
Explanation:
    assume that the number of bridges is 'cost',   
    values of cost table is defined like,
        {premise: 0 < i <= j < 30}
        cost = 0                                (if i=0, j=0)
             = 1                                (else if i==j)
             = j                                (else if i==1)
             = cost[i, j-1] + cost[i-1, j-1]    (else if i<j)

test case:
4
2 2 
1 5
2 3
2 4

result:
1
5
3
6
"""

import sys
def input():
    return sys.stdin.readline().rstrip()

# prepare
size = 30
T = int(input())
cost = [[0 for _ in range(size)] for _ in range(size)]

# fill cost table with values for DP
for i in range(size):
    for j in range(size):
        if i==0 or j==0:
            cost [i][j] = 0
        elif i==j:
            cost [i][j] = 1
        elif i==1:
            cost [i][j] = j
        else:
            cost [i][j] = cost [i][j-1] + cost [i-1][j-1]

for i in range(T):
    x, y = map(int, input().split(" "))
    print(cost[x][y])        