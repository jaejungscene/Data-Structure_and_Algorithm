def solution(board, moves):
    answer = 0
    selected = []
    for select in moves:
        select -= 1
        for i in range(len(board)):
            if board[i][select] != 0:
                selected.append(board[i][select])
                board[i][select] = 0
                break
        if len(selected)>=2 and selected[-1] == selected[-2]:
            del selected[-1]
            del selected[-1]
            answer += 2
    return answer


## Test 1
board = [
    [0,0,0,0,0],
    [0,0,1,0,3],
    [0,2,5,0,1],
    [4,2,4,4,2],
    [3,5,1,3,1]]
moves = [1,5,3,5,1,2,1,4]
print(solution(board, moves))