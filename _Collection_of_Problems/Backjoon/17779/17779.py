# 게리맨더링 2
# https://www.acmicpc.net/problem/17779
N = int(input())
A = [ list(map(int, input().split(" "))) for _ in range(N) ]

def calculMinMax(A: list, x, y, d1, d2) -> int:
    population = [ 0 for _ in range(5) ]

    s = 0
    e = 0
    fiveArea = set()
    for step, i in enumerate(range(x, x+d1+d2+1)):
        s = y - step if step <= d1 else s + 1
        e = y + step if step <= d2 else e - 1
        for j in range(s, e+1):
            population[4] += A[i][j]
            fiveArea.add((i, j))

    for i in range(len(A)):
        for j in range(len(A[0])):
            if (i, j) not in fiveArea:
                if 0<=i and i<x+d1 and 0<=j and j<=y:
                    population[0] += A[i][j]
                elif 0<=i and i<=x+d2 and y<j and j<N:
                    population[1] += A[i][j]
                elif x+d1<=i and i<N and 0<=j and j<y-d1+d2:
                    population[2] += A[i][j]
                elif x+d2<i and i<N and y-d1+d2<=j and j<N:
                    population[3] += A[i][j]    
    return max(population) - min(population)


def solution(A: list) -> int:
    result = 100000000000  # min(maxNum - minNum)
    x = 0
    y = 0
    d1 = 1
    d2 = 1
    for x in range(N):
        for y in range(1, N):
            for d1 in range(1, N):
                for d2 in range(1, N):
                    if d1>=1 and d2>=1 and 0<=x and x+d1+d2<N and 0<=y-d1 and y+d2<N:
                        result = min(result, calculMinMax(A, x, y, d1, d2))
    return result


print(solution(A))

"""
input

6
1 2 3 4 1 6
7 8 9 1 4 2
2 3 4 1 1 3
6 6 6 6 9 4
9 1 9 1 9 5
1 1 1 1 9 9

6
5 5 5 5 5 5
5 5 5 5 5 5
5 5 5 5 5 5
5 5 5 5 5 5
5 5 5 5 5 5
5 5 5 5 5 5

8
1 2 3 4 5 6 7 8
2 3 4 5 6 7 8 9
3 4 5 6 7 8 9 1
4 5 6 7 8 9 1 2
5 6 7 8 9 1 2 3
6 7 8 9 1 2 3 4
7 8 9 1 2 3 4 5
8 9 1 2 3 4 5 6

"""

"""
output

18

20

23
"""