# dynamic programming으로 구현
def solution(m, n, puddles):
    s = set(map(tuple, puddles))
    opt = [[0 for _ in range(m+1)] for _ in range(n+1)]
    opt[1][1] = 1

    for x in range(1,n+1):
        for y in range(1,m+1):
            if (x==1 or y==1) and ((y,x) not in s):
                if (opt[x][y-1] != 0) or (opt[x-1][y] != 0):
                    opt[x][y] = 1
            elif (y, x) not in s:
                opt[x][y] = (opt[x-1][y] + opt[x][y-1])
                
    return opt[n][m] % 1000000007


# dfs 형식으로 구현 -> 효율성 실패
def solution(m, n, puddles):
    global answer
    answer = 0
    s = set(map(tuple, puddles))
    
    def search(nowX, nowY):
        global answer
        if nowX == n and nowY == m:
            answer += 1
            return
        
        if nowX > n or nowY > m or (nowY, nowX) in s:
            return
        
        search(nowX+1, nowY)
        search(nowX, nowY+1)
    
    search(1, 1)
    return answer%1000000007
