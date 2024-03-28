N, M, K = map(int, input().split())
NxM_map = list( list(map(int,input().split())) for _ in range(N) )

now_coord = [0, 0]
direction = [
    [0, 1], # 0 right
    [1, 0], # 1 bottom
    [0, -1], # 2 left
    [-1, 0] # 3 top
]
now_direct_str = "right"
now_direct_num = 0
die = [
    [2],
    [4,1,3],
    [5],
    [6]
]

def changeDie(die:list, now_direct_num: int) -> list:
    if 0 == now_direct_num: #right
        die = [
            [die[0][0]],
            [die[3][0],die[1][0],die[1][1]],
            [die[2][0]],
            [die[1][2]],
        ]
    elif 2 == now_direct_num: #left
        die = [
            [die[0][0]],
            [die[1][1],die[1][2],die[3][0]],
            [die[2][0]],
            [die[1][0]],
        ]
    elif 3 == now_direct_num: #top
        die = [
            [die[1][1]],
            [die[1][0],die[2][0],die[1][2]],
            [die[3][0]],
            [die[0][0]],
        ]
    elif 1 == now_direct_num: #bottom
        die = [
            [die[3][0]],
            [die[1][0],die[0][0],die[1][2]],
            [die[1][1]],
            [die[2][0]],
        ]
    return die


def dfs(num:list, value:int, now_coord:list, NxM_map: list, visited: set):
    dx = [0,1,0,-1]
    dy = [-1,0,1,0]

    for i in range(4):
        new_coord = [now_coord[0]+dx[i], now_coord[1]+dy[i]]
        if new_coord[0]>=0 and new_coord[0]<len(NxM_map)\
        and new_coord[1]>=0 and new_coord[1]<len(NxM_map[0])\
        and tuple(new_coord) not in visited\
        and NxM_map[new_coord[0]][new_coord[1]] == value:
            num[0] += 1
            visited.add(tuple(new_coord))
            dfs(num, value, new_coord, NxM_map, visited)


SCORE = 0
for i in range(K):
    # 1. 주사위가 이동 방향으로 한 칸 굴러간다. 만약, 이동 방향에 칸이 없다면, 이동 방향을 반대로 한 다음 한 칸 굴러간다.
    now_direct = direction[now_direct_num]
    if now_coord[0] + now_direct[0] < 0\
    or now_coord[0] + now_direct[0] >= N\
    or now_coord[1] + now_direct[1] < 0\
    or now_coord[1] + now_direct[1] >= M:
        now_direct_num = (now_direct_num + 2) % 4
        now_direct = direction[now_direct_num]
    now_coord[0] += now_direct[0]
    now_coord[1] += now_direct[1]
    die = changeDie(die, now_direct_num)

    # 2. 주사위가 도착한 칸 (x, y)에 대한 점수를 획득한다.
    visited = set([(now_coord[0], now_coord[1])])
    value = NxM_map[now_coord[0]][now_coord[1]]
    num = [1]
    dfs(num, value, now_coord, NxM_map, visited)
    SCORE += num[0] * value

    # 3. 주사위의 아랫면에 있는 정수 A와 주사위가 있는 칸 (x, y)에 있는 정수 B를 비교해 이동 방향을 결정한다.
    if die[3][0] > value:
        now_direct_num = (now_direct_num + 1) % 4
    elif die[3][0] < value:
        now_direct_num = (now_direct_num - 1) % 4
    else:
        pass

print(SCORE)