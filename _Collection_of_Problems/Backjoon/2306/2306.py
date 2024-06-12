"""
유전자
"""
# input_seq = input()
# dp = [ [ 0 for _ in range(len(input_seq)) ] for _ in range((len(input_seq))) ]
# for s in range(len(input_seq)-2, -1, -1):
#     for e in range(s+1, len(input_seq)):
#         if (input_seq[s] == "a" and input_seq[e] == "t")\
#         or (input_seq[s] == "g" and input_seq[e] == "c"):
#             dp[s][e] = dp[s+1][e-1] + 2
#         else:
#             dp[s][e] = max(dp[s+1][e], dp[s][e-1])
#             for i in range(s+1, e):
#                 dp[s][e] = max(dp[s][i] + dp[i+1][e], dp[s][e])

# print(dp[0][-1])
# list(map(print, dp))










# A=input()
# size=len(A)

# dp=[[0 for j in range(size)] for i in range(size)]

# for j in range(1,size):
#     for k in range(size-j):
#         dp[k][j + k] = dp[k + 1][j + k - 1]
#         #a()t or g()c
#         if (A[k]=="a" and A[j+k]=="t") or (A[k]=="g" and A[j+k]=="c"):
#             dp[k][j+k]+=2

#         #합치기
#         for s in range(1,j+1):
#             dp[k][j+k]=max(dp[k][j+k],dp[k][j+k-s]+dp[k+(j+1-s)][j+k])

# print(dp[0][size-1])
# list(map(print, dp))











myDNA = input()
N = len(myDNA)

DP = [[-1] * N for _ in range(N)] # DP[i][j] = i ~ j 까지 DNA 서열에서 최장KOI 길이

def DFS(x, y):
    if x >= y:
        return 0
    
    if DP[x][y] != -1:
        return DP[x][y]
    
    if (myDNA[x] == "a" and myDNA[y] == "t") or (myDNA[x] == "g" and myDNA[y] == "c"):
        DP[x][y] = DFS(x+1, y-1) + 2

    for i in range(x, y):
        DP[x][y] = max(DP[x][y], DFS(x, i) + DFS(i+1, y))
    
    return DP[x][y]

DFS(0, N-1)
print(DP[0][N-1])
