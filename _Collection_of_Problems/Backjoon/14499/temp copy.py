N, M, x, y, K = map(int, input().split())
board = [ list(map(int, input().split())) for _ in range(N) ]
command_list = list( map(int, input().split()) )
dice = [0, 0, 0, 0, 0, 0]
dx = [None, 0, 0, -1, 1]
dy = [None, 1, -1, 0, 0]


def move_dice(dice: list, command: int) -> list:
    a, b, c, d, e, f = dice[0], dice[1], dice[2], dice[3], dice[4], dice[5]
    if command == 1: #동
        dice[0], dice[1], dice[2], dice[3], dice[4], dice[5] = d, b, a, f, e, c
    elif command == 2: #서
        dice[0], dice[1], dice[2], dice[3], dice[4], dice[5] = c, b, f, a, e, d
    elif command == 3: #북
        dice[0], dice[1], dice[2], dice[3], dice[4], dice[5] = e, a, c, d, f, b
    elif command == 4: #남
        dice[0], dice[1], dice[2], dice[3], dice[4], dice[5] = b, f, c, d, a, e
    return dice


for command in command_list:
    x += dx[command]
    y += dy[command]
    
    if x < 0 or x >= N or y < 0 or y >= M:
        x -= dx[command]
        y -= dy[command]
        continue

    move_dice(dice, command)
    if board[x][y] == 0:
        board[x][y] = dice[-1]
    else:
        dice[-1] = board[x][y]
        board[x][y] = 0
    print(dice[0])