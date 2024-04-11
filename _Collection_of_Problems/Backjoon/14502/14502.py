"""
연구소
"""
import copy
from collections import deque
from itertools import combinations

N, M = map(int, input().split(" "))
building = [ list(map(int, input().split(" "))) for _ in range(N) ]

def cal_not_infected_areas(building: list[list[int]]) -> int:
    global N, M
    dx = [1,-1,0,0]
    dy = [0,0,1,-1]
    queue = deque()
    for y in range(N):
        for x in range(M):
            if building[y][x] == 2:
                queue.append((y,x))

    while len(queue):
        y, x = queue.popleft()
        for i in range(4):
            next_x, next_y = (x+dx[i], y+dy[i])
            if (0 <= next_y < N) and (0 <= next_x < M) and (building[next_y][next_x] == 0):
                building[next_y][next_x] = 2
                queue.append((next_y, next_x))
    
    count = sum([i.count(0) for i in building])
    return count

result = 0
zero_x_y = [(x, y) for x in range(M) for y in range(N) if not building[y][x]]
for c in combinations(zero_x_y, 3):
    temp_building = copy.deepcopy(building)
    for x, y in c:
        temp_building[y][x] = 1
    result = max(result, cal_not_infected_areas(temp_building))

print(result)