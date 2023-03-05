from sys import stdin

for line in stdin:
    N = int(line.rstrip().split("/")[-1])
    squareN = N**2
    cnt = 0
    for i in range(1, squareN+1):
        if squareN % i == 0:
            cnt += 1
    if cnt%2 == 0:
        print(cnt//2)
    else:
        print(cnt//2 +1)