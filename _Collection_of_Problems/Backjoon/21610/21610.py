"""
마법사 상어와 비바라기
https://www.acmicpc.net/problem/21610
"""

from collections import deque

N, M = map(int, input().split())
maps = list( list(map(int,input().split())) for _ in range(N) )
move = list( tuple(map(int,input().split())) for _ in range(M) )

dList = [(), (0,-1), (-1,-1), (-1,0), (-1,1), (0,1), (1,1), (1,0), (1,-1)]
diagonal = [(-1,-1), (-1,1), (1,-1), (1,1)]

clouds = deque([(N-2,0),(N-2,1),(N-1,0),(N-1,1)])
prevClouds = set()

for d,s in move:
    # 1. move every cloud
    while len(clouds) > 0:
        x, y = clouds.popleft()
        dx, dy = dList[d]

        x = (x+(dx*s)) % N
        y = (y+(dy*s)) % N

        # 2. water increase by 1
        maps[x][y] += 1
        # 3. vanish the clouds
        prevClouds.add((x, y))

    # 4. water increase by the number of diagonal bukets full of water >= 2
    for x, y in prevClouds:
        for dx, dy in diagonal:
            if (-1 <(x+dx)and(x+dx)< N) and (-1 <(y+dy)and(y+dy)< N) and maps[x + dx][y + dy] > 0:
                maps[x][y] += 1

    # 5. create new clouds
    for i in range(len(maps)):
        for j in range(len(maps[0])):
            if maps[i][j] >= 2 and (i,j) not in prevClouds:
                clouds.append((i,j))
                maps[i][j] -= 2

    prevClouds.clear()

cnt = 0
for row in maps:
    for v in row:
        cnt += v

print(cnt)

"""
5 4
0 0 1 0 2
2 3 2 1 0
4 3 2 9 0
1 0 2 9 0
8 8 2 1 0
1 3
3 4
8 1
4 8

77
"""