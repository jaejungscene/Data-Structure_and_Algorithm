def solution(board: list, skill: list) -> int:
    answer = 0
    tmp = [[0 for _ in range(len(board[0])+1)] for _ in range(len(board)+1)]
    for t, r1, c1, r2, c2, degree in skill:
        tmp[r1][c1] += -degree if t==1 else degree
        tmp[r1][c2+1] += degree if t==1 else -degree
        tmp[r2+1][c1] += degree if t==1 else -degree
        tmp[r2+1][c2+1] += -degree if t==1 else degree
    
    for i in range(len(tmp)-1):
        for j in range(len(tmp[0])-1):
            tmp[i][j+1] += tmp[i][j]

    for j in range(len(tmp[0])-1):
        for i in range(len(tmp)-1):
            tmp[i+1][j] += tmp[i][j]

    for i in range(len(board)):
        for j in range(len(board[0])):
            board[i][j] += tmp[i][j]
            if board[i][j] > 0:
                answer += 1
                
    return answer