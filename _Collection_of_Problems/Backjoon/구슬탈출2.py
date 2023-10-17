from collections import defaultdict, deque

N, M = map(int, input().split())
board = [[char for char in input("")] for _ in range(N)]


def printboard(num, board, R, B, d):
    import os
    root = os.path.dirname(os.path.abspath(__file__))
    with open(f"{root}/output.txt", "a") as f:
        f.write(f"-------- {num} --------\n")
        f.write(f"R: {R},  B: {B},  d: {d}\n")
        for i in range(len(board)):
            for j in range(len(board[0])):
                if board[i][j] == "O":
                    f.write(f"{board[i][j]}")
                elif i==R[0] and j==R[1]:
                    f.write("R")
                elif i==B[0] and j==B[1]:
                    f.write("B")
                else:
                    f.write(f"{board[i][j]}")
            f.write("\n")
        f.write("-------------------------\n")


def move(main: list[int], sub: list[int], board: list[int], dx: int, dy: int) -> list[int]:
    mx, my = main
    while board[mx+dx][my+dy] == "." and not(mx+dx == sub[0] and my+dy == sub[1]):
        mx += dx
        my += dy
    if board[mx+dx][my+dy] == "O":
        mx += dx
        my += dy
    return [mx, my]


def play(N, M, board):
    q = defaultdict(deque)
    q["d"].append([1,1])
    for i in range(len(board)):
        for j in range(len(board[0])):
            if board[i][j] == "R":
                q["R"].append([i, j])
                board[i][j] ="."
            if board[i][j] == "B":
                q["B"].append([i, j])
                board[i][j] = "."
            if len(q["B"]) != 0 and len(q["R"]) != 0:
                break

    direction = [(1,0), (0,1), (-1,0), (0,-1)] # bottom, right, top, left
    for i in range(1,11):
        size = len(q["d"])
        # print(i, size)
        for _ in range(size):
            prev = q["d"].popleft()
            R = q["R"].popleft()
            B = q["B"].popleft()
            for dx, dy in direction:
                if not(-prev[0] == dx and -prev[1] == dy):
                    if ((dx, dy) == (1, 0) and B[1] == R[1] and B[0] > R[0])\
                        or ((dx, dy) == (0, 1) and B[0] == R[0] and B[1] > R[1])\
                        or ((dx, dy) == (-1, 0) and B[1] == R[1] and B[0] < R[0])\
                        or ((dx, dy) == (0, -1) and B[0] == R[0] and B[1] < R[1]):
                        newB = move(B, R, board, dx, dy)
                        newR = move(R, newB, board, dx, dy)
                    else:
                        newR = move(R, B, board, dx, dy)
                        newB = move(B, newR, board, dx, dy)

                    if board[newB[0]][newB[1]] != "O" and board[newR[0]][newR[1]] == "O":
                        # printboard(i, board, newR, newB, [dx,dy])
                        return i
                    if board[newB[0]][newB[1]] != "O" and not(newR == R and newB == B):
                        # printboard(i, board, newR, newB, [dx,dy])
                        q["d"].append([dx,dy])
                        q["R"].append(newR)
                        q["B"].append(newB)
    return -1

print(play(N, M, board))