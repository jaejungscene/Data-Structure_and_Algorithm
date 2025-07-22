import sys

if __name__ == "__main__":
    input = sys.stdin.readline
    N = int(input())
    person_list = []
    for _ in range(N):
        w, h = map(int, input().split())
        person_list.append((w, h))

    ranks = []
    for i in range(N):
        rank = 1
        for j in range(N):
            if (
                person_list[i][0] < person_list[j][0]
                and person_list[i][1] < person_list[j][1]
            ):
                rank += 1
        ranks.append(rank)

    print(" ".join(map(str, ranks)))
