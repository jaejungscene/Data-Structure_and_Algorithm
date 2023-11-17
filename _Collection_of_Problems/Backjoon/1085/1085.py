import sys
def input():
    return sys.stdin.readline().rstrip()

x, y, w, h = map(int, input().split(" "))

answers = [w-x, h-y, x, y]
print(min(answers))