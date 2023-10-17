from itertools import combinations
result = 99999999
MAX_N = 50
N, M = tuple(map(int, input().split()))
cityMap = list(list(map(int, input().split())) for _ in range(N))

houses = []
chickens = []
for i in range(N):
    for j in range(N):
        if cityMap[i][j] == 1:
            houses.append((i, j))
        elif cityMap[i][j] == 2:
            chickens.append([i, j])

for comb in combinations(chickens, M):
    temp = 0
    for (k, t) in houses:
        temp += min( map(lambda x: abs(k-x[0])+abs(t-x[1]), comb) )
    result = min(result, temp)

print(result)








# 5 3
# 0 0 1 0 0
# 0 0 2 0 1
# 0 1 2 0 0
# 0 0 1 0 0
# 0 0 0 0 2
#
# 5 2
# 0 2 0 1 0
# 1 0 1 0 0
# 0 0 0 0 0
# 2 0 0 1 1
# 2 2 0 1 2
#
# 5 1
# 1 2 0 0 0
# 1 2 0 0 0
# 1 2 0 0 0
# 1 2 0 0 0
# 1 2 0 0 0
#
# 5 1
# 1 2 0 2 1
# 1 2 0 2 1
# 1 2 0 2 1
# 1 2 0 2 1
# 1 2 0 2 1