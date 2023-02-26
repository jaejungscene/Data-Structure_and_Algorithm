import sys
def input():
    return sys.stdin.readline().rstrip()

N = int(input())
answer = 0
while N!=0:
    if N % 5 == 0:
        quotient = N//5
        answer += quotient
        N -= quotient * 5
    elif N < 3:
        answer = -1
        break
    else:
        answer += 1
        N -= 3
    # print(N)
print(answer)