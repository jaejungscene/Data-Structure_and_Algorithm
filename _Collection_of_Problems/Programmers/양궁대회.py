diff = 0
answer = []

def compareScore(info: list, lionList: list):
    global diff, answer
    score = 0
    for i in range(11):
        if info[i] < lionList[i]:
            score += 10 - i
        elif info[i] != 0:
            score -= 10 - i
    if score > diff:
        answer = lionList.copy()
        diff = score
    if diff != 0 and score == diff:
        for i in range(10, -1, -1):
            if answer[i] != lionList[i]:
                if answer[i] < lionList[i]:
                    answer = lionList.copy()
                break


def dfs(now: int, n: int, info: list, lionList: list):
    global diff, answer

    if n == 0 or now == 11:
        compareScore(info, lionList)
        return

    for i in range(now, 11):
        if n > info[i]:
            lionList[i] = info[i] + 1
            dfs(i + 1, n - info[i] - 1, info, lionList)
            lionList[i] = 0

    if n != 0:
        lionList[-1] = n
        compareScore(info, lionList)
        lionList[-1] = 0
    return
                
                
def solution(n: int, info: list) -> list:
    global answer, diff
    
    dfs(0, n, info, [0 for _ in range(11)])
    if len(answer) == 0:
        return [-1]
    
    return answer
