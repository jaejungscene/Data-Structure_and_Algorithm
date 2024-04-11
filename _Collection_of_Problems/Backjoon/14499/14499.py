"""
주사위 굴리기
https://www.acmicpc.net/problem/14499
"""

N, M, x, y, K = map(int, input().split())
board = [ list(map(int, input().split())) for _ in range(N) ]
command_list = list( map(int, input().split()) )
dice = [
    [0],
    [0, 0, 0],
    [0],
    [0]
]
dx = [None, 0, 0, -1, 1]
dy = [None, 1, -1, 0, 0]

def move_dice(dice: list, command: int) -> list:
    if command == 1: #동
        dice = [
            [dice[0][0]],
            [dice[3][0], dice[1][0], dice[1][1]],
            [dice[2][0]],
            [dice[1][2]]
        ]
    elif command == 2: #서
        dice = [
            [dice[0][0]],
            [dice[1][1], dice[1][2], dice[3][0]],
            [dice[2][0]],
            [dice[1][0]]
        ]
    elif command == 3: #북
        dice = [
            [dice[1][1]],
            [dice[1][0], dice[2][0], dice[1][2]],
            [dice[3][0]],
            [dice[0][0]]
        ]
    elif command == 4: #남
        dice = [
            [dice[3][0]],
            [dice[1][0], dice[0][0], dice[1][2]],
            [dice[1][1]],
            [dice[2][0]]
        ]
    return dice


for command in command_list:
    x += dx[command]
    y += dy[command]
    
    if x < 0 or x >= N or y < 0 or y >= M:
        x -= dx[command]
        y -= dy[command]
        continue

    dice = move_dice(dice, command)
    if board[x][y] == 0:
        board[x][y] = dice[3][0]
    else:
        dice[3][0] = board[x][y]
        board[x][y] = 0
    print(dice[1][1])