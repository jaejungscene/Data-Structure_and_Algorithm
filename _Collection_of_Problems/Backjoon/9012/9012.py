"""
괄호
https://www.acmicpc.net/problem/9012
"""
import sys
def input():
    return sys.stdin.readline().rstrip()

T = int(input())

flag = True
answer = []
for _ in range(T):
    vps = input()
    stack = []
    for j in range(len(vps)):
        if vps[j] == "(":
            stack.append(vps[j])
        elif len(stack) > 0:
            if stack[-1] == "(" and vps[j] == ")":
                del stack[-1]
            else:
                flag = False
                break
        else:
            flag = False
            break
    if len(stack) != 0:
        flag = False 
    answer.append(flag)
    flag = True

for i in range(T):
    if answer[i]:
        print("YES")
    else:
        print("NO")


"""
6
(())())
(((()())()
(()())((()))
((()()(()))(((())))()
()()()()(()()())()
(()((())()(
"""