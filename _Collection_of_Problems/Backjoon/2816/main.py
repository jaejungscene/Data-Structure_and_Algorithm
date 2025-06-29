import sys


def get_input():
    N = sys.stdin.readline().rstrip()
    channel_list = [sys.stdin.readline().rstrip() for _ in range(int(N))]
    return N, channel_list


if __name__ == "__main__":
    N, channel_list = get_input()

    KBS1_idx = channel_list.index("KBS1")
    KBS2_idx = channel_list.index("KBS2")

    buttons = ""
    now_idx = 0

    buttons += "1" * KBS1_idx
    buttons += "4" * KBS1_idx
    value = channel_list.pop(KBS1_idx)
    channel_list.insert(0, value)

    if KBS2_idx < KBS1_idx:
        KBS2_idx += 1

    if channel_list[1] != "KBS2":
        buttons += "1" * KBS2_idx
        buttons += "4" * (KBS2_idx - 1)
        value = channel_list.pop(KBS2_idx)
        channel_list.insert(1, value)

    sys.stdout.write(buttons)
