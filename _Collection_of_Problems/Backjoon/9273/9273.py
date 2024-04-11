"""
정제헌을 팔자!
https://www.acmicpc.net/problem/9273
"""
# 1/n = 1/a + 1/b
# a,b가 2n일 때 절반 지점이다.
# a,b 각각의 한계 지점은 n이다.
# n+1 -------- 2n -------- ?
# a                      b
#       a           b
#            ab
#       b           a
# b                      a
# 따라서 n+1부터 2n까지 a를 돌려보기만 하면 모든 쌍을 찾을 수 있음.

for _ in range(4):
    one, n = map(int, input().split('/'))
    cnt = 0
    for a in range(n+1, 2*n + 1):
        if (n*a) % (a-n) == 0:
            cnt += 1
    print(cnt)