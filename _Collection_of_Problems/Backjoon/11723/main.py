import sys

input = sys.stdin.readline

def solve():
    try:
        M = int(input())
    except (ValueError, IndexError):
        return

    S = 0
    
    for _ in range(M):
        command_line = input().rstrip().split()
        cmd = command_line[0]

        if cmd == "add":
            x = int(command_line[1])
            S |= (1 << x)
        elif cmd == "remove":
            x = int(command_line[1])
            S &= ~(1 << x)
        elif cmd == "check":
            x = int(command_line[1])
            if S & (1 << x):
                print("1")
            else:
                print("0")
        elif cmd == "toggle":
            x = int(command_line[1])
            S ^= (1 << x)
        elif cmd == "all":
            S = (1 << 21) - 1
        elif cmd == "empty":
            S = 0

if __name__ == "__main__":
    solve()
