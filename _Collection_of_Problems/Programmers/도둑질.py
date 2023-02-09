""" 
go to>> https://school.programmers.co.kr/learn/courses/30/lessons/42897
"""
def solution(money):
    N = len(money)
    if N<=3:
        return max(money)
    else:
        cost1 = [0 for _ in range(N-1)]
        cost1[0] = money[0]
        cost1[1] = max(money[0], money[1])
        for i in range(2, N-1):
            cost1[i] = max(cost1[i-1], money[i]+cost1[i-2])

        cost2 = [0 for _ in range(N-1)]
        cost2[0] = money[1]
        cost2[1] = max(money[1], money[2])
        for i in range(2, N-1):
            cost2[i] = max(cost2[i-1], money[i+1]+cost2[i-2])
		
    return max(cost1[-1], cost2[-1])

money = [1,2,3,3,2,2]
print(solution(money))