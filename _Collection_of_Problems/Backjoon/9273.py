import sys
def input():
    return sys.stdin.readline().rstrip()
    
n = int(input())
times = list(map(int, sys.stdin.readline().split()))
times.sort(reverse=True)
times = [times[i]-(n-(i+1)) for i in range(n)]
print(n+max(times)+1)