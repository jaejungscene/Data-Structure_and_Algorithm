import collections
N, K = tuple(map(int, input().split()))
belt = collections.deque(map(int, input().split()))
robot = collections.deque([0 for _ in range(N)])

result = 0
cntZero = 0
while cntZero < K:
    # 1.belt and robot move
    belt.rotate(1)
    robot.rotate(1)
    robot[0] = 0

    # 2. robots move toward if they can
    for i in range(len(robot)-1, -1, -1):
        if i == len(robot)-1:
            robot[i] = 0
        elif robot[i] == 1 and robot[i+1] == 0 and belt[i+1] > 0:
            robot[i + 1] = robot[i]
            robot[i] = 0
            belt[i+1] -= 1
            if belt[i+1] == 0:
                cntZero += 1

    # 3. put a new robot at start if it can
    if belt[0] != 0 and robot[0] == 0:
        robot[0] = 1
        belt[0] -= 1
        if belt[0] == 0:
            cntZero += 1

    result += 1

print(result)


#
# 3 6
# 10 10 10 10 10 10
