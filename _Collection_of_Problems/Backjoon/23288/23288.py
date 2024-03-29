from collections import deque

N, M, K = map(int, input().split())
NxM_map = list( list(map(int,input().split())) for _ in range(N) )
RIGHT, DOWN, LEFT, UP = 0, 1, 2, 3
dx = [0,1,0,-1]
dy = [1,0,-1,0]
direct_num = RIGHT
die = [
    [2],
    [4,1,3],
    [5],
    [6]
]


def move_die(die:list, direct_num: int) -> list:
    if RIGHT == direct_num:
        die = [
            [die[0][0]],
            [die[3][0],die[1][0],die[1][1]],
            [die[2][0]],
            [die[1][2]],
        ]
    elif DOWN == direct_num:
        die = [
            [die[3][0]],
            [die[1][0],die[0][0],die[1][2]],
            [die[1][1]],
            [die[2][0]],
        ]
    elif LEFT == direct_num:
        die = [
            [die[0][0]],
            [die[1][1],die[1][2],die[3][0]],
            [die[2][0]],
            [die[1][0]],
        ]
    elif UP == direct_num:
        die = [
            [die[1][1]],
            [die[1][0],die[2][0],die[1][2]],
            [die[3][0]],
            [die[0][0]],
        ]
    return die


def dfs(num:list, B:int, now_coord:list, NxM_map: list, visited: set):
    dx = [0,1,0,-1]
    dy = [-1,0,1,0]

    for i in range(4):
        new_coord = [now_coord[0]+dx[i], now_coord[1]+dy[i]]
        if new_coord[0]>=0 and new_coord[0]<len(NxM_map)\
        and new_coord[1]>=0 and new_coord[1]<len(NxM_map[0])\
        and tuple(new_coord) not in visited\
        and NxM_map[new_coord[0]][new_coord[1]] == B:
            num[0] += 1
            visited.add(tuple(new_coord))
            dfs(num, B, new_coord, NxM_map, visited)


def bfs(value:int, first_x:int, first_y:int, NxM_map:list) -> int:
    global N, M

    dx = [0,1,0,-1]
    dy = [1,0,-1,0]
    result = 0
    visited = set()
    q = deque()

    q.append((first_x, first_y))
    visited.add((first_x, first_y))
    while len(q) != 0:
        now_x, now_y = q.popleft()
        result += value
        for j in range(4):
            next_x = now_x + dx[j]
            next_y = now_y + dy[j]
            if next_x >= 0 and next_y >= 0 and next_x < N and next_y < M\
            and (next_x, next_y) not in visited and NxM_map[next_x][next_y] == value:
                visited.add((next_x, next_y))
                q.append((next_x, next_y))
    return result


loc_store = (0, 0)
SCORE = 0
for i in range(K):
    # 1. 주사위가 이동 방향으로 한 칸 굴러간다. 만약, 이동 방향에 칸이 없다면, 이동 방향을 반대로 한 다음 한 칸 굴러간다.
    now_x = loc_store[0] + dx[direct_num]
    now_y = loc_store[1] + dy[direct_num]
    if now_x < 0 or now_y < 0 or now_x >= N or now_y >= M:
        direct_num = (direct_num + 2) % 4
        now_x = loc_store[0] + dx[direct_num]
        now_y = loc_store[1] + dy[direct_num]
    loc_store = (now_x, now_y)
    die = move_die(die, direct_num)
    A = die[3][0]
    B = NxM_map[now_x][now_y]

    # 2. 주사위가 도착한 칸 (x, y)에 대한 점수를 획득한다.
    # visited = set([(now_x, now_y)])
    # num = [1]
    # dfs(num, B, [now_x, now_y], NxM_map, visited)
    # SCORE += num[0] * B
    SCORE += bfs(B, now_x, now_y, NxM_map)

    # 3. 주사위의 아랫면에 있는 정수 A와 주사위가 있는 칸 (x, y)에 있는 정수 B를 비교해 이동 방향을 결정한다.
    if   A > B:     direct_num = (direct_num + 1) % 4
    elif A < B:     direct_num = (direct_num - 1) % 4

print(SCORE)