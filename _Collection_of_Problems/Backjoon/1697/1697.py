"""
숨바꼭질
https://www.acmicpc.net/problem/1697
"""
from collections import deque

N, K = map(int, input().split(" "))
MAX_VALUE = 100000

def bfs(N: int, K: int) -> int:
    global MAX_VALUE
    visited = set()
    q = deque([N])
    cnt = 0
    
    while cnt < abs(N-K) and len(q) != 0:
        step = len(q)
        for i in range(step):
            now = q.popleft()
            if now-1 == K or now+1 == K or now*2 == K:
                cnt += 1
                return cnt
            if 0 <= now-1 and now-1 <= MAX_VALUE and now-1 not in visited:
                visited.add(now-1)
                q.append(now-1)
            if 0 <= now+1 and now+1 <= MAX_VALUE and now+1 not in visited:
                visited.add(now+1)
                q.append(now+1)
            if 0 <= now*2 and now*2 <= MAX_VALUE and now*2 not in visited:
                visited.add(now*2)
                q.append(now*2)
        cnt += 1
    return abs(N-K)

print(bfs(N, K))

"""
5 12

5 17

4 2
"""
"""
3

4

2
"""