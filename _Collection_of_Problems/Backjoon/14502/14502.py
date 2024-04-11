"""
연구소
"""
import copy
from collections import deque
from itertools import combinations

N, M = map(int, input().split(" "))
building = [ list(map(int, input().split(" "))) for _ in range(N) ]
result = 0
zero_x_y = [(x, y) for x in range(M) for y in range(N) if not building[y][x]]
first_virus = []
for y in range(N):
    for x in range(M):
        if building[y][x] == 2:
            first_virus.append((y, x))


def cal_not_infected_areas(building: list[list[int]]) -> int:
    global N, M, first_virus
    dx = [1,-1,0,0]
    dy = [0,0,1,-1]
    queue = deque(first_virus)

    while len(queue):
        y, x = queue.popleft()
        for i in range(4):
            nx, ny = (x+dx[i], y+dy[i])
            if (0 <= ny < N) and (0 <= nx < M) and (building[ny][nx] == 0):
                building[ny][nx] = 2
                queue.append((ny, nx))
    
    count = sum([i.count(0) for i in building])
    return count


for c in combinations(zero_x_y, 3):
    temp_building = copy.deepcopy(building)
    for x, y in c:
        temp_building[y][x] = 1
    result = max(result, cal_not_infected_areas(temp_building))

print(result)